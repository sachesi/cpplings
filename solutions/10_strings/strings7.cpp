#include "cpplings_test.hpp"

#include <string_view>

bool is_image(std::string_view file_name) {
    return file_name.ends_with(".png") || file_name.ends_with(".jpg");
}

bool is_hidden(std::string_view file_name) {
    return file_name.starts_with('.');
}

TEST(images) {
    CHECK(is_image("cat.png"));
    CHECK(is_image("holiday.jpg"));
    CHECK(!is_image("notes.txt"));
    CHECK(!is_image("cat.png.txt"));
}

TEST(hidden_files) {
    CHECK(is_hidden(".bashrc"));
    CHECK(!is_hidden("cat.png"));
    CHECK(!is_hidden("README"));
}
