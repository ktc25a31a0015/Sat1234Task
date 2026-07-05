#pragma once

#include "Character.h"

class Fencer : public Character {
public:
	Fencer();

private:
	ResultId TargetFencer() override;
	ResultId TargetWizard() override;
	ResultId TargetSummoner() override;
};