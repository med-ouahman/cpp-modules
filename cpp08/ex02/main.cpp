#include <iostream>
#include <list>
#include <stack>
#include "MutantStack.hpp"

int main()
{
    std::cout << "=== PDF Example: MutantStack ===" << std::endl;
    {
        MutantStack<int> mstack;

        mstack.push(5);
        mstack.push(17);
        std::cout << mstack.top() << std::endl;

        mstack.pop();
        std::cout << mstack.size() << std::endl;

        mstack.push(3);
        mstack.push(5);
        mstack.push(737);
        mstack.push(0);

        MutantStack<int>::iterator it  = mstack.begin();
        MutantStack<int>::iterator ite = mstack.end();
        ++it;
        --it;
        while (it != ite)
        {
            std::cout << *it << std::endl;
            ++it;
        }

        std::stack<int> s(mstack);
        (void)s;
    }

    std::cout << "\n=== Same sequence: std::list (outputs must match) ===" << std::endl;
    {
        std::list<int> lst;

        lst.push_back(5);
        lst.push_back(17);
        std::cout << lst.back() << std::endl;

        lst.pop_back();
        std::cout << lst.size() << std::endl;

        lst.push_back(3);
        lst.push_back(5);
        lst.push_back(737);
        lst.push_back(0);

        std::list<int>::iterator it  = lst.begin();
        std::list<int>::iterator ite = lst.end();
        ++it;
        --it;
        while (it != ite)
        {
            std::cout << *it << std::endl;
            ++it;
        }
    }

    std::cout << "\n=== Test: const_iterator ===" << std::endl;
    {
        MutantStack<int> ms;
        ms.push(10);
        ms.push(20);
        ms.push(30);

        const MutantStack<int> cms(ms);
        MutantStack<int>::const_iterator cit = cms.begin();
        while (cit != cms.end())
        {
            std::cout << *cit << " ";
            ++cit;
        }
        std::cout << std::endl;
    }

    std::cout << "\n=== Test: reverse_iterator (top to bottom) ===" << std::endl;
    {
        MutantStack<int> ms;
        ms.push(100);
        ms.push(200);
        ms.push(300);

        MutantStack<int>::reverse_iterator rit = ms.rbegin();
        while (rit != ms.rend())
        {
            std::cout << *rit << " ";
            ++rit;
        }
        std::cout << std::endl;
    }

    std::cout << "\n=== Test: copy constructor independence ===" << std::endl;
    {
        MutantStack<int> ms1;
        ms1.push(1);
        ms1.push(2);
        ms1.push(3);

        MutantStack<int> ms2(ms1);
        ms2.push(4);

        std::cout << "ms1 size: " << ms1.size() << std::endl;
        std::cout << "ms2 size: " << ms2.size() << std::endl;
    }

    std::cout << "\n=== Test: assignment operator ===" << std::endl;
    {
        MutantStack<int> ms1;
        ms1.push(7);
        ms1.push(8);

        MutantStack<int> ms2;
        ms2.push(99);
        ms2 = ms1;

        MutantStack<int>::iterator it = ms2.begin();
        while (it != ms2.end())
        {
            std::cout << *it << " ";
            ++it;
        }
        std::cout << std::endl;
    }

    std::cout << "\n=== Test: empty() and size() ===" << std::endl;
    {
        MutantStack<int> ms;
        std::cout << "empty: " << ms.empty() << std::endl;
        ms.push(42);
        std::cout << "size after push: " << ms.size() << std::endl;
        std::cout << "top: " << ms.top() << std::endl;
        ms.pop();
        std::cout << "empty after pop: " << ms.empty() << std::endl;
    }

    return 0;
}
