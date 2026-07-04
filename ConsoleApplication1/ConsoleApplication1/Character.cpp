#include "Character.h"

#include "Swordman.h"
#include "Wizard.h"
#include "Summoner.h"

Character::Character(int attack) {
	opponentId = -1;
	actionId = 0;

	this->attack = attack;
}

/// <summary>
/// 0 = null,
/// 1 = critical,
/// 2 = counter
/// </summary>
int Character::TackAction(std::shared_ptr<Character> opponent) {
	if (IsAttack()) {
		if (typeid(opponent) == typeid(Swordman)) {
			opponentId = 0;
		}
		else if (typeid(opponent) == typeid(Wizard)) {
			opponentId = 1;
		}
		else if (typeid(opponent) == typeid(Summoner)) {
			opponentId = 2;
		}
		else {
			opponentId = -1;

			std::cout << "‘z’èŠO‚ÌŒ^‚ªŽw’è‚³‚ê‚Ä‚¢‚Ü‚·\n";
		}
		
		return Attack();
	}
	else return 0;
}

bool Character::IsAttack() {
	return actionId == 0;
}