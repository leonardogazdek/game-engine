#include "GameData.h"

GameData* GameData::Instance = nullptr;

GameData::GameData() {
	window = nullptr;
}

GameData* GameData::GetInstance() {
	if (Instance == nullptr) {
		Instance = new GameData();
	}
	return Instance;
}

