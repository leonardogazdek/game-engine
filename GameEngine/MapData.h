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
	std::uint16_t startingPosX = 0, startingPosY = 0, obstacles = 0;
	Obstacles obs = Obstacles(GameData::GetInstance()->renderer);
	void LoadMap(std::string mapName);
	std::vector<std::string> GetAllMaps();
};

