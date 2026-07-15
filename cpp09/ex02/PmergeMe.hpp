#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();

		static std::vector<int> parseArguments(int argc, char** argv);

		void sortVector(std::vector<int>& vec) const;
		void sortDeque(std::deque<int>& deq) const;

	private:
		void mergeInsertVector(std::vector<int>& vec) const;
		void mergeInsertDeque(std::deque<int>& deq) const;
		std::vector<size_t> jacobsthalOrder(size_t k) const;
};

#endif
