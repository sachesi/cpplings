#include "cpplings_test.hpp"

#include <cstddef>
#include <vector>

using Board = std::vector<std::vector<char>>;

// TODO: Create a board with `rows` rows. Every row should hold `columns`
// characters, all of them '.'. The rows are empty so far.
Board make_board(std::size_t rows, std::size_t columns) {
    Board board(rows);
    return board;
}

TEST(board_size) {
    Board board = make_board(3, 4);
    CHECK_EQ(board.size(), 3);
    CHECK_EQ(board[0].size(), 4);
    CHECK_EQ(board[2].size(), 4);
}

TEST(board_starts_empty) {
    Board board = make_board(2, 2);
    Board expected = {{'.', '.'}, {'.', '.'}};
    CHECK_EQ(board, expected);
}

TEST(placing_a_piece) {
    Board board = make_board(3, 4);
    board[1][3] = '#';
    CHECK_EQ(board[1][3], '#');
    CHECK_EQ(board[1][2], '.');
}
