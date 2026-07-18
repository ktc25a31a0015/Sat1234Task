#include "SkillManager.h"

SkillData::SkillData() {
	for (int i = 0; i < characterCount; i++) {
		conditionCount[i] = 0;
	}

	availables = {
		{ CharacterId::Fencer, 0 },
		{ CharacterId::Wizard, 0 },
		{ CharacterId::Summoner, 0 }
	};
}

void SkillData::DispSkillInfo() {
	std::cout << "各キャラのスキル状況\n";
	for (std::pair<CharacterId, int> pair : availables) {
		const char* available = pair.second == 0 ? "未達成" : pair.second == 1 ? "使用可能" : "使用済み";

		int index = (int)pair.first;

		std::cout << characterNames[index] << " " << available << " " << conditionCount[index] << " / " << availableNumber[index] << " 回（" << skillConditionInfo[index] << "）\n";
		std::cout << " - " << skillWorkInfo[index] << '\n';
		std::cout << std::endl;
	}
}

void SkillData::CheckAvailables(DamageSource& ally, DamageSource& enemy) {
	// スキルの発動条件に基づき、使用可能なスキルを設定
	conditionCount[0] = ally.GetType(ResultId::None);
	conditionCount[1] = ally.GetType(ResultId::Critical);
	conditionCount[2] = enemy.GetType(ResultId::Counter);

	if ((conditionCount[0] + conditionCount[1]) == availableNumber[0]) {
		// 味方が累計６回、攻撃を受ける（クリティカル含む）
		SetAvailable(CharacterId::Fencer);
	}
	if (conditionCount[1] == availableNumber[1]) {
		// 味方が累計３回、クリティカルを受ける
		SetAvailable(CharacterId::Wizard);
	}
	if (conditionCount[2] == availableNumber[2]) {
		// 味方が累計３回、カウンターを成功させる
		SetAvailable(CharacterId::Summoner);
	}
}

void SkillData::SetAvailable(CharacterId character) {
	if (availables[character] == 0) {
		// 未使用の時のみ使用可能に
		availables[character] == 1;
	}
}

bool SkillData::TryUse(CharacterId character) {
	if (availables[character] == 1) {
		availables[character] == -1; // 使用済みに

		return true;
	}

	return false;
}