#pragma once
#include <cstdint>
#include "Obstacle.h"
#include "GameData.h"
#include <string>
#include <vector>

class MapData
{
public:
	bool mapLoaded = false;
	char background[50];
	std::uint16_t startingPosX, startingPosY, obstacles;
	Obstacles obs = Obstacles(GameData::GetInstance()->renderer);
	void LoadMap(std::string mapName);
	std::vector<std::string> GetAllMaps();
};

