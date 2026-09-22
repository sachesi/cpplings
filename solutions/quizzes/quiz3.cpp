#include "cpplings_test.hpp"

#include <format>
#include <string>

template <typename Grade>
    requires std::formattable<Grade, char>
struct ReportCard {
    Grade grade;
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
