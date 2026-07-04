#include <iostream>

#include "character.h"
#include "turn.h"

int main()
{
	std::shared_ptr<Player> player(new Player);
	player->setName("プレイヤー");
	std::shared_ptr<Slime> slime(new Slime);
	slime->setName("スライム");
	std::shared_ptr<Goblin> goblin(new Goblin);
	goblin->setName("ゴブリン");

	int turnCount = 0;

	int playerMax = 0;
	int enemyMax = 0;

	while (true) {
		turnCount++;

		std::cout << turnCount << " ターンスタート\n";

		Turn turn(player, slime, goblin);

		if (turn.playerMax > playerMax) {
			playerMax = turn.playerMax;
		}

		if (turn.enemyMax > enemyMax) {
			enemyMax = turn.enemyMax;
		}

		if (player->isDead()) {
			std::cout << "プレイヤー死亡\n";

			break;
		}

		if (slime->isDead() && goblin->isDead()) {
			std::cout << "敵全滅\n";

			break;
		}
	}

	std::cout << "戦闘ターン数 : " << turnCount << std::endl;
	std::cout << "プレイヤーの最大与ダメージ : " << playerMax << std::endl;
	std::cout << "いずれかの敵の最大与ダメージ : " << enemyMax << std::endl;

	return 0;
}