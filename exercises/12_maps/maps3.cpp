// A list of scores (one per line) of a soccer match is given. Each line is of
// the form "<team_1_name>,<team_2_name>,<team_1_goals>,<team_2_goals>"
// Example: "England,France,4,2" (England scored 4 goals, France 2).
//
// You have to build a scores table containing the name of the team, the total
// number of goals the team scored, and the total number of goals the team
// conceded.

#include "cpplings_test.hpp"

#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

struct TeamScores {
    int goals_scored = 0;
    int goals_conceded = 0;
};

std::unordered_map<std::string, TeamScores> build_scores_table(std::string_view results) {
    // The name of the team is the key and its associated struct is the value.
    std::unordered_map<std::string, TeamScores> scores;

    std::istringstream lines{std::string(results)};
    for (std::string line; std::getline(lines, line);) {
        std::istringstream fields(line);
        std::string team_1_name, team_2_name, team_1_score, team_2_score;
        std::getline(fields, team_1_name, ',');
        std::getline(fields, team_2_name, ',');
        std::getline(fields, team_1_score, ',');
        std::getline(fields, team_2_score, ',');
        int team_1_goals = std::stoi(team_1_score);
        int team_2_goals = std::stoi(team_2_score);

        // TODO: Populate the scores table with the extracted details.
        // Keep in mind that goals scored by team 1 will be the number of goals
        // conceded by team 2. Similarly, goals scored by team 2 will be the
        // number of goals conceded by team 1.
    }

    return scores;
}

constexpr std::string_view RESULTS = "England,France,4,2\n"
                                     "France,Italy,3,1\n"
                                     "Poland,Spain,2,0\n"
                                     "Germany,England,2,1\n"
                                     "England,Spain,1,0\n";

TEST(build_scores) {
    auto scores = build_scores_table(RESULTS);
    CHECK_EQ(scores.size(), 6);
    for (const char* team : {"England", "France", "Germany", "Italy", "Poland", "Spain"}) {
        CHECK(scores.contains(team));
    }
}

TEST(validate_team_score_1) {
    auto scores = build_scores_table(RESULTS);
    TeamScores team = scores.at("England");
    CHECK_EQ(team.goals_scored, 6);
    CHECK_EQ(team.goals_conceded, 4);
}

TEST(validate_team_score_2) {
    auto scores = build_scores_table(RESULTS);
    TeamScores team = scores.at("Spain");
    CHECK_EQ(team.goals_scored, 0);
    CHECK_EQ(team.goals_conceded, 3);
}
