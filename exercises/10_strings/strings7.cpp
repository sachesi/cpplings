#include "cpplings_test.hpp"

#include <string_view>

// TODO: Both functions search the whole name, so they are fooled by names like
// "cat.png.txt". Check only the beginning or the end of the name instead.

bool is_image(std::string_view file_name) {
    return file_name.find(".png") != std::string_view::npos ||
           file_name.find(".jpg") != std::string_view::npos;
}

// Hidden files start with a dot.
bool is_hidden(std::string_view file_name) {
    return file_name.find('.') != std::string_view::npos;
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
