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

        // `operator[]` inserts a zero-initialized entry for new teams.
        TeamScores& team_1 = scores[team_1_name];
        team_1.goals_scored += team_1_goals;
        team_1.goals_conceded += team_2_goals;

        TeamScores& team_2 = scores[team_2_name];
        team_2.goals_scored += team_2_goals;
        team_2.goals_conceded += team_1_goals;
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
