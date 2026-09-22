// This quiz tests:
// - Templates
// - Concepts
//
// An imaginary magical school has a new report card generation system written
// in C++! Currently, the system only supports creating report cards where the
// student's grade is represented numerically (e.g. 1.0 -> 5.5). However, the
// school also issues alphabetical grades (A+ -> F-) and needs to be able to
// print both types of report card!
//
// Make the necessary code changes in the struct `ReportCard` to support
// alphabetical report cards in addition to numerical ones. Only types that
// `std::format` can format should be accepted as grades: constrain the template
// with the standard concept `std::formattable<T, char>`.

#include "cpplings_test.hpp"

#include <format>
#include <string>

// TODO: Adjust the struct as described above.
struct ReportCard {
    double grade;
    std::string student_name;
    int student_age;

    std::string print() const {
        return std::format("{} ({}) - achieved a grade of {}", student_name, student_age, grade);
    }
};

struct Unprintable {};

template <typename T>
concept AcceptedGrade = requires { typename ReportCard<T>; };

TEST(generate_numeric_report_card) {
    ReportCard<double> report_card{2.1, "Tom Wriggle", 12};
    CHECK_EQ(report_card.print(), "Tom Wriggle (12) - achieved a grade of 2.1");
}

TEST(generate_alphabetic_report_card) {
    ReportCard<std::string> report_card{"A+", "Gary Plotter", 11};
    CHECK_EQ(report_card.print(), "Gary Plotter (11) - achieved a grade of A+");
}

TEST(only_printable_grades) {
    static_assert(AcceptedGrade<int>);
    static_assert(!AcceptedGrade<Unprintable>);
}
