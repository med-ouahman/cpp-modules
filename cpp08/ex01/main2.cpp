#include <iostream>
#include <vector>
#include <cstdlib>
#include "Span.hpp"

int main()
{
    std::cout << "=== PDF Example ===" << std::endl;
    {
        Span sp = Span(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);
        std::cout << sp.shortestSpan() << std::endl;
        std::cout << sp.longestSpan() << std::endl;
    }

    std::cout << "\n=== Test: Span full exception ===" << std::endl;
    {
        Span sp(3);
        sp.addNumber(1);
        sp.addNumber(2);
        sp.addNumber(3);
        try {
            sp.addNumber(4);
        } catch (const std::exception &e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }
    }

    std::cout << "\n=== Test: Too few numbers exception ===" << std::endl;
    {
        Span sp(5);
        try {
            sp.shortestSpan();
        } catch (const std::exception &e) {
            std::cout << "Empty span: " << e.what() << std::endl;
        }
        sp.addNumber(42);
        try {
            sp.longestSpan();
        } catch (const std::exception &e) {
            std::cout << "One element: " << e.what() << std::endl;
        }
    }

    std::cout << "\n=== Test: addNumbers with iterator range ===" << std::endl;
    {
        std::vector<int> source;
        source.push_back(1);
        source.push_back(5);
        source.push_back(3);
        source.push_back(9);
        source.push_back(7);

        Span sp(5);
        sp.addNumbers(source.begin(), source.end());
        std::cout << "shortestSpan: " << sp.shortestSpan() << std::endl;
        std::cout << "longestSpan:  " << sp.longestSpan() << std::endl;
    }

    std::cout << "\n=== Test: addNumbers overflow exception ===" << std::endl;
    {
        Span sp(3);
        std::vector<int> nums;
        nums.push_back(1);
        nums.push_back(2);
        nums.push_back(3);
        nums.push_back(4);
        try {
            sp.addNumbers(nums.begin(), nums.end());
        } catch (const std::exception &e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }
    }

    std::cout << "\n=== Test: 10 000 numbers ===" << std::endl;
    {
        Span sp(10000);
        std::vector<int> nums;
        nums.reserve(10000);
        std::srand(42);
        for (int i = 0; i < 10000; ++i)
            nums.push_back(std::rand());
        sp.addNumbers(nums.begin(), nums.end());
        std::cout << "shortestSpan: " << sp.shortestSpan() << std::endl;
        std::cout << "longestSpan:  " << sp.longestSpan() << std::endl;
    }

    std::cout << "\n=== Test: Copy constructor ===" << std::endl;
    {
        Span sp1(5);
        sp1.addNumber(1);
        sp1.addNumber(10);
        sp1.addNumber(5);

        Span sp2(sp1);
        std::cout << "shortestSpan: " << sp2.shortestSpan() << std::endl;
        std::cout << "longestSpan:  " << sp2.longestSpan() << std::endl;
    }

    std::cout << "\n=== Test: Assignment operator ===" << std::endl;
    {
        Span sp1(5);
        sp1.addNumber(2);
        sp1.addNumber(12);
        sp1.addNumber(7);

        Span sp2(3);
        sp2 = sp1;
        std::cout << "shortestSpan: " << sp2.shortestSpan() << std::endl;
        std::cout << "longestSpan:  " << sp2.longestSpan() << std::endl;
    }

    std::cout << "\n=== Test: Two equal numbers (span = 0) ===" << std::endl;
    {
        Span sp(3);
        sp.addNumber(7);
        sp.addNumber(7);
        sp.addNumber(20);
        std::cout << "shortestSpan: " << sp.shortestSpan() << std::endl;
        std::cout << "longestSpan:  " << sp.longestSpan() << std::endl;
    }

    return 0;
}
