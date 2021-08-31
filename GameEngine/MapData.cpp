#include "MapData.h"
#include <fstream>
#include <filesystem>



void MapData::LoadMap(std::string mapName) {
	std::string mapPath = "maps/" + mapName + ".gmap";
	std::ifstream mapFile(mapPath.c_str(), std::ios::binary);

	mapFile.read(reinterpret_cast<char*>(&startingPosX), sizeof(startingPosX));
	mapFile.read(reinterpret_cast<char*>(&startingPosY), sizeof(startingPosY));
	mapFile.read(reinterpret_cast<char*>(&obstacles), sizeof(obstacles));

	for (int i = 0; i < obstacles; i++) {
		std::uint16_t x, y, w, h;
		char textureFile[50];

		mapFile.read(reinterpret_cast<char*>(&x), sizeof(x));
		mapFile.read(reinterpret_cast<char*>(&y), sizeof(y));
		mapFile.read(reinterpret_cast<char*>(&w), sizeof(w));
		mapFile.read(reinterpret_cast<char*>(&h), sizeof(h));
		mapFile.read(textureFile, sizeof(textureFile));

		obs.Add(Obstacle(GameData::GetInstance()->renderer, SDL_Rect{ x, y, w, h }, std::string("textures/" + std::string(textureFile)).c_str()));
	}

	mapFile.close();
}

std::vector<std::string> MapData::GetAllMaps() {
	std::vector<std::string> result;
	for (const auto& entry : std::filesystem::directory_iterator("maps/")) {
		std::string mapname = entry.path().string();
		size_t dotIdx = mapname.find(".");
		std::string extension = mapname.substr(dotIdx + 1);
		size_t slashIdx = mapname.find("/");
		std::string mapName = mapname.substr(slashIdx + 1, dotIdx - slashIdx - 1);
		if (extension == "gmap") {
			result.push_back(mapName);
		}
	}
	return result;
}