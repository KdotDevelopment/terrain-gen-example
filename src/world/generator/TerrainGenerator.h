#pragma once
#ifndef TERRAIN_GENERATOR_H
#define TERRAIN_GENERATOR_H

#include "../ChunkContainer.h"
#include "../../object/Block.h"
#include "../../lib/FastNoiseLite.h"
#include "OpenSimplexNoise.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <tuple>

class TerrainGenerator {
public:

	int seed;

	float smoothness = 1.0f;
	int octaves = 3;
	float riverWidth = 0.1f;
	float riverFrequency = 5; //LOWER = MORE RIVERS!!
	float caveFrequency = 1.0f; //HIGHER = MORE CAVES!!
	float caveWidth = 0.08f;
	int densityFloor = 8;

	int seaLevel = 48;


	FastNoiseLite noise;
	FastNoiseLite multiplierNoise;
	FastNoiseLite riverNoise;
	FastNoiseLite caveNoise1;
	FastNoiseLite caveNoise2;
	FastNoiseLite blobNoise;

	ChunkContainer *chunk;

	TerrainGenerator(int seed) {
		this->seed = seed;

		noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
		noise.SetSeed(seed);

		multiplierNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
		multiplierNoise.SetSeed(seed + 123);

		riverNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
		riverNoise.SetSeed(seed + 1);

		caveNoise1.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
		caveNoise1.SetSeed(seed + 2);

		caveNoise2.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
		caveNoise2.SetSeed(seed + 3);

		blobNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
		blobNoise.SetSeed(seed + 4);
	}

	TerrainGenerator() {

	}

	uint8_t blockAt(int x, int y, int z) {
		if (x > 16 - 1) return 0;
		if (y > 16 - 1) return 0;
		if (z > 16 - 1) return 0;
		if (x < 0) return 0;
		if (y < 0) return 0;
		if (z < 0) return 0;

		return chunk->blockArray[x][y][z];
	}

	void setBlock(int x, int y, int z, uint8_t blockType) {
		chunk->blockArray[x][y][z] = blockType;
	}

	/*void generateTerrain(ChunkContainer* achunk) {
		this->chunk = achunk;
		//BASE TERRAIN
		for (int x = 0; x < 16; x++) {
			for (int y = 0; y < 16; y++) {
				for (int z = 0; z < 16; z++) {
					int blockX = x + (chunk->chunkX * 16);
					int blockY = y + (chunk->chunkY * 16);
					int blockZ = z + (chunk->chunkZ * 16);
					
					//uint8_t stage1 = getBlock(blockX, blockY, blockZ);
					//chunk->blockArray[x][y][z] = stage1;
					if (blockY == 0) {
						chunk->blockArray[x][y][z] = EBlockType::Bedrock;
						continue;
					}
					OpenSimplexNoise::Noise noise = OpenSimplexNoise::Noise(seed);
					

					float amp = 1;
					int multiplier = 1;
					double value = 1;

					for (int i = 1; i <= octaves; i++) {
						value += amp * noise.eval(multiplier * (blockX / smoothness), multiplier * (blockZ / smoothness));
						amp = amp / 2;
						multiplier = multiplier * 2;
					}

					if (value <= 0)
						value = 0.001;

					value = pow(value, 3.0f);

					value /= 3;

					value += 0.3f;

					double multiply = noise.eval(blockX / (smoothness * 10), blockY / (smoothness * 10), blockZ / (smoothness * 10));
					multiply += 0.7f;

					if (multiply <= 0.3f)
						multiply = 0.301f;

					value *= multiply;

					carveRiver(&value, blockX, blockY, blockZ);

					value = (value * 24) + 8;

					if ((int)value == blockY && blockY >= 13) {
						chunk->blockArray[x][y][z] = EBlockType::Grass;
						continue;
					}
					if ((int)value == blockY && blockY < 13) {
						chunk->blockArray[x][y][z] = EBlockType::Dirt;
						continue;
					}
					if ((int)value - blockY == 1.0f) {
						chunk->blockArray[x][y][z] = EBlockType::Dirt;
						continue;
					}
					if ((int)value - blockY == 2.0f) {
						chunk->blockArray[x][y][z] = EBlockType::Dirt;
						continue;
					}
					if (blockY < 14 && !((int)value > blockY)) {
						chunk->blockArray[x][y][z] = EBlockType::Water;
						continue;
					}
					else if ((int)value > blockY) {
						chunk->blockArray[x][y][z] = EBlockType::Stone;
						continue;
					}
					else {
						chunk->blockArray[x][y][z] = EBlockType::Air;
						continue;
					}
				}
			}
		}
	}*/

