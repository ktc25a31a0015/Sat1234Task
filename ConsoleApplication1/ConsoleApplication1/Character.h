#pragma once

#include <iostream>

enum class CharacterId { Fencer, Wizard, Summoner };
enum class ActionId { Attack, Defence };
enum class ResultId { None, Draw, Critical, Counter };

const int characterCount = 3;
const char characterNames[characterCount][16] = { "åïém", "ñÇñ@égÇ¢", "è¢ä´ém" };
const char characterInitials[characterCount] = { 'f', 'w', 's' };

class Character
{
public:
	ResultId Attack(CharacterId opponentId);

	bool IsAttack();
	
private:
	virtual ResultId TargetFencer() = 0;
	virtual ResultId TargetWizard() = 0;
	virtual ResultId TargetSummoner() = 0;

public:
	ActionId actionId;
	int attackPower;
};