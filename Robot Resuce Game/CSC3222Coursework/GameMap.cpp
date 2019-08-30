#include "GameMap.h"
#include "GameSimsRenderer.h"
#include "TextureManager.h"
#include "../../Common/Assets.h"
#include "../../Common/TextureLoader.h"
#include "CollisionVolume.h"
#include "GameSimsPhysics.h"
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace NCL;
using namespace CSC3222;
using namespace Rendering;

//These are all in format: x pos, y pos, xsize, ysize
Vector4 GameMap::tileSpecs[MAX_TILES] = {
	Vector4(101,13,16,16),	//Flat
	Vector4(96,56,16,16),	//Wall
	Vector4(144,56,16,16),	//Rough
};

//Random rough looking tiles for variety
Vector4 randomRoughTiles[4] = {
	Vector4(144,40,16,16),	//
	Vector4(144,56,16,16),	//
	Vector4(160,40,16,16),	//
	Vector4(160,56,16,16),	//
};

Vector4 buildingTypes[4] = {
	Vector4(376,56,32,48),	//Red teleporter
	Vector4(376,112,32,48), //blue teleporter
	Vector4(376,168,32,48), //green teleporter
	Vector4(144,256,64,64)  //Robot Home
};


GameMap::GameMap(const std::string& filename, std::vector<SimObject*>& objects, TextureManager& texManager, GameSimsPhysics* physics)	{
	tileTexture = texManager.GetTexture("Colony.png");

	std::ifstream mapFile(Assets::DATADIR + filename);

	if (!mapFile) {
		std::cout << "GameMap can't be loaded in!" << std::endl;
		return;
	}

	mapFile >> mapWidth;
	mapFile >> mapHeight;

	mapData = new MapTileType[mapWidth * mapHeight];
	nodeData = new MapNode[mapWidth * mapHeight];

	for (int y = 0; y < mapHeight; ++y) {
		for (int x = 0; x < mapWidth; ++x) {
			int tileIndex = (y * mapWidth) + x;

			char type = 0;

			mapFile >> type;
			if (type == '1') {

				int size = 16;
				int radius = 16;
				bool staticObj = true;
				float inverseMass = 0 ;

				RigidBody* wRb = new RigidBody();
				wRb->setIMass(inverseMass);

				CollisionVolume* col = new CollisionVolume(CollisionVolume::bBox, wRb);

				col->setRadius(radius);
				col->setSize(size);
				col->setStatic(staticObj);
				col->setPos(Vector2(x*16, y*16));
				physics->AddCollider(col);
			}
			mapData[tileIndex] = (MapTileType)(type - 48);
			nodeData[tileIndex] = MapNode();
			nodeData[tileIndex].posX = x * 16;
			nodeData[tileIndex].posY = y * 16;
		}
	}
	mapFile >> structureCount;

	structureData = new StructureData[structureCount];

	for (int i = 0; i < structureCount; ++i) {
		int type  = 0;
		int xTile = 0;
		int yTile = 0;

		mapFile >> type;
		mapFile >> xTile;
		mapFile >> yTile;

		structureData[i].structureType = (MapStructureType)type;
		structureData[i].startPos.x = xTile * 16;
		structureData[i].startPos.y = yTile * 16;
	}

	//PathFinding(Vector2(16, 64), Vector2(16, 128));	
	//16,64 16, 128
}

GameMap::~GameMap()	{
	delete[] mapData;
	delete[] structureData;
}

void GameMap::DrawMap(GameSimsRenderer & r) {
	int tileSize = 16;

	srand(0); //so we get consistent floor tiles

	for (int y = 0; y < mapHeight; ++y) {
		for (int x = 0; x < mapWidth; ++x) {
			int tileType = mapData[(y * mapWidth) + x];

			Vector4 tileData;

			if (tileType == MapTileType::Rough) {
				int randomFlatTile = rand() % 4;
				tileData = randomRoughTiles[randomFlatTile];
			}
			else {
				tileData = tileSpecs[tileType];
			}

			Vector2 texPos  = Vector2(tileData.x, tileData.y);
			Vector2 texSize = Vector2(tileData.z, tileData.w);

			Vector2 screenPos = Vector2(x * 16, y * 16);

			r.DrawTextureArea((OGLTexture*)tileTexture, texPos, texSize, screenPos, false);
			r.DrawBox(screenPos + Vector2(8, 8), Vector2(8, 8));
		}
	}

	for (int i = 0; i < structureCount; ++i) {
		Vector4 buildingData = buildingTypes[structureData[i].structureType];

		Vector2 texPos = Vector2(buildingData.x, buildingData.y);
		Vector2 texSize = Vector2(buildingData.z, buildingData.w);

		Vector2 screenPos = structureData[i].startPos;

		r.DrawTextureArea((OGLTexture*)tileTexture, texPos, texSize, screenPos, false);
	}
}

