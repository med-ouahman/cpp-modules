#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <numeric>

class Span {
public:
    Span(unsigned int n);
    Span(const Span &other);
    Span &operator=(const Span &other);
    ~Span();

    void addNumber(int n);

    template <typename InputIterator>
    void addNumbers(InputIterator begin, InputIterator end) {
        size_t count = static_cast<size_t>(std::distance(begin, end));
        if (_numbers.size() + count > _maxSize)
            throw std::runtime_error("Not enough capacity to add all numbers");
        _numbers.insert(_numbers.end(), begin, end);
    }

    int shortestSpan() const;
    int longestSpan() const;

private:
    unsigned int        _maxSize;
    std::vector<int>    _numbers;
};

#endif
