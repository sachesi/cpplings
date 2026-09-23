#include "cpplings_test.hpp"

#include <memory>
#include <string>

// Counts how many `Connection` objects are alive.
int open_connections = 0;

class Connection {
public:
    virtual std::string name() const = 0;
    // TODO: The tests show that closing connections doesn't work. Find out why.
    // The compiler warns about it.
    ~Connection() = default;
};

class DatabaseConnection : public Connection {
public:
    DatabaseConnection() { ++open_connections; }
    ~DatabaseConnection() { --open_connections; }
    std::string name() const override { return "database"; }
};

TEST(connection_is_closed) {
    {
        std::unique_ptr<Connection> connection = std::make_unique<DatabaseConnection>();
        CHECK_EQ(connection->name(), "database");
        CHECK_EQ(open_connections, 1);
    }
    CHECK_EQ(open_connections, 0);
}
