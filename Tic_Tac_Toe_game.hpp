#ifndef TIC_TAC_TOE_GAME_HPP
#define TIC_TAC_TOE_GAME_HPP

#include <iostream>

class Game_Board {
private:
    char board[9] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};

    class Sequence {
    public:
        Sequence(int i0, int i1, int i2) {sequence[0] = i0, sequence[1] = i1, sequence[2] = i2;}
        int sequence[3];
        Sequence *next = nullptr;
    };

    class Rating {
    public:
        int rating = 0;
        Sequence *next = nullptr;

    };

    Rating *priority_board[9];

public:
    Game_Board();

    void show_board();

    void show_priority_sequences();

    void show_priority_values();

    void place(int index, char symbol);

    int rate_sequence(Sequence *temp_s, char symbol);

    int AI_1(char symbol);

    bool cross_strat(char symbol);

    bool game_won(char symbol);

    bool game_tie();

    bool block_empty(int block);

    bool board_empty();

    void reset_ratings();
};

#endif