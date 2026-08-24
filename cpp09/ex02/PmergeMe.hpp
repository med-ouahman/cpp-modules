#pragma once

#include <vector>
#include <deque>
#include <string>
#include <iostream>

class PmergeMe {
public:
	PmergeMe(size_t k);
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();

	static void parseArguments(std::vector<int>& out, const char** args, size_t size);

	void sortVector(std::vector<int>& vec) const;
	void sortDeque(std::deque<int>& deq) const;

private:
	std::vector<size_t> jacobsthal_;

	void mergeInsertVector(std::vector<int>& vec) const;
	void mergeInsertDeque(std::deque<int>& deq) const;
	std::vector<size_t> jacobsthalOrder(size_t k) const;
	void generateJacobsthal(size_t k);
	void generateOrder(std::vector<size_t>& out, size_t n) const;
};
