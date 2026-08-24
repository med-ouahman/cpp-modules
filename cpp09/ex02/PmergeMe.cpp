#include "PmergeMe.hpp"
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <climits>
#include <cstdlib>
#include <cctype>
#include <cerrno>

PmergeMe::PmergeMe(size_t k) {
	generateJacobsthal(k);
}

PmergeMe::PmergeMe(const PmergeMe&) {}

PmergeMe& PmergeMe::operator=(const PmergeMe&) { return *this; }

PmergeMe::~PmergeMe() {}

std::vector<size_t> PmergeMe::jacobsthalOrder(size_t k) const {
	std::vector<size_t> jacobsthal;
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);
	while (jacobsthal[jacobsthal.size() - 1] < k) {
		size_t next = jacobsthal[jacobsthal.size() - 1] +
		2 * jacobsthal[jacobsthal.size() - 2];
		jacobsthal.push_back(next);
	}

	std::vector<bool> used(k + 1, false);
	if (k >= 1) used[1] = true;

	std::vector<size_t> order;
	for (size_t idx = 2; idx < jacobsthal.size(); ++idx) {
		size_t upper = jacobsthal[idx];
		size_t lower = jacobsthal[idx - 1];
	
		if (upper > k) upper = k;
		for (size_t v = upper; v > lower; --v) {
			if (v >= 1 && v <= k && !used[v]) {
				order.push_back(v);
				used[v] = true;
			}
		}
	}

	for (size_t v = 2; v <= k; ++v) {
		if (!used[v]) {
			order.push_back(v);
			used[v] = true;
		}
	}

	return order;
}

void PmergeMe::generateJacobsthal(size_t k) {
	
	jacobsthal_.clear();

	jacobsthal_.reserve(k);
	jacobsthal_.push_back(0);
	jacobsthal_.push_back(1);

	while (jacobsthal_[jacobsthal_.size() - 1] < k) {
		size_t next = jacobsthal_[jacobsthal_.size() - 1] +
		2 * jacobsthal_[jacobsthal_.size() - 2];
		jacobsthal_.push_back(next);
	}

}

void PmergeMe::generateOrder(std::vector<size_t>& order, size_t k) const {
	
	for (size_t i = 2; i < jacobsthal_.size(); ++i) {

		size_t upper = std::min(k, jacobsthal_[i]);
		size_t lower = jacobsthal_[i - 1];
	
		for (size_t j = upper; j > lower; --j) {			
			order.push_back(j);
		}
	}
}

static bool parsePositiveInt(const std::string& token, int& out) {
	if (token.empty())
		return false;

	size_t i = 0;
	if (token[0] == '+') i = 1;

	if (i == token.size()) return false;

	for ( size_t j = i; j < token.size(); ++j ) {
		if (!std::isdigit(static_cast<unsigned char>(token[j])))
			return false;
	}

	errno = 0;
	long value = std::strtol(token.c_str(), NULL, 10);
	if (errno == ERANGE || value < 0 || value > INT_MAX)
		return false;

	out = static_cast<int>(value);
	return true;
}

void PmergeMe::parseArguments(std::vector<int>& out, const char** args, size_t size) {

	for ( size_t i = 0; i < size; ++i ) {
		std::istringstream iss(args[i]);
		std::string token;
		while (iss >> token) {
			int value;
			if (!parsePositiveInt(token, value))
				throw std::runtime_error("invalid argument");
			out.push_back(value);
		}
	}

	if (out.empty())
		throw std::runtime_error("no arguments");
}

