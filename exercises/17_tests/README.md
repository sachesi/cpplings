# Tests

Tests make sure that code does what it should. Many exercises in cpplings are
checked with tests; now it's your turn to write some.

The tests use the small framework in `include/cpplings_test.hpp`. Real projects
usually use a framework like GoogleTest, Catch2 or doctest, which offer the same
ideas: named test cases containing checks, and a report of what failed.

- `TEST(name) { ... }` defines a test case.
- `CHECK(condition)` fails if the condition is false.
- `CHECK_EQ(actual, expected)` fails if the values differ and shows both.
- `CHECK_THROWS_AS(expression, type)` fails unless the expression throws `type`.

## Further information

- [The test framework used by cpplings](../../include/cpplings_test.hpp)
- [GoogleTest primer](https://google.github.io/googletest/primer.html)
- [Catch2 tutorial](https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md)
