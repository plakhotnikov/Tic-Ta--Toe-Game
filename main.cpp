#include <iostream>
#include <string>
#include <vector>

class TicTacToeGame {
private:
    std::vector<std::vector<char>> field;
    char defaultSymbol = '.';
public:
    std::string player1;
    std::string player2;
    TicTacToeGame(const std::string& player1 = "player1", const std::string& player2 = "player2"): player1(player1), player2(player2) {
        field.resize(3);
        for (auto& vec : field)
            vec.resize(3, defaultSymbol);
    }
    void print() {
        std::cout << "  1 2 3\n";
        for (int i = 0; i < 3; ++i) {
            std::cout << static_cast<char>('a' + i) << " ";
            for (int j = 0; j < 3; ++j)
                std::cout << field[i][j] << " ";
            std::cout << '\n';
        }
    }

    bool set(char symbol, int x, int y) {
        if (field[x][y] == defaultSymbol) {
            field[x][y] = symbol;
            return true;
        }
        return false;
    }

    int updateGameStatus() {
        for (int i = 0; i < 3; ++i) {
            if (field[i][0] != defaultSymbol && field[i][0] == field[i][1] && field[i][0] == field[i][2])
                return (field[i][0] == 'X' ? 1 : 2);
            if (field[0][i] != defaultSymbol && field[0][i] == field[1][i] && field[0][i] == field[2][i])
                return (field[i][0] == 'X' ? 1 : 2);
        }
        if (field[0][0] != defaultSymbol && field[0][0] == field[1][1] && field[0][0] == field[2][2])
            return (field[0][0] == 'X' ? 1 : 2);
        if (field[2][0] != defaultSymbol && field[2][0] == field[1][1] && field[2][0] == field[0][2])
            return (field[2][0] == 'X' ? 1 : 2);
        return 0;
    }

    void clearField() {
        for (int i = 0; i < 3;++i) 
            for (int j = 0; j < 3; ++j)
                field[i][j] = defaultSymbol;
    }

    void start() {
        clearField();
        bool player = true; // true - X, false - O
        int gameStatus = 0; // 1 - player1 победил, 2 - player2
        int emptyCells = 9;
        while (gameStatus == 0 || emptyCells != 0) {
            bool correct_step = false;
            while (!correct_step) {
                print();
                std::cout << "Ход игрока " << (player ? player1 : player2) << ", введите координаты ячейки (пример: a1, b2, c1): "; 
                std::string cell;
                std::cin >> cell;
                if (cell.size() != 2) {
                    std::cout << "Некорректный формат ввода ячейки, повторите!\n\n";
                    std::cout << cell.size() << std::endl;
                    continue;
                }
                int x = cell[0] - 'a';
                int y = cell[1] - '1';
                if (x > 2 || y > 2 || x < 0 || y < 0) {
                    std::cout << "Некорректный формат ввода ячейки, повторите!\n\n";
                    std::cout << x << " " << y << std::endl;
                    continue;
                }
                char sym = (player ? 'X' : 'O');
                if (!set(sym,x,y)) {
                    std::cout << "Ячейка уже занята!\n\n";
                    continue;
                }
                else {
                    correct_step = true;
                    player = !player;
                }
            } 
            gameStatus = updateGameStatus();
            --emptyCells;
            if (gameStatus)
                break;
        }    
        switch (gameStatus) {
            case 0:
                std::cout << "Ничья! ";
                break;
            case 1:
                std::cout << player1 << " победил! ";
                break;
            case 2:
                std::cout << player2 << " победил! ";
        }
    }


};


int main() {
    TicTacToeGame g;
    std::string flag = "Y";
    while (flag == "Y" || flag == "y") {
        g.start();
        std::cout << "Хотите продолжить игру? (Y - да) ";
        std::cin >> flag;
    }

}