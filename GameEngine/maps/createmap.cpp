#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <string>

struct Obstacle {
	std::uint16_t x, y, w, h;
	char textureFile[50];
};

int main() {
 	// GMAP file format
	// (char[50]) background
	// (uint16_t) startingPosX
	// (uint16_t) startingPosY
	// (uint16_t) obstacles
	// repeat "obstacles" times

	// end repeat


	std::string mapName;
	std::cout << "Enter map name: "; std::cin >> mapName; 
	std::ofstream mapfile((mapName + ".gmap").c_str(), std::ios::binary);
	char background[50];
	std::uint16_t startingPosX = 0;
	std::uint16_t startingPosY = 0;
	std::vector<Obstacle> obstacles;


	std::cout << "Background image file name: "; std::cin >> background;

	std::cout << "Starting pos X: "; std::cin >> startingPosX;
	std::cout << "Starting pos Y: "; std::cin >> startingPosY;

	mapfile.write(background, sizeof(background));
	mapfile.write(reinterpret_cast<char*>(&startingPosX), sizeof(startingPosX));
	mapfile.write(reinterpret_cast<char*>(&startingPosY), sizeof(startingPosY));

	int option;
	do {
		std::cout << "Enter 9 to stop entering obstacles, enter anything else to continue" << std::endl;
		std::cin >> option;
		if(option != 9) {
			Obstacle o;
			std::cout << "Obstacle X pos: "; std::cin >> o.x;
			std::cout << "Obstacle Y pos: "; std::cin >> o.y;
			std::cout << "Obstacle width: "; std::cin >> o.w;
			std::cout << "Obstacle height: "; std::cin >> o.h;
			std::cout << "Obstacle texture file name: "; std::cin >> o.textureFile;
			obstacles.push_back(o);
		}

	} while(option != 9);

	std::uint16_t Nobstacles = obstacles.size();

	mapfile.write(reinterpret_cast<char*>(&Nobstacles), sizeof(Nobstacles));

	for(Obstacle &o : obstacles) {
		mapfile.write(reinterpret_cast<char*>(&o.x), sizeof(o.x));
		mapfile.write(reinterpret_cast<char*>(&o.y), sizeof(o.y));
		mapfile.write(reinterpret_cast<char*>(&o.w), sizeof(o.w));
		mapfile.write(reinterpret_cast<char*>(&o.h), sizeof(o.h));
		mapfile.write(o.textureFile, sizeof(o.textureFile));
	}

	std::cout << "Written " << obstacles.size() << " obstacles" << std::endl;

    return 0;
}