#include <iostream>

#include "Character.h"
#include "Fencer.h"
#include "Wizard.h"
#include "Summoner.h"

const int characterCount = 3;
const char characterNames[characterCount][16] = { "剣士", "魔法使い", "召喚士" };
const char characterInitials[characterCount] = { 'f', 'w', 's' };

const int actionCount = 2;
const char actionNames[actionCount][8] = { "攻撃", "防御" };
const char actionInitials[actionCount] = { 'a', 'd' };

int main()
{
	srand((unsigned int)time(NULL));

	int turnCount = 0;

	int allyHP = 300;
	int enemyHP = 300;

	std::shared_ptr<Character> allies[characterCount] = { std::make_shared<Fencer>(), std::make_shared<Wizard>(), std::make_shared<Summoner>() };
	std::shared_ptr<Character> enemies[characterCount] = { std::make_shared<Fencer>(), std::make_shared<Wizard>(), std::make_shared<Summoner>() };

	char input;
	while (allyHP > 0 && enemyHP > 0) {
		turnCount++;

		std::cout << turnCount << " ターン目スタート\n";
		std::cout << "戦力 -> 味方:" << allyHP << " VS 敵 : " << enemyHP << '\n';
		std::cout << std::endl;

		int allyId = -1;
		
		while (allyId == -1) {
			std::cout << "使用するキャラクターに当てはまるキーワードを入力してください。(攻撃力)\n";
			for (int i = 0; i < characterCount; i++) {
				std::cout << characterNames[i] << "(" << allies[i]->attackPower << ") : [" << characterInitials[i] << "]";

				if (i + 1 == characterCount) {
					std::cout << " -> ";
				}
				else {
					std::cout << "、";
				}
			}

			std::cin >> input;

			for (int i = 0; i < characterCount; i++) {
				char initial = characterInitials[i];

				if (input == initial) {
					allyId = i;

					break;
				}
			}
		}
		std::shared_ptr<Character> ally = allies[allyId];
		std::cout << characterNames[allyId] << "を使用して戦います。\n";
		std::cout << std::endl;

		int allyActionId = -1;
		while (allyActionId == -1) {
			std::cout << "選択する行動に当てはまるキーワードを入力してください。\n";
			std::cout << "攻撃 : [a]、防御 : [d] -> ";
			std::cin >> input;

			for (int i = 0; i < actionCount; i++) {
				char initial = actionInitials[i];

				if (input == initial) {
					allyActionId = i;

					break;
				}
			}
		}
		ally->actionId = (ActionId)allyActionId;
		std::cout << "味方は" << actionNames[allyActionId] << "します。\n";
		std::cout << std::endl;

		int enemyId = rand() % characterCount;
		std::shared_ptr<Character> enemy = enemies[enemyId];
		std::cout << "敵の使用キャラクター : " << characterNames[enemyId] << '\n';
		
		int enemyActionId = rand() % 2;
		enemy->actionId = (ActionId)enemyActionId;
		std::cout << "敵の行動 : " << actionNames[enemyActionId] << '\n';

		std::cout << std::endl;

		std::cout << "味方(" << characterNames[allyId] << ":" << actionNames[allyActionId]
			<< ") VS " << "敵(" << characterNames[enemyId] << ":" << actionNames[enemyActionId] << ")\n";

		int allyAttack = ally->attackPower;
		int enemyAttack = enemy->attackPower;

		std::cout << " - ";
		
		if (ally->actionId == enemy->actionId) {
			// 互いに攻撃を選択したとき
			if (ally->IsAttack() && enemy->IsAttack()) {
				if (allyAttack == enemyAttack) {
					std::cout << "味方と敵の攻撃力が一緒のため、ドローとなりました。\n";
				}
				else if (allyAttack > enemyAttack) {
					enemyHP -= allyAttack;
					std::cout << "味方の攻撃力が敵を上回ったため、敵の戦力を削りました。\n";
				}
				else {
					allyHP -= enemyAttack;
					std::cout << "敵の攻撃力が味方を上回ったため、味方の戦力が削られました。\n";
				}
			}
			else { // 互いに防御を選択したとき
				std::cout << "未定義\n";
			}
		}
		else { // それぞれが別の行動を選択したとき
			ResultId result = ResultId::Draw;

			if (ally->IsAttack()) {
				result = ally->Attack((CharacterId)enemyId);
			}
			else if (enemy->IsAttack()) {
				result = enemy->Attack((CharacterId)allyId);
			}

			switch (result) {
			case ResultId::Draw:
				std::cout << "互いのキャラクターが一緒のため、ドローとなりました。\n";

				break;

			case ResultId::Critical:
				std::cout << "クリティカル攻撃\n";

				if (ally->IsAttack()) {
					enemyHP -= ally->attackPower * 2;

					std::cout << "敵の戦力を大幅に削りました。\n";
				}
				else {
					allyHP -= enemy->attackPower * 2;

					std::cout << "味方の戦力が大幅に削られました。\n";
				}

				break;

			case ResultId::Counter:
				std::cout << "カウンター発生\n";

				if (ally->IsAttack()) {
					allyHP -= ally->attackPower * 2;

					std::cout << "味方の戦力が大幅に減少しました。\n";
				}
				else {
					enemyHP -= enemy->attackPower * 2;

					std::cout << "敵の戦力が大幅に減少しました。\n";
				}

				break;

			default:
				std::cout << "想定されていない行動です。\n";

				return 0;
			}
		}

		std::cout << std::endl;
		
		// 次のターンに行くとき、画面をクリアする
		if (allyHP > 0 && enemyHP > 0) {
			std::cout << "任意の入力をして次のターンに進む : ";

			char wait;
			std::cin >> wait;

			std::system("cls");
		}
	}

	if (allyHP <= 0 && enemyHP <= 0) {
		std::cout << "引き分け\n";
	}
	else if (allyHP > 0) {
		std::cout << "味方陣営の勝利です\n";
	}
	else {
		std::cout << "敵陣営の勝利です\n";
	}

	std::cout << "経過ターン数 : " << turnCount << std::endl;

	return 0;
}