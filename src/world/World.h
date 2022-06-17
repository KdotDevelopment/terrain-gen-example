#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <unordered_map>
#include <thread>
#include <mutex>
#include <queue>

#include "../camera.h"
#include "../shader.h"
#include "Chunk.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Chunk;

class World {
public:

	static const unsigned int worldChunkSize = 2;

	//Chunk chunkArray[worldChunkSize][1][worldChunkSize];

	Chunk getChunk(int chunkX, int chunkY, int chunkZ);;
	//World();
	void loadWorld();
	void getVAO(unsigned int cubeVAO);
	World();

	std::vector<std::shared_ptr<Chunk>> GetRenderableChunks();

	void SetTextureMap(GLuint map);

	void render(Camera camera, Shader shader);

	~World();

private:

	std::vector<std::thread> m_generatorThreads;
	bool m_generatorRunning = false;

	unsigned int m_textureMapID;

	std::unordered_map<glm::vec3, std::shared_ptr<Chunk>> m_chunks;

	//std::unordered_map<glm::vec2, std::shared_ptr<Chunk>> m_ints;

	std::mutex m_chunkUpdaterMutex;
	std::queue<glm::vec3> m_chunkUpdatesQueue;

	std::mutex m_chunkLoderMutex;
	std::queue<glm::vec3> m_chunkLoaderQueue;

	void m_loadChunks();

};
#endif