bool GameMap::PathFinding(Vector2 start, Vector2 end, std::vector <MapNode*>& path) {
	int aX = start.x / 16;
	int bX = end.x / 16;
	int aY = start.y / 16;
	int bY = end.y / 16;

	MapNode* a = &nodeData[aY * mapWidth + aX];
	MapNode* b = &nodeData[bY * mapWidth + bX];

	//Initialisation
	a->g = 0;
	a->h = manhattanDist(a, b);
	//std::cout << "Manhattan Dist: " << a->h << std::endl;
	a->f = a->g + a->h;

	std::vector<MapNode*> openList;
	std::vector<MapNode*> closedList;
	openList.push_back(a);
	a->open = true;

	//Procedure
	MapNode* p = best(openList);
	while (openList.size() > 0) {
		if (p == b) {
			break;
		}
		else {
			std::vector<MapNode*> n = findNeighbour(p);
				for (auto &q: n){
					if (!q->closed) {
						q->g = p->g + 1;
						q->h = manhattanDist(q, b);
						//std::cout << "Manhattan Dist 2: " << q->h << std::endl;
						float fNew = q->g + q->h;

						if (q->open && fNew >= q->f) {

						}
						else if (q->open && fNew < q->f) {
							q->bestParent = p;
							q->f = fNew;
						}
						else {
							q->bestParent = p;
							q->open = true;
							q->f = fNew;
							openList.emplace_back(q);
					}
				}
			}
			
			p->closed = true;
			closedList.push_back(p);
			p = best(openList);
			for (int i = 0; i < openList.size(); i++) {
				if (openList[i] == p) {
					openList.erase(openList.begin() + i);
				}
			}
		}
	}

	//Generate Path
	//std::vector <MapNode*> nodePath;
	MapNode* r = b;
	while (r != a && r != nullptr) {
		path.emplace_back(r);
		MapNode* s = r->bestParent;
		r = s;
	}
	path.emplace_back(a);

	for (int i = 0; i < path.size(); i++) {
		std::cout << "Node: " << i << " posX: " << path[i]->posX << " posY: " << path[i]->posY << " " << std::endl;
	}

	return true;
}

float GameMap::manhattanDist(MapNode* node1, MapNode* node2) {
	return abs(node1->posX - node2->posX) + abs(node1->posY - node2->posY);
}

MapNode* GameMap::best(std::vector<MapNode*> openList) {

	float bestF = openList[0]->g + openList[0]->h;
	MapNode* bestNode = openList[0];
	
	for (auto& i : openList) {
		float iF = i->g + i->h;
		if (iF < bestF) {
			bestF = iF;
			bestNode = i;
		}
	}

	return bestNode;
}

std::vector<MapNode*> GameMap::findNeighbour(MapNode* p) {
	std::vector < MapNode * > activeNeighbours;// valid nodes to expand to
	int x = p->posX / 16;
	int y = p->posY / 16;
	if (x >0) {
		int tileType = mapData[((y)* mapWidth) + (x - 1)];
		if (tileType != Wall) {
			MapNode * neighbour = &nodeData[((y)* mapWidth) + (x - 1)];
			activeNeighbours.emplace_back(neighbour);
		}
	}

	if (x < mapWidth - 2) { // can expand right
		int tileType = mapData[((y)* mapWidth) + (x + 1)];
		if (tileType != Wall) {
			MapNode * neighbour = &nodeData[((y)* mapWidth) + (x + 1)];
			activeNeighbours.emplace_back(neighbour);
		}
	}
	if (y > 0) { // can expand up
		int tileType = mapData[((y - 1) * mapWidth) + (x)];
			if (tileType != Wall) {
				MapNode * neighbour = &nodeData[((y - 1) * mapWidth) + (x)];
				activeNeighbours.emplace_back(neighbour);
			}
	}
	if (y < mapHeight - 2) { // can expand right
		int tileType = mapData[((y + 1) * mapWidth) + (x)];
		if (tileType != Wall) {
			MapNode * neighbour = &nodeData[((y + 1) * mapWidth) + (x)];
			activeNeighbours.emplace_back(neighbour);

		}
	}	return activeNeighbours;
}