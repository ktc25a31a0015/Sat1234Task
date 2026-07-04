#include "character.h"

Character::Character() {
	this->name = "name";

	_isDead = false;

	_parameter.hp = rand() % 51 + 50;
	_parameter.attack = 0;
}
void Character::setName(const char* name) {
	this->name = name;
}

void Character::damage(int attack) {
	_parameter.hp -= attack;

	if (_parameter.hp <= 0) {
		_parameter.hp = 0;

		dead();
	}
}

bool Character::isDead() {
	return _isDead;
}

void Character::dead() {
	_isDead = true;
}

int Character::getHP() {
	return _parameter.hp;
}

int Character::getAttack() {
	return _parameter.attack;
}

void Player::setAttack() {
	_parameter.attack = rand() % 21;
}

void Slime::setAttack() {
	_parameter.attack = rand() % 11;
}

void Goblin::setAttack() {
	_parameter.attack = rand() % 9 + 8;
}