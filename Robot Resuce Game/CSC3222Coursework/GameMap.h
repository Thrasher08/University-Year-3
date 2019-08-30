#pragma once
#include <string>
#include <vector>

#include "../../Common/Vector2.h"
#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"

#include "GameSimsPhysics.h"
#include "GameSimsRenderer.h"

namespace NCL {
	namespace Rendering {
		class TextureBase;
	}
	using namespace Maths;
	namespace CSC3222 {
		class GameSimsRenderer;
		class SimObject;
		class TextureManager;

		enum MapTileType {
			Flat,
			Wall,
			Rough,
			MAX_TILES
		};

		enum MapStructureType {
			RedTeleporter,
			GreenTeleporter,
			BlueTeleporter
		};

		struct StructureData {
			Vector2				startPos;
			MapStructureType	structureType;
		};

		struct MapNode {
			MapNode* bestParent;
			int posX;
			int posY;
			float g;
			float h;
			float f;
			bool closed;
			bool open;
		};

		class GameMap	{
		public:
			GameMap(const std::string& filename, std::vector<SimObject*>& objects, TextureManager& texManager, GameSimsPhysics* physics);
			~GameMap();

			void DrawMap(GameSimsRenderer & r);

			int GetMapWidth() const {
				return mapWidth;
			}

			int GetMapHeight() const {
				return mapHeight;
			}
			
			float manhattanDist(MapNode* node1, MapNode* node2);
			
			bool PathFinding(Vector2 start, Vector2 end, std::vector <MapNode*>& path);
			
			//Vector2 GetRandomPosition() const;
			//Vector2 GetRandomPositionWithinRadius(Vector2 pos, float r) const;
			
			MapNode* best(std::vector<MapNode*> node);
			
			std::vector<MapNode*> findNeighbour(MapNode* p);
			
			bool GeneratePath(Vector2 start, Vector2 end, std::vector<Vector2>& path) const;

		protected:
			int mapWidth;
			int mapHeight;
			int structureCount;

			static Vector4 tileSpecs[MAX_TILES];

			GameSimsRenderer r;

			Rendering::TextureBase*	tileTexture;
			MapTileType*	mapData;
			MapNode*		nodeData;
			StructureData*	structureData;		
		};
	}
}

