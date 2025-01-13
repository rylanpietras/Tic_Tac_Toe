#include "Tic_Tac_Toe_game.hpp"

int main() {
    Game_Board g1;

    char p1_symbol;
    char p2_symbol;
    std::cout << "\n" << "Play as X or O? (Type X or O): ";
    std::cin >> p1_symbol;
    while (p1_symbol != 'X' && p1_symbol != 'O' && p1_symbol != 'x' && p1_symbol != 'o') {
        std::cout << "Error: Please type either X or O: ";
        std::cin >> p1_symbol;
    }
    if (p1_symbol == 'X' || p1_symbol == 'x') {
        p1_symbol = 'X';
        p2_symbol = 'O';
    }
    else {
        p1_symbol = 'O';
        p2_symbol = 'X';
    }

    char first_or_sec;
    std::cout << "Would you like to go first or second? (Type 1 or 2): ";
    std::cin >> first_or_sec;
    while (first_or_sec != '1' && first_or_sec != '2') {
        std::cout << "Error: Type 1 or 2: ";
        std::cin >> first_or_sec;
    }
    bool p1_turn = true;
    bool do_cross_strat = false;
    if (first_or_sec == '2') {
        p1_turn = false;
        do_cross_strat = true;
    }

    bool p1_win = false;
    bool p2_win = false;
    bool tie = false;
    int p1_place = -1;
    while ((!p1_win) && (!p2_win) && (!tie)) {
        g1.show_board();

        if (p1_turn) {
            std::cout << p1_symbol << "'s Turn: ";
            std::cin >> p1_place;
            while (p1_place < 0 || p1_place > 8 || !g1.block_empty(p1_place)) {
                std::cout << "Error: Input occupied or not in range" << std::endl;
                std::cout << p1_symbol << "'s Turn: ";
                std::cin >> p1_place;
            }

            g1.place(p1_place, p1_symbol);

            p1_turn = false;
        }
        else {
            std::cout << p2_symbol << "'s Turn..." << std::endl;

            if (do_cross_strat) {
                if (g1.board_empty()) {
                    g1.place(0, p2_symbol);
                }
                else if (!g1.block_empty(4)) {
                    g1.place(8, p2_symbol);
                    do_cross_strat = false;
                }
                else {
                    if (g1.block_empty(1) && g1.block_empty(2) && g1.block_empty(5)) {
                        g1.place(2, p2_symbol);
                        do_cross_strat = false;
                    }
                    else {
                        g1.place(6, p2_symbol);
                        do_cross_strat = false;
                    }
                }
            }
            else if (g1.cross_strat(p2_symbol)) {
                g1.place(1, p2_symbol); // Use random number later
            }
            else {
                g1.place(g1.AI_1(p2_symbol), p2_symbol);
            }

            p1_turn = true;
        }

        p1_win = g1.game_won(p1_symbol);
        p2_win = g1.game_won(p2_symbol);
        tie = g1.game_tie();
    }

    g1.show_board();

    if (p1_win) {
        std::cout << p1_symbol << " Wins!!!\n" << std::endl;
    }
    else if (p2_win) {
        std::cout << p2_symbol << " Wins!!!\n" << std::endl;
    }
    else {
        std::cout << "Tied Game - No Player Wins\n" << std::endl;
    }

    return 0;
}