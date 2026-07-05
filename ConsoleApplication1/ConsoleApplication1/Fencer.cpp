#include "Fencer.h"

Fencer::Fencer() {
	attackPower = 15;
}

ResultId Fencer::TargetFencer() {
	return ResultId::Draw;
}

ResultId Fencer::TargetWizard() {
	return ResultId::Counter;
}

ResultId Fencer::TargetSummoner() {
	return ResultId::Critical;
}