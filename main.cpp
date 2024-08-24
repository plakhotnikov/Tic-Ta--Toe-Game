#include "player.hpp"

#include <iostream>
#include <string>
#include <vector>

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


void changePlayers(Player*& p1, Player*& p2) {
	if (p1)
		delete p1;
	if (p2)
		delete p2;
	std::string name1;
	std::string name2;
 	std::cout << "Введите имя первого игрока (если хотите, что бы первый игрок был ботом, введите bot\n";

	std::cin >> name1;
	if (name1 == "bot")
		p1 = new Bot('X');
	else
		p1 = new Player(name1, 'X');

	
	std::cout << "Введите имя второго игрока (если хотите, что бы первый игрок был ботом, введите bot\n";
	std::cin >> name2;
    if (name2 == "bot")
		p2 = new Bot('O');
	else
		p2 = new Player(name2, 'O');
}



int main() {
	std::string flag = "Y";
	Player* p1; 
	Player* p2;
	changePlayers(p1,p2);
	while (flag == "Y" || flag == "y") {
		
	    TicTacToeGame g(p1,p2);
		g.start();

		std::cout << "Начать заново? (Y - да)\n";
		std::cin >> flag;
	}
}
