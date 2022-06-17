#ifndef BLOCK_H_
#define BLOCK_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/hash.hpp>

#include <vector>
#include <map>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

namespace EBlockType {
	enum Block {
		Air,
		Stone,
		Grass,
		Water,
		Log,
		Leaves,
		Dirt,
		Cobblestone,
		Bedrock
	};
}

namespace EFaceTexture {

	enum Texture : uint16_t {

		Stone,
		Dirt,
		GrassSide,
		Grass,
		Water,
		LogTop,
		LogSide,
		Leaves,
		Cobblestone,
		Bedrock

	};

}

// Texture winding order - top, bottom, left, right, front, back
class CBlockEntry {
public:

	CBlockEntry(uint8_t id, std::vector<uint16_t> faceTextures)
		: ID(id), FaceTextures(faceTextures) { }

	uint8_t ID;
	std::vector<uint16_t> FaceTextures;

};


class CBlockDictionary {
public:

	static std::shared_ptr<CBlockDictionary> GetInstance();

	static std::shared_ptr<CBlockDictionary> Instance;

public:

	void Build();

	// The index of the texutres path in this array is equal to
	// that textures ID, to be referenced in the block entry
	std::vector<std::string> Textures;

	// Only supports up to 255 blocs, 0 being air
	// word stores vectors of chunks which are 16x16x256
	// vectors of uint8_t which reference the block dictionary
	std::map<uint8_t, std::shared_ptr<CBlockEntry>> BlockEntries;

	// Expects textures to be inserted in order, 0-...
	void RegisterTexture(std::string texture);

	void RegisterBlock(EBlockType::Block block, std::vector<uint16_t> faceTextures);

};


// static std::vector<std::pair<int, std::string>> TextureIdsAndPaths {
// 	{0, "dirt.png"},
// 	{1, "grass_side.png"},
// 	{2, "grass_top.png"}
// };

#endif