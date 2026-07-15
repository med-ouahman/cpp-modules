# Exercise 01 — Reverse Polish Notation

## What this program does

`RPN` takes one argument: a space-separated Reverse Polish Notation expression
(e.g. `"8 9 * 9 - 9 - 9 - 4 - 1 +"`) and prints the result. Any malformed
expression prints `Error` to standard error and exits with status 1.

## Concepts covered

- **`std::stack<long>` as the required container.** RPN evaluation is the
  textbook use case for a stack: read tokens left to right, push numbers, and
  when an operator is seen, pop the two most recent operands, combine them, and
  push the result back. `std::stack` is a different container from the
  `std::map` used in ex00, satisfying the "can't reuse the previous exercise's
  container" rule.
- **Tokenizing with `std::istringstream`**, which conveniently splits on
  whitespace via `iss >> token`, instead of manually scanning `argv[1]`
  character by character.
- **Operator precedence is irrelevant in RPN** — that's the entire point of the
  notation. There's no need for a parser, precedence table, or recursion;
  everything resolves left to right with a stack.
- **Defensive error handling**: not enough operands for an operator, division
  by zero, a token that's neither a single digit nor one of `+ - * /`, and a
  leftover stack of more than one value at the end (e.g. `"1 2"` with no
  operator) are all treated as errors.
- **Exceptions for control flow.** `evaluate()` throws `std::runtime_error` on
  any problem; `main` only needs one `catch` block, keeping the error path
  simple and centralized.

## Design notes

- Values are stored as `long`, not `int`. The subject only constrains the
  *input* numbers to be single digits (`< 10`); intermediate and final results
  are explicitly exempt from that limit, so a slightly wider type avoids
  surprises on `*`/`+` chains without changing behavior for the given examples.
- A token is only accepted as an operand if it is **exactly one character and
  a digit**. This is what makes `"(1 + 1)"` fail correctly: the token `"(1"` is
  two characters, so it's neither a recognized operator nor a valid single-digit
  operand, and evaluation throws immediately — matching the subject's example
  output of `Error`.
- Brackets and decimal numbers are explicitly out of scope per the subject, so
  there's no tokenizer support for them — an unsupported token simply falls
  through to the "invalid token" error.

## Build & run

```
make
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
```

## Tests

`tests/run_tests.sh` builds the project and checks 12 cases: the three worked
examples from the subject (all expected to print `42`, `42`, `0`), the
bracket-error example, several hand-computed expressions, division by zero,
not enough operands, too many operands left on the stack, and an empty
expression. Run it with:

```
bash tests/run_tests.sh
```

All 12 cases pass, including exact matches for the subject's three numeric
examples and its `Error` example.
