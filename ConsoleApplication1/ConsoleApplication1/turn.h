#pragma once

#include <iostream>
#include "character.h"

class Turn
{
public:
	Turn(std::shared_ptr<Player> player, std::shared_ptr<Slime> slime, std::shared_ptr<Goblin> goblin);

private:
	void enemyAttack(std::shared_ptr<Player> player, std::shared_ptr<Character> enemy);
	void dispHP(std::shared_ptr<Character> character);

public:
	int playerMax;
	int enemyMax;
};