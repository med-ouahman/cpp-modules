# Exercise 00 — Bitcoin Exchange

## What this program does

`btc` reads a file of `date | value` lines, looks up the Bitcoin exchange rate for
each date in a reference database (`data.csv`), and prints `value * rate`. If a
requested date isn't in the database, it uses the **closest earlier date**
(never a later one).

## Concepts covered

- **`std::map<std::string, float>` as the required container.** A map keeps its
  keys sorted, which is exactly what's needed here: dates compare correctly as
  plain strings because they're zero-padded `YYYY-MM-DD`, so lexicographic order
  matches chronological order. This is the *only* container used in this
  exercise (per the module rule, it can't be reused in ex01/ex02).
- **`std::map::lower_bound`.** This is the core trick for "find this date, or the
  closest one before it." `lower_bound(date)` returns an iterator to the first
  entry whose key is `>= date`. If that entry's key matches exactly, that's the
  rate. Otherwise, stepping one position back (`--it`) lands on the latest
  database entry that is still *before* the requested date — which is what "use
  the lower date" means. If `lower_bound` returns `begin()` and it's not an exact
  match, the date is earlier than anything in the database, which is treated as
  an error.
- **File parsing with `std::ifstream` / `std::getline` / string streams**,
  instead of C-style `fscanf`/`*printf` (forbidden in these modules).
- **Validation logic split into small, testable static functions**
  (`isValidDate`, `parseValue`) so `main.cpp` and the class itself don't
  duplicate parsing logic.
- **Orthodox Canonical Form** (default constructor, copy constructor, copy
  assignment, destructor) on `BitcoinExchange`, as required from Module 02
  onward.
- **Exceptions (`std::runtime_error`)** for truly fatal conditions (can't open
  the database, database ends up empty), while per-line formatting/range issues
  are reported as plain printed messages and the program keeps processing the
  rest of the file — a bad line shouldn't abort the whole run.

## Design notes

- `BitcoinExchange::parseValue` returns a status enum
  (`VALUE_OK / VALUE_NOT_A_NUMBER / VALUE_NEGATIVE / VALUE_TOO_LARGE`) rather
  than throwing, because `main.cpp` needs to produce three *different* error
  messages depending on what went wrong, and exceptions would make that
  three-way branching clunkier than a simple switch on a status value.
- `isValidDate` checks the `YYYY-MM-DD` shape strictly (length 10, dashes at
  positions 4 and 7, digits everywhere else), then validates the month (1–12)
  and day (1–31, adjusted for the month and for leap years on February). This
  is why `2001-42-42` is rejected as "bad input" — month 42 doesn't exist.
- Header lines (`date | value` for the input file, anything for `data.csv`) are
  simply skipped by index (first line), not validated, since they aren't data.
- Errors are printed to **`std::cout`**, matching the subject's example
  transcript where error lines are interleaved with successful lookups in the
  same output stream.

## About `data.csv`

The real 42 subject ships an official `data.csv` (actual historical BTC/USD
exchange rates). That file isn't included in this PDF, so a **small sample
database** is provided here instead, with just enough entries to reproduce the
subject's worked example exactly (e.g. `2011-01-03 -> 0.3`, `2012-01-11 -> 7.1`).
**Replace `data.csv` with the official one from the subject before submitting.**
The program doesn't care about the file's size — it just needs a header line
followed by `date,rate` rows.

## Build & run

```
make
./btc tests/input.txt
```

## Tests

`tests/input.txt` is the exact example from the subject. `tests/run_tests.sh`
runs it plus: no argument, a missing file, an empty file, and a file full of
malformed lines (bad date shape, non-numeric value, empty value, invalid
calendar day). Run it with:

```
bash tests/run_tests.sh
```

Verified output for `tests/input.txt` against the sample `data.csv` matches the
subject's transcript line for line:

```
2011-01-03 => 3 = 0.9
2011-01-03 => 2 = 0.6
2011-01-03 => 1 = 0.3
2011-01-03 => 1.2 = 0.36
2011-01-09 => 1 = 0.32
Error: not a positive number.
Error: bad input => 2001-42-42
2012-01-11 => 1 = 7.1
Error: too large a number.
```
