# C++ Module 08 — Templated Containers, Iterators, Algorithms

## What This Module Is About

Module 08 introduces the **Standard Template Library (STL)**, the core of modern C++ programming. Previous modules forbade STL containers and algorithms. Here, using them is not just allowed — it is **required**. The module grades poorly if you solve exercises without them, even if the logic works.

The module covers three interlocking pillars of the STL:

- **Containers** — generic data structures (`std::vector`, `std::list`, `std::deque`, `std::stack`, etc.)
- **Iterators** — a uniform interface to traverse any container without knowing its internal layout
- **Algorithms** — generic functions (`std::find`, `std::sort`, `std::min_element`, `std::adjacent_difference`, etc.) that operate on any range defined by two iterators

All code must compile under the **C++98 standard** (`-std=c++98`), which means no lambdas, no range-based `for`, no `auto`. Every class that is not a template must follow the **Orthodox Canonical Form** (default constructor, copy constructor, copy assignment operator, destructor).

---

## Exercises at a Glance

| Exercise | Name | Core Skill |
|---|---|---|
| 00 | Easy find | Function templates + `std::find` |
| 01 | Span | Class design + STL algorithms + iterator ranges |
| 02 | Mutated abomination | Inheritance from STL adapter + exposing iterators |

---

## Key Concepts

### Function Templates
A function template generates a concrete function for each type it is instantiated with. The compiler deduces the type from the call site. Template definitions (not just declarations) must be visible at the point of instantiation, which is why they live in headers or `.tpp` files.

### Iterators
An iterator is an object that points into a container and supports at minimum `*` (dereference), `++` (advance), and `==`/`!=` (comparison). The STL defines five categories: input, output, forward, bidirectional, and random-access. Algorithms only require the weakest category they need, which makes them work with any compatible container.

### STL Algorithms
Algorithms in `<algorithm>` and `<numeric>` are free functions that take iterator pairs `[begin, end)`. They never know about the container itself — only about the range. This is the power of the iterator abstraction.

### Orthodox Canonical Form (OCF)
Classes must provide:
1. Default constructor
2. Copy constructor
3. Copy assignment operator (`operator=`)
4. Destructor

This ensures correct behaviour when objects are copied, assigned, or destroyed.

### Protected Container Member in `std::stack`
`std::stack` is a *container adapter*. It wraps an underlying container (default `std::deque`) exposed as the protected member `c`. A class that inherits from `std::stack` can access `this->c` directly — the key to Exercise 02.
