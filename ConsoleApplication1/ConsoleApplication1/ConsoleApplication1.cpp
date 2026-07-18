#include <iostream>
#include <unordered_map>

#include "SkillManager.h"
#include "DamageManager.h"
#include "Character.h"
#include "Fencer.h"
#include "Wizard.h"
#include "Summoner.h"

const int actionCount = 2;
const char actionNames[actionCount][8] = { "攻撃", "防御" };
const char actionInitials[actionCount] = { 'a', 'd' };

void inputClear() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main()
{
	srand((unsigned int)time(NULL));

	int turnCount = 0;

	int allyHP = 300;
	int enemyHP = 300;

	std::shared_ptr<Character> allies[characterCount] = { std::make_shared<Fencer>(), std::make_shared<Wizard>(), std::make_shared<Summoner>() };
	std::shared_ptr<Character> enemies[characterCount] = { std::make_shared<Fencer>(), std::make_shared<Wizard>(), std::make_shared<Summoner>() };

	SkillData skill;

	DamageSource allyDamage;
	DamageSource enemyDamage;

	while (allyHP > 0 && enemyHP > 0) {
		turnCount++;

		std::cout << turnCount << " ターン目スタート\n";
		std::cout << "戦力 -> 味方:" << allyHP << " VS 敵 : " << enemyHP << '\n';
		std::cout << std::endl;

		skill.DispSkillInfo();

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

			char charInput;
			std::cin >> charInput;

			for (int i = 0; i < characterCount; i++) {
				char initial = characterInitials[i];

				if (charInput == initial) {
					allyId = i;

					break;
				}
			}

			inputClear();
		}
		std::shared_ptr<Character> ally = allies[allyId];
		std::cout << characterNames[allyId] << "を使用して戦います。\n";
		std::cout << std::endl;

		int allyActionId = -1;
		while (allyActionId == -1) {
			std::cout << "選択する行動に当てはまるキーワードを入力してください。\n";
			std::cout << "攻撃 : [a]、防御 : [d] -> ";

			char attackInput;
			std::cin >> attackInput;

			for (int i = 0; i < actionCount; i++) {
				char initial = actionInitials[i];

				if (attackInput == initial) {
					allyActionId = i;

					break;
				}
			}

			inputClear();
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
		
		if ((CharacterId)allyId == CharacterId::Summoner) {
			if (skill.TryUse(CharacterId::Summoner)) {
				std::cout << "召喚士の特殊スキルが発動しました。\n";
				std::cout << "特殊スキルにより、強制的にドローとなりました。\n";
			}
		}
		else if (ally->actionId == enemy->actionId) {
			// 互いに攻撃を選択したとき
			if (ally->IsAttack() && enemy->IsAttack()) {
				if (allyAttack == enemyAttack) {
					std::cout << "味方と敵の攻撃力が一緒のため、ドローとなりました。\n";
				}
				else if (allyAttack > enemyAttack) {
					enemyHP -= allyAttack;
					enemyDamage.Add(ResultId::None, (CharacterId)allyId);

					std::cout << "味方の攻撃力が敵を上回ったため、敵の戦力を削りました。\n";
				}
				else {
					allyHP -= enemyAttack;
					allyDamage.Add(ResultId::None, (CharacterId)enemyId);

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
					int multiply = 2;

					if ((CharacterId)allyId == CharacterId::Fencer) {
						if (skill.TryUse(CharacterId::Fencer)) {
							multiply = 6;

							std::cout << "剣士の特殊スキルが発動しました。\n";
						}
					}

					enemyHP -= ally->attackPower * multiply;
					enemyDamage.Add(ResultId::Critical, (CharacterId)allyId);

					std::cout << "敵の戦力を大幅に削りました。（倍率 : " << multiply << " 倍）\n";
				}
				else {
					allyHP -= enemy->attackPower * 2;
					allyDamage.Add(ResultId::Critical, (CharacterId)enemyId);

					std::cout << "味方の戦力が大幅に削られました。\n";
				}

				break;

			case ResultId::Counter:
				std::cout << "カウンター発生\n";

				if (ally->IsAttack()) {
					allyHP -= ally->attackPower * 2;
					allyDamage.Add(ResultId::Counter, (CharacterId)enemyId);

					std::cout << "味方の戦力が大幅に減少しました。\n";
				}
				else {
					enemyHP -= enemy->attackPower * 2;
					enemyDamage.Add(ResultId::Counter, (CharacterId)allyId);

					std::cout << "敵の戦力が大幅に減少しました。\n";
				}

				break;

			default:
				std::cout << "想定されていない行動です。\n";

				return 0;
			}
		}

		std::cout << std::endl;

		skill.CheckAvailables(allyDamage, enemyDamage);

		if (skill.TryUse(CharacterId::Wizard)) {

			int heal = enemyDamage.GetTypeChar(ResultId::None, CharacterId::Wizard) + enemyDamage.GetTypeChar(ResultId::None, CharacterId::Wizard);
			allyHP += heal * 10;

			std::cout << "魔法使いの特殊スキルが発動しました。\n";
			std::cout << "自身が攻撃した " << heal << " 回 x 10 の戦力を回復させました。\n";
		}
		
		// 次のターンに行くとき、画面をクリアする
		if (allyHP > 0 && enemyHP > 0) {
			std::cout << "任意の入力をして次のターンに進む : ";

			char wait;
			std::cin >> wait;

			inputClear();

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