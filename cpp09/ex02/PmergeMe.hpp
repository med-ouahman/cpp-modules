#pragma once

#include <vector>
#include <deque>
#include <string>

struct Pair {
	size_t large;
	size_t small;
};

class PmergeMe {
public:
	PmergeMe(size_t maxK);
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();
	
	static bool parseArguments(std::vector<int>& out, char** args, size_t size);
	void sortVector(std::vector<int>& vec);
	void sortDeque(std::deque<int>& deq);

	const std::vector<size_t>& getMasterOrder() const;

private:
	std::vector<size_t> order_;
	void mergeInsertVector(std::vector<int>& vec);
	void mergeInsertDeque(std::deque<int>& deq);
	static void generateMasterOrder(size_t maxK, std::vector<size_t>& order_);
	
};
