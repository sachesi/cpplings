#include "cpplings_test.hpp"

#include <memory>
#include <string>
#include <utility>
#include <vector>

struct Book {
    std::string title;
};

class Library {
public:
    // TODO: Fix the compiler error. A `std::unique_ptr` can't be copied.
    void add(std::unique_ptr<Book> book) {
        books_.push_back(book);
    }

    const std::vector<std::unique_ptr<Book>>& books() const { return books_; }

private:
    std::vector<std::unique_ptr<Book>> books_;
};

TEST(library_owns_the_book) {
    Library library;
    auto book = std::make_unique<Book>("The C++ Programming Language");

    // TODO: Fix the compiler error here as well.
    library.add(book);

    CHECK_EQ(library.books().size(), 1);
    CHECK_EQ(library.books()[0]->title, "The C++ Programming Language");
    // The book was moved into the library.
    CHECK(book == nullptr);
}
