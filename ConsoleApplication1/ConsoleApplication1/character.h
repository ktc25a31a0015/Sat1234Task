#pragma once

#include <iostream>

struct Parameter
{
	int hp;
	int attack;
};

class Character {
public:
	Character();

public:
	void setName(const char* name);
	int getHP();
	int getAttack();
	virtual void setAttack() = 0;
	void damage(int attack);
	bool isDead();

private:
	void dead();

public:
	const char* name;

protected:
	bool _isDead;
	Parameter _parameter;
};

class Player : public Character {
public:
	void setAttack() override;
};

class Slime : public Character {
public:
	void setAttack() override;
};

class Goblin : public Character {
public:
	void setAttack() override;
};