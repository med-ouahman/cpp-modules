#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "easyfind.hpp"

static void printResult(const std::string &label, int value)
{
    std::cout << label << ": " << value << std::endl;
}

int main()
{
    std::cout << "=== std::vector tests ===" << std::endl;
    {
        std::vector<int> vec;
        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);
        vec.push_back(40);
        vec.push_back(50);

        try {
            std::vector<int>::iterator it = easyfind(vec, 30);
            printResult("Found in vector", *it);
        } catch (const std::exception &e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }

        try {
            easyfind(vec, 99);
        } catch (const std::exception &e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }

        try {
            std::vector<int>::iterator it = easyfind(vec, 10);
            printResult("Found first element", *it);
        } catch (const std::exception &e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }

        try {
            std::vector<int>::iterator it = easyfind(vec, 50);
            printResult("Found last element", *it);
        } catch (const std::exception &e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }
    }

    std::cout << "\n=== std::list tests (first occurrence) ===" << std::endl;
    {
        std::list<int> lst;
        lst.push_back(1);
        lst.push_back(2);
        lst.push_back(3);
        lst.push_back(2);

        try {
            std::list<int>::iterator it = easyfind(lst, 2);
            std::cout << "Found in list (first occurrence): " << *it << std::endl;
            ++it;
            std::cout << "Next element after found position: " << *it << std::endl;
        } catch (const std::exception &e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }

        try {
            easyfind(lst, 99);
        } catch (const std::exception &e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }
    }

    std::cout << "\n=== std::deque tests ===" << std::endl;
    {
        std::deque<int> deq;
        deq.push_back(100);
        deq.push_back(200);
        deq.push_back(300);

        try {
            std::deque<int>::iterator it = easyfind(deq, 200);
            printResult("Found in deque", *it);
        } catch (const std::exception &e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }

        try {
            easyfind(deq, 0);
        } catch (const std::exception &e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }
    }

    std::cout << "\n=== Empty container test ===" << std::endl;
    {
        std::vector<int> empty;
        try {
            easyfind(empty, 1);
        } catch (const std::exception &e) {
            std::cout << "Exception on empty container: " << e.what() << std::endl;
        }
    }

    return 0;
}
