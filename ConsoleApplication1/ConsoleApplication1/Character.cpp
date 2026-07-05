#include "Character.h"

#include "Fencer.h"
#include "Wizard.h"
#include "Summoner.h"

ResultId Character::Attack(CharacterId opponentId) {
	ResultId result = ResultId::None;

	if (IsAttack()) {
		switch (opponentId) {
		case CharacterId::Fencer:
			result = TargetFencer();

			break;

		case CharacterId::Wizard:
			result = TargetWizard();

			break;

		case CharacterId::Summoner:
			result = TargetSummoner();

			break;

		default:
			std::cout << "‘z’èŠO‚ÌŒ^‚ªŽw’è‚³‚ê‚Ä‚¢‚Ü‚·\n";

			break;
		}
	}
	else {
		std::cout << "UŒ‚•s‰Â\n";
	}
	
	return result;
}

bool Character::IsAttack() {
	return actionId == ActionId::Attack;
}