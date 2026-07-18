#include "DamageManager.h"

void DamageSource::Add(ResultId type, CharacterId attacker) {
	data[type][attacker]++;
}

int DamageSource::GetType(ResultId type) {
	int count = 0;

	for (int i = 0; i < data[type].size(); i++) {
		count += data[type][(CharacterId)i];
	}

	return count;
}

int DamageSource::GetTypeChar(ResultId type, CharacterId character) {
	return data[type][character];
}