// A tiny test framework for the cpplings exercises.
//
//     TEST(adds_numbers) {
//         CHECK_EQ(add(1, 2), 3);
//     }
//
// Including this header provides `main`, which runs every TEST in the file.
// A failed check stops the test it is in. Available checks:
//
//     CHECK(condition)
//     CHECK_EQ(actual, expected)       CHECK_NE(actual, unexpected)
//     CHECK_NEAR(actual, expected, tolerance)
//     CHECK_THROWS(expression)         CHECK_THROWS_AS(expression, ExceptionType)
//     CHECK_NOTHROW(expression)

#pragma once

#include <cmath>
#include <concepts>
#include <cstdio>
#include <exception>
#include <optional>
#include <ostream>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

namespace cpplings_test {

struct TestCase {
    const char* name;
    void (*function)();
};

inline std::vector<TestCase>& registry() {
    static std::vector<TestCase> tests;
    return tests;
}

struct Registrar {
    Registrar(const char* name, void (*function)()) { registry().push_back({name, function}); }
};

struct Failure {
    std::string message;
};

template <typename T>
concept Streamable = requires(std::ostream& os, const T& value) { os << value; };

template <typename T>
struct is_optional : std::false_type {};
template <typename T>
struct is_optional<std::optional<T>> : std::true_type {};

template <typename T>
void show_to(std::ostream& os, const T& value) {
    if constexpr (std::is_same_v<T, bool>) {
        os << (value ? "true" : "false");
    } else if constexpr (std::is_same_v<T, char>) {
        os << '\'' << value << '\'';
    } else if constexpr (std::is_convertible_v<const T&, std::string_view>) {
        os << '"' << std::string_view(value) << '"';
    } else if constexpr (std::is_same_v<T, std::nullopt_t>) {
        os << "nullopt";
    } else if constexpr (is_optional<T>::value) {
        if (value) {
            os << "optional(";
            show_to(os, *value);
            os << ')';
        } else {
            os << "nullopt";
        }
    } else if constexpr (std::is_enum_v<T>) {
        os << "enum value " << static_cast<long long>(std::to_underlying(value));
    } else if constexpr (Streamable<T>) {
        os << value;
    } else if constexpr (std::ranges::input_range<const T>) {
        os << '[';
        bool first = true;
        for (const auto& element : value) {
            os << (first ? "" : ", ");
            first = false;
            show_to(os, element);
        }
        os << ']';
    } else if constexpr (requires { value.first; value.second; }) {
        os << '(';
        show_to(os, value.first);
        os << ", ";
        show_to(os, value.second);
        os << ')';
    } else {
        os << "<value without operator<<>";
    }
}

template <typename T>
std::string show(const T& value) {
    std::ostringstream os;
    show_to(os, value);
    return os.str();
}

template <typename T>
concept Integer = std::integral<T> && !std::same_as<T, bool> && !std::same_as<T, char>;

template <typename A, typename B>
bool equal(const A& a, const B& b) {
    if constexpr (Integer<A> && Integer<B>) {
        return std::cmp_equal(a, b);
    } else {
        return a == b;
    }
}

inline std::string location(const char* file, int line) {
    return std::string(file) + ":" + std::to_string(line) + ": ";
}

inline void check(bool condition, const char* expression, const char* file, int line) {
    if (!condition) {
        throw Failure{location(file, line) + "CHECK(" + expression + ") failed"};
    }
}

template <typename A, typename B>
void check_eq(const A& actual, const B& expected, const char* actual_expr, const char* expected_expr,
              const char* file, int line) {
    if (!equal(actual, expected)) {
        throw Failure{location(file, line) + "CHECK_EQ(" + actual_expr + ", " + expected_expr + ") failed\n" +
                      "  actual: " + show(actual) + "\nexpected: " + show(expected)};
    }
}

template <typename A, typename B>
void check_ne(const A& actual, const B& unexpected, const char* actual_expr, const char* unexpected_expr,
              const char* file, int line) {
    if (equal(actual, unexpected)) {
        throw Failure{location(file, line) + "CHECK_NE(" + actual_expr + ", " + unexpected_expr + ") failed\n" +
                      "both are: " + show(actual)};
    }
}

inline void check_near(double actual, double expected, double tolerance, const char* actual_expr,
                       const char* expected_expr, const char* file, int line) {
    if (!(std::fabs(actual - expected) <= tolerance)) {
        throw Failure{location(file, line) + "CHECK_NEAR(" + actual_expr + ", " + expected_expr + ") failed\n" +
                      "  actual: " + show(actual) + "\nexpected: " + show(expected) + " ± " + show(tolerance)};
    }
}

template <typename F>
void check_throws(F&& f, const char* expression, const char* file, int line) {
    try {
        f();
    } catch (...) {
        return;
    }
    throw Failure{location(file, line) + "CHECK_THROWS(" + expression + ") failed: nothing was thrown"};
}

template <typename E, typename F>
void check_throws_as(F&& f, const char* expression, const char* type, const char* file, int line) {
    std::string what;
    try {
        f();
        what = "nothing was thrown";
    } catch (const E&) {
        return;
    } catch (const std::exception& e) {
        what = std::string("a different exception was thrown: ") + e.what();
    } catch (...) {
        what = "a different exception was thrown";
    }
    throw Failure{location(file, line) + "CHECK_THROWS_AS(" + expression + ", " + type + ") failed: " + what};
}

template <typename F>
void check_nothrow(F&& f, const char* expression, const char* file, int line) {
    std::string what;
    try {
        f();
        return;
    } catch (const std::exception& e) {
        what = e.what();
    } catch (...) {
        what = "unknown exception";
    }
    throw Failure{location(file, line) + "CHECK_NOTHROW(" + expression + ") failed: " + what};
}

inline int run_all() {
    constexpr const char* green = "\x1b[32m";
    constexpr const char* red = "\x1b[31m";
    constexpr const char* reset = "\x1b[0m";

    std::vector<TestCase>& tests = registry();
    std::vector<std::pair<const char*, std::string>> failures;

    std::printf("\nrunning %zu test%s\n", tests.size(), tests.size() == 1 ? "" : "s");
    for (const TestCase& test : tests) {
        std::printf("test %s ... ", test.name);
        std::fflush(stdout);
        std::optional<std::string> failure;
        try {
            test.function();
        } catch (const Failure& f) {
            failure = f.message;
        } catch (const std::exception& e) {
            failure = std::string("unexpected exception: ") + e.what();
        } catch (...) {
            failure = "unexpected exception of an unknown type";
        }
        if (failure) {
            std::printf("%sFAILED%s\n", red, reset);
            failures.emplace_back(test.name, *failure);
        } else {
            std::printf("%sok%s\n", green, reset);
        }
    }

    if (!failures.empty()) {
        std::printf("\nfailures:\n");
        for (const auto& [name, message] : failures) {
            std::printf("\n---- %s ----\n%s\n", name, message.c_str());
        }
    }

    std::size_t passed = tests.size() - failures.size();
    std::printf("\ntest result: %s. %zu passed; %zu failed\n\n",
                failures.empty() ? "\x1b[32mok\x1b[0m" : "\x1b[31mFAILED\x1b[0m", passed, failures.size());
    return failures.empty() ? 0 : 1;
}

} // namespace cpplings_test

