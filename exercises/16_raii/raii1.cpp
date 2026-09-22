#include "cpplings_test.hpp"

#include <stdexcept>
#include <string>
#include <utility>

// Counts how many files are open.
int open_files = 0;

class File {
public:
    explicit File(std::string name) : name_(std::move(name)) {
        ++open_files;
    }

    // TODO: Add a destructor that closes the file by decrementing `open_files`.

    // Copying would close the same file twice.
    File(const File&) = delete;
    File& operator=(const File&) = delete;

    const std::string& name() const { return name_; }

private:
    std::string name_;
};

TEST(closed_at_end_of_scope) {
    {
        File file("notes.txt");
        CHECK_EQ(open_files, 1);
    }
    CHECK_EQ(open_files, 0);
}

TEST(closed_when_an_exception_is_thrown) {
    try {
        File file("report.txt");
        throw std::runtime_error("disk full");
    } catch (const std::runtime_error&) {
    }
    CHECK_EQ(open_files, 0);
}
