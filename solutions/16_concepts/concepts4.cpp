#include "cpplings_test.hpp"

#include <memory>
#include <string>

int open_connections = 0;

class Connection {
public:
    virtual std::string name() const = 0;
    // Deleting a derived object through a base class pointer only runs the
    // derived destructor if the base destructor is virtual.
    virtual ~Connection() = default;
};

class DatabaseConnection : public Connection {
public:
    DatabaseConnection() { ++open_connections; }
    ~DatabaseConnection() override { --open_connections; }
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
