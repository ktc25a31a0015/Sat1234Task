#pragma once

#include <iostream>
#include <unordered_map>

#include "Character.h"

typedef std::unordered_map<ResultId, int, CharacterId> Test;

class DamageSource {
public:
	void Add(ResultId type, CharacterId attacker);
	int GetType(ResultId type);
	int GetTypeChar(ResultId type, CharacterId character);

private:
	std::unordered_map<ResultId, std::unordered_map<CharacterId, int>> data;
};