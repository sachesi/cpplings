#pragma once

#include <cstddef>
#include <iterator>
#include <optional>
#include <string_view>

struct EmbeddedFile {
    std::string_view path;
    std::string_view content;
};

extern const EmbeddedFile embedded_files[];
extern const std::size_t embedded_files_count;

std::optional<std::string_view> embedded_file(std::string_view path);
