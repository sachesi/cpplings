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
    void add(std::unique_ptr<Book> book) {
        books_.push_back(std::move(book));
    }

    const std::vector<std::unique_ptr<Book>>& books() const { return books_; }

private:
    std::vector<std::unique_ptr<Book>> books_;
};

TEST(library_owns_the_book) {
    Library library;
    auto book = std::make_unique<Book>("The C++ Programming Language");

    library.add(std::move(book));

    CHECK_EQ(library.books().size(), 1);
    CHECK_EQ(library.books()[0]->title, "The C++ Programming Language");
    CHECK(book == nullptr);
}
