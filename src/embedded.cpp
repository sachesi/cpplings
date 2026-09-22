#include "embedded.hpp"

#include <algorithm>
#include <span>

std::optional<std::string_view> embedded_file(std::string_view path) {
    std::span files{embedded_files, embedded_files_count};
    auto it = std::ranges::lower_bound(files, path, {}, &EmbeddedFile::path);
    if (it == files.end() || it->path != path) {
        return std::nullopt;
    }
    return it->content;
}
