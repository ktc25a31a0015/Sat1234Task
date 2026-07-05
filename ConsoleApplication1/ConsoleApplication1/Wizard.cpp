#include "Wizard.h"

Wizard::Wizard() {
	attackPower = 35;
}

ResultId Wizard::TargetFencer() {
	return ResultId::Critical;
}

ResultId Wizard::TargetWizard() {
	return ResultId::Draw;
}

ResultId Wizard::TargetSummoner() {
	return ResultId::Counter;
}