void PmergeMe::mergeInsertVector(std::vector<int>& vec) const {

	size_t n = vec.size();

	if (n <= 1) return;
	
	bool hasOdd = (n % 2 == 1);
	int oddValue = 0;

	if (hasOdd) {
		oddValue = vec.back();
		vec.pop_back();
		n--;
	}

	size_t pairCount = n / 2;
	std::vector<int> smalls(pairCount);
	std::vector<int> larges(pairCount);

	for (size_t i = 0; i < pairCount; ++i) {
		int first = vec[2 * i];
		int second = vec[2 * i + 1];
		if (first > second) {
			larges[i] = first;
			smalls[i] = second;
		} else {
			larges[i] = second;
			smalls[i] = first;
		}
	}

	std::vector<int> originalLarges(larges);

	mergeInsertVector(larges);

	std::vector<size_t> rankOrder(pairCount);
	std::vector<bool> picked(pairCount, false);
	for (size_t r = 0; r < pairCount; ++r) {
		for (size_t i = 0; i < pairCount; ++i) {
			if (!picked[i] && originalLarges[i] == larges[r]) {
				rankOrder[r] = i;
				picked[i] = true;
				break;
			}
		}
	}

	size_t idx0 = rankOrder[0];
	std::vector<int>& chain = larges;
	chain.insert(chain.begin(), smalls[idx0]);

	std::vector<size_t> insertOrder;
	insertOrder.reserve(pairCount);
	generateOrder(insertOrder, insertOrder.capacity());
	
	for ( size_t i = 0; i < insertOrder.size(); ++i ) {
		size_t rank = insertOrder[i];
		size_t origIdx = rankOrder[rank - 1];
		int largeValue = originalLarges[origIdx];
		std::vector<int>::iterator boundIt = std::lower_bound(chain.begin(), chain.end(), largeValue);
		std::vector<int>::iterator insertPos = std::lower_bound(chain.begin(), boundIt, smalls[origIdx]);
		chain.insert(insertPos, smalls[origIdx]);
	}

	if (hasOdd) {
		std::vector<int>::iterator insertPos = std::lower_bound(chain.begin(), chain.end(), oddValue);
		chain.insert(insertPos, oddValue);
	}

	vec = chain;
}

void PmergeMe::mergeInsertDeque(std::deque<int>& deq) const {
	size_t n = deq.size();

	if (n <= 1) return;

	bool hasOdd = (n % 2 == 1);
	int oddValue = 0;
	if (hasOdd) {
		oddValue = deq.back();
		deq.pop_back();
		n--;
	}

	size_t pairCount = n / 2;
	std::deque<int> smalls(pairCount);
	std::deque<int> larges(pairCount);

	for (size_t i = 0; i < pairCount; ++i) {
		int first = deq[2 * i];
		int second = deq[2 * i + 1];
		if (first > second) {
			larges[i] = first;
			smalls[i] = second;
		} else {
			larges[i] = second;
			smalls[i] = first;
		}
	}

	std::deque<int> originalLarges(larges);

	mergeInsertDeque(larges);

	std::vector<size_t> rankOrder(pairCount);
	std::vector<bool> picked(pairCount, false);
	for (size_t r = 0; r < pairCount; ++r) {
		for (size_t i = 0; i < pairCount; ++i) {
			if (!picked[i] && larges[r] == originalLarges[i]) {
				rankOrder[r] = 0;
				picked[i] = true;
				break;
			}
		}
	}

	size_t idx0 = rankOrder[0];
	std::deque<int>& chain = larges;
	chain.insert(chain.begin(), smalls[idx0]);

	std::vector<size_t> insertOrder;
	insertOrder.reserve(pairCount);
	generateOrder(insertOrder, insertOrder.capacity());
	for (size_t i = 0; i < insertOrder.size(); ++i) {
		size_t rank = insertOrder[i];
		size_t origIdx = rankOrder[rank - 1];
		int largeValue = originalLarges[origIdx];
		std::deque<int>::iterator boundIt = std::lower_bound(chain.begin(), chain.end(), largeValue);
		std::deque<int>::iterator insertPos = std::lower_bound(chain.begin(), boundIt, smalls[origIdx]);
		chain.insert(insertPos, smalls[origIdx]);
	}

	if (hasOdd) {
		std::deque<int>::iterator insertPos = std::lower_bound(chain.begin(), chain.end(), oddValue);
		chain.insert(insertPos, oddValue);
	}

	deq = chain;
}

void PmergeMe::sortVector(std::vector<int>& vec) const {
	mergeInsertVector(vec);
}

void PmergeMe::sortDeque(std::deque<int>& deq) const {
	mergeInsertDeque(deq);
}