	void generateDensityTerrain(ChunkContainer* achunk) {
		this->chunk = achunk;
		//BASE TERRAIN
		for (int x = 0; x < 16; x++) {
			int blockX = x + (chunk->chunkX * 16);

			for (int y = 0; y < 16; y++) {
				int blockY = y + ((chunk->chunkY - (int)(seaLevel/16)) * 16);

				for (int z = 0; z < 16; z++) {
					int blockZ = z + (chunk->chunkZ * 16);

					if (blockY == -seaLevel) {
						chunk->blockArray[x][y][z] = EBlockType::Bedrock;
						continue;
					}
					//OpenSimplexNoise::Noise noise = OpenSimplexNoise::Noise(seed);

					/*double densvalue = 0;
					if (blockY < seaLevel) {
						float densamp = 1;
						int densmultiplier = 1;
						

						for (int i = 1; i <= octaves; i++) {
							//densvalue += densamp * noise.eval(densmultiplier * (blockX / smoothness), densmultiplier * ((blockY) / smoothness), densmultiplier * (blockZ / smoothness));
							densvalue += densamp * noise.GetNoise(densmultiplier * (blockX / smoothness), densmultiplier * ((blockY + seaLevel) / smoothness), densmultiplier * (blockZ / smoothness));
							densamp = densamp / 2;
							densmultiplier = densmultiplier * 2;
						}

						densvalue /= 5.0f;

						densvalue += 0.3f;

						carveRiver(&densvalue, blockX, blockY, blockZ);

						//densvalue -= pow(blockY * 0.009f, 1.03f);
						densvalue -= blockY * 0.009f;

						//float multiplier = noise.eval(blockX / (smoothness*4), blockZ / (smoothness*4));
						float multiplier = multiplierNoise.GetNoise(blockX / (smoothness * 4), blockZ / (smoothness * 4));
						if (multiplier <= 0.0f)
							multiplier = 0.01f;
						multiplier += 0.1f;

						densvalue *= multiplier;
					}
					else {
						densvalue = 1.0f;
					}*/

					double densvalue = getDensityAt(blockX, blockY, blockZ);

					if (densvalue > 0.0f) {
						chunk->blockArray[x][y][z] = EBlockType::Stone;
					}
					else {
						chunk->blockArray[x][y][z] = EBlockType::Air;
					}

					if (chunk->blockArray[x][y][z] == EBlockType::Air && blockY <= 14 && blockY >= 0) {
						chunk->blockArray[x][y][z] = EBlockType::Water;
					}

					carveCaves(&densvalue, blockX, blockY, blockZ, x, y, z);

					if (densvalue > 0.0f) {
						chunk->blockArray[x][y][z] = EBlockType::Stone;
					}
					else {
						if(chunk->blockArray[x][y][z] != EBlockType::Water)
							chunk->blockArray[x][y][z] = EBlockType::Air;
					}

					
					if (blockY >= 14) {
						if (chunk->blockArray[x][y][z] == EBlockType::Stone && (getDensityAt(blockX, blockY + 1, blockZ) <= 0.0f)) {
							chunk->blockArray[x][y][z] = EBlockType::Grass;
						}
						if (chunk->blockArray[x][y][z] == EBlockType::Stone && (getDensityAt(blockX, blockY + 2, blockZ) <= 0.0f) && (getDensityAt(blockX, blockY + 1, blockZ) >= 0.0f)) {
							chunk->blockArray[x][y][z] = EBlockType::Dirt;
						}
						if (chunk->blockArray[x][y][z] == EBlockType::Stone && (getDensityAt(blockX, blockY + 3, blockZ) <= 0.0f) && (getDensityAt(blockX, blockY + 1, blockZ) >= 0.0f) && (getDensityAt(blockX, blockY + 2, blockZ) >= 0.0f)) {
							chunk->blockArray[x][y][z] = EBlockType::Dirt;
						}
						
					}
					placeBlobs(&densvalue, blockX, blockY, blockZ);
					if (densvalue == -3.0f) {
						if (chunk->blockArray[x][y][z] == EBlockType::Stone)
							chunk->blockArray[x][y][z] = EBlockType::Dirt;
					}
				}
			}
		}
	}

	void carveRiver(double *value, int blockX, int blockY, int blockZ) {
		//OpenSimplexNoise::Noise riverNoise = OpenSimplexNoise::Noise(seed + 1);

		float amp = 1;
		int multiplier = 1;
		double riverValue = 0;

		for (int i = 1; i <= 3; i++) {
			//riverValue += amp * riverNoise.eval(multiplier * (blockX / (smoothness * riverFrequency)), multiplier * (blockZ / (smoothness * riverFrequency)));
			riverValue += amp * riverNoise.GetNoise(multiplier * (blockX / (1.0 * riverFrequency)), multiplier * (blockZ / (1.0 * riverFrequency)));
			amp = amp / 2;
			multiplier = multiplier * 2;
		}

		//riverValue = riverNoise.eval(blockX / (smoothness * riverFrequency), blockZ / (smoothness * riverFrequency));

		//riverValue /= 2;

		if (riverValue > -riverWidth && riverValue < riverWidth) {
			riverValue *= (1 / riverWidth);
			*value = *value * abs(riverValue);
		}
	}

