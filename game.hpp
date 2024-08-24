#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"


class TicTacToeGame {
private:
    std::vector<std::vector<char>> field;
	Player* player1;
	Player* player2;
public:
	TicTacToeGame(Player* p1, Player* p2): player1(p1), player2(p2) {
        field.resize(3);
        for (auto& vec : field)
            vec.resize(3, '.');
		player1->field = &field;
		player2->field = &field;
    }


    int updateGameStatus() {
        for (int i = 0; i < 3; ++i) {
            if (field[i][0] != '.' && field[i][0] == field[i][1] && field[i][0] == field[i][2])
                return (field[i][0] == 'X' ? 1 : 2);
            if (field[0][i] != '.' && field[0][i] == field[1][i] && field[0][i] == field[2][i])
                return (field[i][0] == 'X' ? 1 : 2);
        }
        if (field[0][0] != '.' && field[0][0] == field[1][1] && field[0][0] == field[2][2])
            return (field[0][0] == 'X' ? 1 : 2);
        if (field[2][0] != '.' && field[2][0] == field[1][1] && field[2][0] == field[0][2])
            return (field[2][0] == 'X' ? 1 : 2);
        return 0;
    }

    void clearField() {
        for (int i = 0; i < 3;++i) 
            for (int j = 0; j < 3; ++j)
                field[i][j] = '.';
    }

	void show_winner() {
		std::cout << "  1 2 3\n";
     	for (int i = 0; i < 3; ++i) {
			std::cout << static_cast<char>('a' + i) << " ";
			for (int j = 0; j < 3; ++j) {
				std::cout << field[i][j] << " ";
			}
			std::cout << '\n';
		}
	}

    void start() {
        clearField();
        bool player = true; // true - X, false - O
        int gameStatus = 0; // 1 - player1 победил, 2 - player2
        int emptyCells = 9;
        while (gameStatus == 0 && emptyCells != 0) {
			std::pair<int,int> cell;
			char sym;
            if (player) {
				cell = player1->choose_cell();
				sym = 'X';
			}
			else {
				cell = player2->choose_cell();
				sym = 'O';
			}
			field[cell.first][cell.second] = sym;
			player ^= true;

			gameStatus = updateGameStatus();
            --emptyCells;
            if (gameStatus)
                break;
        }    
        switch (gameStatus) {
            case 0:
                std::cout << "Ничья!\n";
                break;
            case 1:
                std::cout << player1->name << " победил!\n";
                break;
            case 2:
                std::cout << player2->name << " победил!\n";
        }
		show_winner();
    }


};

#endif
