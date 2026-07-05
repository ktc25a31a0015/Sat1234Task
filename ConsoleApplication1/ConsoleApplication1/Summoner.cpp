#include "Summoner.h"

Summoner::Summoner() {
	attackPower = 50;
}

ResultId Summoner::TargetFencer() {
	return ResultId::Counter;
}

ResultId Summoner::TargetWizard() {
	return ResultId::Critical;
}

ResultId Summoner::TargetSummoner() {
	return ResultId::Draw;
}