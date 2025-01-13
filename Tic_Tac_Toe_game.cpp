#include "Tic_Tac_Toe_game.hpp"

Game_Board::Game_Board() {
    Rating *b0 = new Rating;
    Rating *b1 = new Rating;
    Rating *b2 = new Rating;
    Rating *b3 = new Rating;
    Rating *b4 = new Rating;
    Rating *b5 = new Rating;
    Rating *b6 = new Rating;
    Rating *b7 = new Rating;
    Rating *b8 = new Rating;

    priority_board[0] = b0;
    priority_board[1] = b1;
    priority_board[2] = b2;
    priority_board[3] = b3;
    priority_board[4] = b4;
    priority_board[5] = b5;
    priority_board[6] = b6;
    priority_board[7] = b7;
    priority_board[8] = b8;

    Sequence *b0_s1 = new Sequence(0, 1, 2);
    Sequence *b0_s2 = new Sequence(0, 4, 8);
    Sequence *b0_s3 = new Sequence(0, 3, 6);
    b0->next = b0_s1;
    b0_s1->next = b0_s2;
    b0_s2->next = b0_s3;

    Sequence *b1_s1 = new Sequence(0, 1, 2);
    Sequence *b1_s2 = new Sequence(1, 4, 7);
    b1->next = b1_s1;
    b1_s1->next = b1_s2;

    Sequence *b2_s1 = new Sequence(0, 1, 2);
    Sequence *b2_s2 = new Sequence(2, 4, 6);
    Sequence *b2_s3 = new Sequence(2, 5, 8);
    b2->next = b2_s1;
    b2_s1->next = b2_s2;
    b2_s2->next = b2_s3;

    Sequence *b3_s1 = new Sequence(0, 3, 6);
    Sequence *b3_s2 = new Sequence(3, 4, 5);
    b3->next = b3_s1;
    b3_s1->next = b3_s2;

    Sequence *b4_s1 = new Sequence(0, 4, 8);
    Sequence *b4_s2 = new Sequence(2, 4, 6);
    Sequence *b4_s3 = new Sequence(3, 4, 5);
    Sequence *b4_s4 = new Sequence(1, 4, 7);
    b4->next = b4_s1;
    b4_s1->next = b4_s2;
    b4_s2->next = b4_s3;
    b4_s3->next = b4_s4;

    Sequence *b5_s1 = new Sequence(2, 5, 8);
    Sequence *b5_s2 = new Sequence(3, 4, 5);
    b5->next = b5_s1;
    b5_s1->next = b5_s2;

    Sequence *b6_s1 = new Sequence(0, 3, 6);
    Sequence *b6_s2 = new Sequence(2, 4, 6);
    Sequence *b6_s3 = new Sequence(6, 7, 8);
    b6->next = b6_s1;
    b6_s1->next = b6_s2;
    b6_s2->next = b6_s3;

    Sequence *b7_s1 = new Sequence(1, 4, 7);
    Sequence *b7_s2 = new Sequence(6, 7, 8);
    b7->next = b7_s1;
    b7_s1->next = b7_s2;

    Sequence *b8_s1 = new Sequence(0, 4, 8);
    Sequence *b8_s2 = new Sequence(2, 5, 8);
    Sequence *b8_s3 = new Sequence(6, 7, 8);
    b8->next = b8_s1;
    b8_s1->next = b8_s2;
    b8_s2->next = b8_s3;
}

void Game_Board::show_board() {
    std::cout << std::endl;
    for (int i = 0; i < 9; i += 3) {
        std::cout << "---------------";
        std::cout << std::endl;
        for (int j = 0; j < 3; ++j) {
            std::cout << " | " << board[i + j];
        }
        std::cout << " | " << std::endl;
    } 
    std::cout << "---------------\n";
    std::cout << std::endl;
}