	void carveCaves(double* value, int blockX, int blockY, int blockZ, int x, int y, int z) {
		if (blockY < 64 && chunk->blockArray[x][y][z] != EBlockType::Water) {
			/*OpenSimplexNoise::Noise caveNoise1 = OpenSimplexNoise::Noise(seed + 2);
			OpenSimplexNoise::Noise caveNoise2 = OpenSimplexNoise::Noise(seed + 3);

			double caveValue1 = caveNoise1.eval(blockX / (smoothness / caveFrequency), blockY / (smoothness / caveFrequency), blockZ / (smoothness / caveFrequency));
			double caveValue2 = caveNoise2.eval(blockX / (smoothness / caveFrequency), blockY / (smoothness / caveFrequency), blockZ / (smoothness / caveFrequency));*/

			float amp = 1;
			int multiplier = 1;
			double caveValue1 = 0;
			double caveValue2 = 0;

			for (int i = 1; i <= 3; i++) {
				//riverValue += amp * riverNoise.eval(multiplier * (blockX / (smoothness * riverFrequency)), multiplier * (blockZ / (smoothness * riverFrequency)));
				caveValue1 += amp * caveNoise1.GetNoise(multiplier * blockX / (smoothness / caveFrequency), multiplier * blockY / (smoothness / caveFrequency), multiplier * blockZ / (smoothness / caveFrequency));
				caveValue2 += amp * caveNoise2.GetNoise(multiplier * blockX / (smoothness / caveFrequency), multiplier * blockY / (smoothness / caveFrequency), multiplier * blockZ / (smoothness / caveFrequency));
				amp = amp / 2;
				multiplier = multiplier * 2;
			}

			//double caveValue1 = caveNoise1.GetNoise(blockX / (smoothness / caveFrequency), blockY / (smoothness / caveFrequency), blockZ / (smoothness / caveFrequency));
			//double caveValue2 = caveNoise2.GetNoise(blockX / (smoothness / caveFrequency), blockY / (smoothness / caveFrequency), blockZ / (smoothness / caveFrequency));

			/*if ((caveValue1 > -caveWidth && caveValue1 < caveWidth) && (caveValue2 > -caveWidth && caveValue2 < caveWidth)) {
				*value = 1.0f;
			}
			else {
				*value = -1.0f;
			}*/

			if ((caveValue1 > -caveWidth && caveValue1 < caveWidth) && (caveValue2 > -caveWidth && caveValue2 < caveWidth)) {
				*value = -2.0f;
			}
		}
	}

	void placeBlobs(double* value, int blockX, int blockY, int blockZ) {
		if (blobNoise.GetNoise(blockX * 4.5f, blockY * 4.5f, blockZ * 4.5f) > 0.7f) {
			*value = -3.0f;
		}
	}

	double getDensityAt(int blockX, int blockY, int blockZ) {
		double densvalue = 0;
		if (blockY > 0.0f) {
			float densamp = 1;
			int densmultiplier = 1;


			for (int i = 1; i <= octaves; i++) {
				//densvalue += densamp * noise.eval(densmultiplier * (blockX / smoothness), densmultiplier * ((blockY) / smoothness), densmultiplier * (blockZ / smoothness));
				densvalue += densamp * noise.GetNoise(densmultiplier * (blockX / smoothness), densmultiplier * ((blockY + seaLevel) / smoothness), densmultiplier * (blockZ / smoothness));
				densamp = densamp / 2;
				densmultiplier = densmultiplier * 2;
			}

			densvalue /= 5.0f;

			densvalue += 0.3f;

			carveRiver(&densvalue, blockX, blockY, blockZ);

			//densvalue -= pow(blockY * 0.009f, 1.03f);
			densvalue -= blockY * 0.009f;

			//float multiplier = noise.eval(blockX / (smoothness*4), blockZ / (smoothness*4));
			float multiplier = multiplierNoise.GetNoise(blockX / (smoothness * 4), blockZ / (smoothness * 4));
			if (multiplier <= 0.0f)
				multiplier = 0.01f;
			multiplier += 0.1f;

			densvalue *= multiplier;
		}
		else {
			densvalue = 1.0f;
		}
		return densvalue;
	}


};

#endif