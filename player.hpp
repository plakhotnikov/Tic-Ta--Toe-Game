#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>

class Player {
public:
	std::string name;
	char symbol;
	char opponent_symbol;
  	const std::vector<std::vector<char>>* field;
	Player() = default;
	Player(const std::string& name, char symbol): name(name), symbol(symbol) {
    	opponent_symbol = (symbol == 'X' ? 'O' : 'X');
	}
	void print() {
		std::cout << "  1 2 3\n";
     	for (int i = 0; i < 3; ++i) {
			std::cout << static_cast<char>('a' + i) << " ";
         	for (int j = 0; j < 3; ++j) {
             	std::cout << (*field)[i][j] << " ";
			}
			std::cout << '\n';
		}
	}

	virtual std::pair<int,int> choose_cell() {
		print();
		bool correct_input = false;
		int x = -1;
		int y = -1;
		while (!correct_input) {
			std::cout << "Ход " << name << " (" << symbol << ")" << ", выберите клетку (например: a1,a2,b3)\n";
    	 	std::string cell;
			std::cin >> cell;
			if (cell.size() != 2) {
				std::cout << "Некорректный формат ввода\n\n";
				continue;
			}
			x = cell[0] - 'a';
			y = cell[1] - '1';
			if (x > 2 || y > 2 || x < 0 || y < 0) {
				std::cout << "Выход за пределы поля\n\n";
				continue;
			}
			if ((*field)[x][y] != '.') {
				std::cout << "Клетка занята!\n\n";
				continue;
			}
			correct_input = true;
		}
		return std::make_pair(x,y);
	}
};


class Bot : public Player {
public:
	Bot(char sym) {
		name = "bot";
		symbol = sym;
    	opponent_symbol = (symbol == 'X' ? 'O' : 'X');
	}
	std::pair<int,int> choose_cell() override {
		if ((*field)[1][1] == '.')
			return std::make_pair(1,1);
		for (int i = 0; i < 3; ++i) {
			int cnt = 0;
         	for (int j = 0; j < 3; ++j) {
             	if ((*field)[i][j] == symbol)
					++cnt;
			}
			if (cnt == 2) {
				for (int j = 0; j < 3; ++j) {
             		if ((*field)[i][j] == '.')
						return std::make_pair(i,j);
				}
			}
			cnt = 0;
			for (int j = 0; j < 3; ++j) {
             	if ((*field)[j][i] == symbol)
					++cnt;
			}
			if (cnt == 2) {
				for (int j = 0; j < 3; ++j) {
             		if ((*field)[j][i] == '.')
						return std::make_pair(j,i);
				}
			}
		}
		int cnt = 0;
		for (int i = 0; i < 3; ++i) {
         	if ((*field)[i][i] == symbol)
				++cnt;
		}
		if (cnt == 2) {
			for (int i = 0; i < 3; ++i) {
				if ((*field)[i][i] == '.')
					return std::make_pair(i,i);
			}
		}
		cnt = 0;
        for (int i = 0; i < 3; ++i) {
         	if ((*field)[i][2 - i] == symbol)
				++cnt;
		}
		if (cnt == 2) {
			for (int i = 0; i < 3; ++i) {
				if ((*field)[i][2 - i] == '.')
					return std::make_pair(i,2 - i);
			}
		}

        for (int i = 0; i < 3; ++i) {
			int cnt = 0;
         	for (int j = 0; j < 3; ++j) {
             	if ((*field)[i][j] == opponent_symbol)
					++cnt;
			}
			if (cnt == 2) {
				for (int j = 0; j < 3; ++j) {
             		if ((*field)[i][j] == '.')
						return std::make_pair(i,j);
				}
			}
			cnt = 0;
			for (int j = 0; j < 3; ++j) {
             	if ((*field)[j][i] == opponent_symbol)
					++cnt;
			}
			if (cnt == 2) {
				for (int j = 0; j < 3; ++j) {
             		if ((*field)[j][i] == '.')
						return std::make_pair(j,i);
				}
			}
		}
		cnt = 0;
		for (int i = 0; i < 3; ++i) {
         	if ((*field)[i][i] == opponent_symbol)
				++cnt;
		}
		if (cnt == 2) {
			for (int i = 0; i < 3; ++i) {
				if ((*field)[i][i] == '.')
					return std::make_pair(i,i);
			}
		}
		cnt = 0;
        for (int i = 0; i < 3; ++i) {
         	if ((*field)[i][2 - i] == opponent_symbol)
				++cnt;
		}
		if (cnt == 2) {
			for (int i = 0; i < 3; ++i) {
				if ((*field)[i][2 - i] == '.')
					return std::make_pair(i,2 - i);
			}
		}
		if ((*field)[0][0] == '.')
			return std::make_pair(0,0);
		else if ((*field)[2][0] == '.')
			return std::make_pair(2,0);
        else if ((*field)[2][2] == '.')
			return std::make_pair(2,2);
        else if ((*field)[0][2] == '.')
			return std::make_pair(0,2);
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				if ((*field)[i][j] == '.')
					return std::make_pair(i,j);
			}
		}
		return std::make_pair(-1,-1);
	}
};
#endif
