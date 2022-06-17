#include "generator/OpenSimplexNoise.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include "Chunk.h"
#include "World.h"
#include "../camera.h"
#include "../shader.h"
#include "generator/TerrainGenerator.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

bool terrainGenerated = false;

int seed = 1234;// rand() % 100000000;

TerrainGenerator generator;

/*Chunk World::getChunk(int chunkX, int chunkY, int chunkZ) {
	//std::cout << chunkArray[chunkX][chunkY][chunkZ].chunkX << " " << chunkArray[chunkX][chunkY][chunkZ].chunkZ << std::endl;
	return chunkArray[chunkX][chunkY][chunkZ];
}*/

void World::loadWorld() {
	if (terrainGenerated) return;
	/*int chunkNum = 0;
	for (int x = 0; x < worldChunkSize; x++) {
		for (int y = 0; y < worldChunkSize; y++) {
			for (int z = 0; z < worldChunkSize; z++) {
				std::cout << "Chunk #" << chunkNum << " being generated" << std::endl;
				chunkArray[x][y][z] = Chunk(x, y, z, seed);
				chunkArray[x][y][z].load();
				if (chunkArray[x][y][z].meshReady) {
					std::cout << "Mesh is Ready" << std::endl;
					chunkArray[x][y][z].uploadMesh();
				}
				std::cout << chunkArray[x][y][z].chunkX << std::endl;
				std::cout << "Chunk #" << chunkNum << " Generated" << std::endl;
				chunkNum++;
			}
		}
	}*/

	//std::cout << "Loading World" << std::endl;
	
	for (int x = -4; x < 20; x++) {
		for (int z = -20; z < 4; z++) {
			for (int y = 0; y < 8; y++) { //8*16 = 128 block height limit
				//std::cout << "Pushing Chunk" << std::endl;
				m_chunkLoaderQueue.push({ x, y, z });
				//std::cout << "Chunk Pushed" << std::endl;
			}
		}
	}

	for (int i = 0; i < 5; i++) {
		m_generatorThreads.push_back(std::thread([&]() {
			m_loadChunks();
		}));
	}

	m_generatorRunning = true;

	terrainGenerated = true;
	
}

World::World() {
	srand(time(0));
	seed = rand() % 100000000;
	generator = TerrainGenerator(seed);
}

void World::SetTextureMap(unsigned int map) {
	m_textureMapID = map;
}

std::vector<std::shared_ptr<Chunk>> World::GetRenderableChunks() {
	std::vector<std::shared_ptr<Chunk>> chunks;

	for (auto& chunk : m_chunks) {
		// Should the chunk be rendererd ?
		//if (chunk.second->shouldRender) {

			m_chunkLoderMutex.lock();

			if (chunk.second->meshReady) {
				chunk.second->uploadMesh();
			}

			m_chunkLoderMutex.unlock();

			// If not, add it
			chunks.push_back(chunk.second);

		//}
	}
	return chunks;
}


void World::m_loadChunks() {
	while (m_generatorRunning) {
		m_chunkLoderMutex.lock();

		glm::vec3 coords = m_chunkLoaderQueue.front();
		m_chunkLoaderQueue.pop();

		m_chunkLoderMutex.unlock();

		std::shared_ptr<Chunk> loadingChunk = std::make_shared<Chunk>(coords.x, coords.y, coords.z, generator);
		loadingChunk->shouldRender = true;
		//std::cout << "Loaded chunk " << coords.x << ":" << coords.y << ":" << coords.z << std::endl;

		m_chunkLoderMutex.lock();

		m_chunks[coords] = loadingChunk;

		m_chunkLoderMutex.unlock();

		while (m_chunkLoaderQueue.empty()) {
			if (!m_generatorRunning) break;

			static std::chrono::milliseconds dura(1);
			std::this_thread::sleep_for(dura);
		}

	}
}

void World::render(Camera camera, Shader shader) {
	glBindTexture(GL_TEXTURE_2D_ARRAY, m_textureMapID);

	std::vector<std::shared_ptr<Chunk>> chunks = GetRenderableChunks();
	
	for (int i = 0; i < chunks.size(); i++) {
		chunks[i]->render(shader, camera);
	}
}

void World::getVAO(unsigned int cubeVAO) {
	//for (int x = 0; x < worldChunkSize; x++) {
	//	for (int y = 0; y < worldChunkSize; y++) {
	//		for (int z = 0; z < worldChunkSize; z++) {
	//			chunkArray[x][y][z].getVAO(cubeVAO);
	//		}
	//	}
	//}
}

World::~World() {

	m_generatorRunning = false;

	for (int i = 0; i < m_generatorThreads.size(); i++) {
		m_generatorThreads[i].join();
	}

	for (auto& chunk : m_chunks) {

		chunk.second->unload();

	}

}

