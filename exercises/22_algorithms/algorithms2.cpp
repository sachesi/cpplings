// Let's define a simple model to track cpplings' exercises progress. Progress
// will be modelled using a map. The name of the exercise is the key and the
// progress is the value.

#include "cpplings_test.hpp"

#include <algorithm>
#include <map>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

enum class Progress { None, Some, Complete };

using ProgressMap = std::map<std::string, Progress>;

int count_for(const ProgressMap& map, Progress value) {
    int count = 0;
    for (const auto& [name, progress] : map) {
        if (progress == value) {
            ++count;
        }
    }
    return count;
}

// TODO: Implement the functionality of `count_for` but without a loop. Use an
// algorithm from `std::ranges` and the view `std::views::values`.
int count_algorithm(const ProgressMap& map, Progress value) {
    return 0;
}

int count_collection_for(const std::vector<ProgressMap>& collection, Progress value) {
    int count = 0;
    for (const ProgressMap& map : collection) {
        count += count_for(map, value);
    }
    return count;
}

// TODO: Implement the functionality of `count_collection_for` but without a
// loop. Use `std::transform_reduce` from <numeric> together with
// `count_algorithm`.
int count_collection_algorithm(const std::vector<ProgressMap>& collection, Progress value) {
    return 0;
}

std::vector<ProgressMap> get_vec_map() {
    return {
        {{"variables1", Progress::Complete},
         {"functions1", Progress::Complete},
         {"structs1", Progress::Some},
         {"enums1", Progress::None}},
        {{"variables2", Progress::Complete},
         {"functions2", Progress::Some},
         {"structs2", Progress::None},
         {"enums2", Progress::None}},
    };
}

TEST(count_complete) {
    ProgressMap map = get_vec_map()[0];
    CHECK_EQ(count_algorithm(map, Progress::Complete), 2);
}

TEST(count_equals_for) {
    ProgressMap map = get_vec_map()[1];
    for (Progress progress : {Progress::Complete, Progress::Some, Progress::None}) {
        CHECK_EQ(count_algorithm(map, progress), count_for(map, progress));
    }
}

TEST(count_collection_complete) {
    CHECK_EQ(count_collection_algorithm(get_vec_map(), Progress::Complete), 3);
}

TEST(count_collection_equals_for) {
    auto collection = get_vec_map();
    for (Progress progress : {Progress::Complete, Progress::Some, Progress::None}) {
        CHECK_EQ(count_collection_algorithm(collection, progress), count_collection_for(collection, progress));
    }
}
