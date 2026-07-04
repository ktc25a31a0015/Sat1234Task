#include <iostream>

#include "Character.h"
#include "Swordman.h"
#include "Wizard.h"
#include "Summoner.h"

int main()
{
	int turnCount = 0;

	int allyHP = 300;
	int enemyHP = 300;

	std::shared_ptr<Character> allies[3] = { std::make_shared<Swordman>(), std::make_shared<Wizard>(), std::make_shared<Summoner>() };
	std::shared_ptr<Character> enemies[3] = { std::make_shared<Swordman>(), std::make_shared<Wizard>(), std::make_shared<Summoner>() };

	while (true) {
		std::shared_ptr<Character> ally = allies[0];
		std::shared_ptr<Character> enemy = enemies[0];

		ally->actionId = 0;
		enemy->actionId = 1;

		int allyAttack = ally->attack;
		int enemyAttack = enemy->attack;

		// 互いに攻撃したとき
		if (ally->IsAttack() && enemy->IsAttack()) {
			std::cout << "互いに攻撃を選択\n";

			if (allyAttack == enemyAttack) {
				std::cout << " - 味方と敵の攻撃力が一緒のため、ドローとなりました。\n";
			}
			else if (allyAttack > enemyAttack) {
				enemyHP -= allyAttack;
				std::cout << " - 味方の攻撃力が敵を上回ったため、敵の戦力を削りました。\n";
			}
			else {
				allyHP -= enemyAttack;
				std::cout << " - 敵の攻撃力が味方を上回ったため、味方の戦力が削られました。\n";
			}
		}
		else {
			std::cout << "それぞれに別の行動を選択\n";

			// 互いのキャラクターが一緒のとき
			if (typeid(ally) == typeid(enemy)) {
				std::cout << " - 互いのキャラクターが一緒のため、ドローとなりました。\n";
			}
			else {
				if (ally->IsAttack()) {

				}
			}
		}
	}

	return 0;
}