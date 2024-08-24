#include "player.hpp"
#include "game.hpp"
#include <iostream>
#include <string>
#include <vector>



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
