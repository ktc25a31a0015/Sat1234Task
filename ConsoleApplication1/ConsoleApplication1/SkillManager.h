#pragma once

#include <unordered_map>

#include "Character.h"
#include "DamageManager.h"

const char skillConditionInfo[characterCount][128] = {
	"味方が累計６回、攻撃を受ける（クリティカル含む）",
	"味方が累計３回、クリティカルを受ける",
	"味方が累計３回、カウンターを成功させる"
};
const int availableNumber[characterCount] = { 6, 3, 3 };
const char skillWorkInfo[characterCount][128] = {
	"次に剣士としてクリティカルを発生させたとき、攻撃力を６倍にする。",
	"条件を満たしたとき、魔法使いとして攻撃した回数 x 10 の戦力を自動回復する。",
	"次に召喚士として行動したとき、結果を必ずドローにする。"
};

class SkillData {
public:
	SkillData();

public:
	void DispSkillInfo();
	void CheckAvailables(DamageSource& ally, DamageSource& enemy);
	bool TryUse(CharacterId character);

private:
	void SetAvailable(CharacterId character);

private:
	int conditionCount[characterCount];
	std::unordered_map<CharacterId, int> availables;
};