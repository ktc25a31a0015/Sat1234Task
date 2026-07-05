#pragma once

#include "Character.h"

class Summoner : public Character {
public:
	Summoner();

private:
	ResultId TargetFencer() override;
	ResultId TargetWizard() override;
	ResultId TargetSummoner() override;
};