void Game_Board::show_priority_sequences() {
    Rating *temp_r;
    Sequence *temp_s;
    std::cout << std::endl; 
    for (int i = 0; i < 9; ++i) {
        temp_r = priority_board[i];
        temp_s = temp_r->next;

        while (temp_s != nullptr) {
            for (int j = 0; j < 3; ++j) {
                std::cout << " " << temp_s->sequence[j];
            }
            temp_s = temp_s->next;
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

void Game_Board::show_priority_values() {
    for (int i = 0; i < 9; i = i + 3) {
        std::cout << std::endl;
        for (int j = 0; j < 3; ++j) {
            std::cout << " " << priority_board[i + j]->rating;
        }
    }
    std::cout << "\n" << std::endl;
}

void Game_Board::place(int block, char symbol) {
    if (block < 0 || block > 8) {
        std::cout << "Error: block not in range for X" << std::endl;
        return;
    }

    board[block] = symbol;
}

int Game_Board::rate_sequence(Sequence *temp_s, char symbol) {
    int my_sym = 0;
    int other_sym = 0;
    for (int i = 0; i < 3; ++i) {
        if (board[temp_s->sequence[i]] == ' ') {
            continue;
        }
        else if (board[temp_s->sequence[i]] == symbol) {
            ++my_sym;
        }
        else {
            ++other_sym;
        }
    }

    switch (my_sym) {
        case 0:
            switch (other_sym) {
                case 0:
                    return 1;
                case 1:
                    return 4;
                case 2:
                    return 13;
                default:
                    std::cout << "ERROR" << std::endl;
                    return -100;
            }
        case 1:
            switch (other_sym) {
                case 0:
                    return 4;
                case 1:
                    return 1;
                default:
                    std::cout << "ERROR" << std::endl;
                    return -100;
            }
        case 2:
            return 40;
        default:
            std::cout << "ERROR" << std::endl;
            return -100;
    }
}

int Game_Board::AI_1(char symbol) {
    reset_ratings();

    for (int i = 0; i < 9; ++i) {
        if (board[i] != ' ') {
            continue;
        }

        auto temp_r = priority_board[i];
        auto temp_s = temp_r->next;

        while (temp_s != nullptr) {
            temp_r->rating += rate_sequence(temp_s, symbol);
            temp_s = temp_s->next;
        }
    }

    int largest_index = 0;
    int largest_value = priority_board[0]->rating;
    for (int i = 1; i < 9; ++i) {
        if (priority_board[i]->rating > largest_value) { // Use random number later for equal priorities
            largest_index = i;
            largest_value = priority_board[i]->rating;
        }
    }

    return largest_index;
}

bool Game_Board::cross_strat(char symbol) {
    if (!block_empty(0) && block_empty(1) && block_empty(2) && block_empty(3) && !block_empty(4) && block_empty(5) && block_empty(6) && block_empty(7) && !block_empty(8)) {
        if (board[4] == symbol && board[0] != symbol && board[8] != symbol) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (block_empty(0) && block_empty(1) && !block_empty(2) && block_empty(3) && !block_empty(4) && block_empty(5) && !block_empty(6) && block_empty(7) && block_empty(8)) {
        if (board[4] == symbol && board[2] != symbol && board[6] != symbol) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Game_Board::game_won(char symbol) {
    for (int i = 0; i < 9; ++i) {
        auto temp_s = priority_board[i]->next;

        while (temp_s != nullptr) {
            if ((board[temp_s->sequence[0]] == symbol) && (board[temp_s->sequence[1]] == symbol) && (board[temp_s->sequence[2]] == symbol)) {
                return true;
            }

            temp_s = temp_s->next;
        }
    }

    return false;
}

bool Game_Board::game_tie() {
    for (auto i : board) {
        if (i == ' ') {
            return false;
        }
    }

    return true;
}

bool Game_Board::block_empty(int block) {
    if (block < 0 || block > 8) {
        std::cout << "Block out of Range" << std::endl;
        return false;
    }

    if (board[block] == ' ') {
        return true;
    }
    else {
        return false;
    }
}

bool Game_Board::board_empty() {
    for (char i : board) {
        if (i != ' ') {
            return false;
        }
    }

    return true;
}

void Game_Board::reset_ratings() {
    for(auto temp_r : priority_board) {
        temp_r->rating = 0;
    }
}