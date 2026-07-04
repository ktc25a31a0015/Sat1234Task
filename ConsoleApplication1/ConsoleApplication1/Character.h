#pragma once

#include <iostream>

class Character
{
public:
	Character(int attack);

public:
	int TackAction(std::shared_ptr<Character> opponent);

	bool IsAttack();
	
private:
	virtual int Attack() = 0;

public:
	int actionId;
	int attack;

protected:
	/// <summary>
	/// 0 = Swordman,
	/// 1 = Wizard,
	/// 2 = Summoner,
	/// </summary>
	int opponentId;
};