#define CPPLINGS_TEST_CONCAT_(a, b) a##b
#define CPPLINGS_TEST_CONCAT(a, b) CPPLINGS_TEST_CONCAT_(a, b)

#define TEST(name)                                                                                               \
    static void CPPLINGS_TEST_CONCAT(cpplings_test_, name)();                                                    \
    static const ::cpplings_test::Registrar CPPLINGS_TEST_CONCAT(cpplings_registrar_, name){                     \
        #name, &CPPLINGS_TEST_CONCAT(cpplings_test_, name)};                                                     \
    static void CPPLINGS_TEST_CONCAT(cpplings_test_, name)()

#define CHECK(condition) ::cpplings_test::check(static_cast<bool>(condition), #condition, __FILE__, __LINE__)

#define CHECK_EQ(actual, expected) \
    ::cpplings_test::check_eq((actual), (expected), #actual, #expected, __FILE__, __LINE__)

#define CHECK_NE(actual, unexpected) \
    ::cpplings_test::check_ne((actual), (unexpected), #actual, #unexpected, __FILE__, __LINE__)

#define CHECK_NEAR(actual, expected, tolerance) \
    ::cpplings_test::check_near((actual), (expected), (tolerance), #actual, #expected, __FILE__, __LINE__)

#define CHECK_THROWS(expression) \
    ::cpplings_test::check_throws([&] { static_cast<void>(expression); }, #expression, __FILE__, __LINE__)

#define CHECK_THROWS_AS(expression, exception_type)                                                              \
    ::cpplings_test::check_throws_as<exception_type>([&] { static_cast<void>(expression); }, #expression,        \
                                                     #exception_type, __FILE__, __LINE__)

#define CHECK_NOTHROW(expression) \
    ::cpplings_test::check_nothrow([&] { static_cast<void>(expression); }, #expression, __FILE__, __LINE__)

int main() {
    return ::cpplings_test::run_all();
}
