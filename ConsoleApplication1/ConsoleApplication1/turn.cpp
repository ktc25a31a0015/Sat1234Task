#include "turn.h"

Turn::Turn(std::shared_ptr<Player> player, std::shared_ptr<Slime> slime, std::shared_ptr<Goblin> goblin) {
	playerMax = 0;
	enemyMax = 0;

	player->setAttack();
	slime->setAttack();
	goblin->setAttack();

	bool isSlime = true;
	if (!slime->isDead() && !goblin->isDead()) {
		std::cout << "攻撃対象がスライムなら「s」、ゴブリンなら「g」を入力してください : ";

		char input;
		while (true) {
			std::cin >> input;

			if (input == 's' || input == 'g') break;
			else {
				std::cout << "スライムの「s」またはゴブリンの「g」を入力してください : ";
			}
		}

		std::cout << std::endl;

		if (input == 's') {
			isSlime = true;
		}
		else if (input == 'g') {
			isSlime = false;
		}
	}
	else if (!slime->isDead()) {
		isSlime = true;
	}
	else if (!goblin->isDead()) {
		isSlime = false;
	}
	
	std::shared_ptr<Character> target;
	if (isSlime) {
		target = slime;

		std::cout << "プレイヤー -> スライムへの攻撃\n";
	}
	else {
		target = goblin;

		std::cout << "プレイヤー～ゴブリンへの攻撃\n";
	}

	int playerAttack = player->getAttack();
	playerMax = playerAttack;
	std::cout << "攻撃力 : " << playerAttack << std::endl;
	target->damage(playerAttack);

	std::cout << std::endl;

	enemyAttack(player, slime);
	enemyAttack(player, goblin);

	dispHP(player);
	dispHP(slime);
	dispHP(goblin);

	std::cout << std::endl;
}

void Turn::enemyAttack(std::shared_ptr<Player> player, std::shared_ptr<Character> enemy) {
	if (!enemy->isDead()) {
		int attack = enemy->getAttack();
		if (attack > enemyMax) {
			enemyMax = attack;
		}

		std::cout << enemy->name << "～プレイヤーへの攻撃\n";
		std::cout << "攻撃力 : " << attack << std::endl;

		player->damage(attack);

		std::cout << std::endl;
	}
}

void Turn::dispHP(std::shared_ptr<Character> character) {
	if (!character->isDead()) {
		std::cout << character->name << "の残り HP : " << character->getHP() << std::endl;
	}
}