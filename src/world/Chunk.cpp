#include "World.h"
#include "Chunk.h"
#include "../shader.h"
#include "../camera.h"
#include "../object/Cube.h"
#include "../object/Face.h"
#include "../object/Block.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "generator/OpenSimplexNoise.h"
//#include "generator/TerrainGenerator.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Chunk::Chunk(int chunkX, int chunkY, int chunkZ, TerrainGenerator generator) {
	this->chunkInfo.chunkX = chunkX;
	this->chunkInfo.chunkY = chunkY;
	this->chunkInfo.chunkZ = chunkZ;
	this->generator = generator;
	//std::cout << chunkX << " " << chunkY << " " << chunkZ << std::endl;
	unsigned int blockNum = 0;
	
	/*for (int x = 0; x < sizeX; x++) {
		for (int y = 0; y < sizeY; y++) {
			for (int z = 0; z < sizeZ; z++) {
				int blockType = getBlock(x+(chunkX*sizeX), y+(chunkY*sizeY), z+(chunkZ*sizeZ), 80.0f);
				if (blockType == EBlockType::Stone) {
					chunkBlockArray[x][y][z] = EBlockType::Stone;
				}
				else {
					chunkBlockArray[x][y][z] = EBlockType::Air;
					blockNum++;
				}
			}
		}
	}*/
	generator.generateDensityTerrain(&chunkInfo);
	//if(blockNum < (sizeX * sizeY * sizeZ))
	load();
}

Chunk::Chunk() {

}

void Chunk::load() {
	//std::cout << "Loading Chunk!!" << std::endl;
	if (loaded)
		return;

	m_model = glm::translate(glm::mat4(1.0f), { chunkInfo.chunkX * sizeX, chunkInfo.chunkY * sizeY, chunkInfo.chunkZ * sizeZ });
	m_mesh();
	loaded = true;
	return;

}

void Chunk::render(Shader lightingShader, Camera camera) {
	glBindVertexArray(m_vao);
	lightingShader.use();
	lightingShader.setMat4("model", m_model);
	//std::cout << m_vao << std::endl;
	glDrawArrays(GL_TRIANGLES, 0, m_numVerts);
}

void Chunk::updateChunk() {
	m_mesh();
}

void Chunk::m_mesh() {
	bool isEmpty();
	int emptyIndex = 0;
	for (int x = 0; x < sizeX; x++) {
		for (int y = 0; y < sizeY; y++) {
			for (int z = 0; z < sizeZ; z++) {
				uint8_t block = blockAt(x, y, z);

				if (block == EBlockType::Air) {
					emptyIndex++;
					continue;
				}

				std::vector<glm::vec3> tempVerts;
				std::vector<glm::vec3> tempNormals;
				std::vector<glm::vec3> tempUVs;

				Cube tmp({ x,y,z }, block);
				if (blockAt(x + 1, y, z) == EBlockType::Air || (blockAt(x + 1, y, z) == EBlockType::Water && !(blockAt(x, y, z) == EBlockType::Water)))
					tmp.addFace(EFaceType::Right);
				if (blockAt(x - 1, y, z) == EBlockType::Air || (blockAt(x - 1, y, z) == EBlockType::Water && !(blockAt(x, y, z) == EBlockType::Water)))
					tmp.addFace(EFaceType::Left);
				if (blockAt(x, y + 1, z) == EBlockType::Air || (blockAt(x, y + 1, z) == EBlockType::Water && !(blockAt(x, y, z) == EBlockType::Water)))
					tmp.addFace(EFaceType::Top);
				if (blockAt(x, y - 1, z) == EBlockType::Air || (blockAt(x, y - 1, z) == EBlockType::Water && !(blockAt(x, y, z) == EBlockType::Water)))
					tmp.addFace(EFaceType::Bottom);
				if (blockAt(x, y, z + 1) == EBlockType::Air || (blockAt(x, y, z + 1) == EBlockType::Water && !(blockAt(x, y, z) == EBlockType::Water)))
					tmp.addFace(EFaceType::Front);
				if (blockAt(x, y, z - 1) == EBlockType::Air || (blockAt(x, y, z - 1) == EBlockType::Water && !(blockAt(x, y, z) == EBlockType::Water)))
					tmp.addFace(EFaceType::Back);


				tmp.getMesh(tempVerts, tempNormals, tempUVs);

				m_vertices.insert(m_vertices.end(), tempVerts.begin(), tempVerts.end());
				m_normals.insert(m_normals.end(), tempNormals.begin(), tempNormals.end());
				m_uvs.insert(m_uvs.end(), tempUVs.begin(), tempUVs.end());

				tmp.clear();
			}
		}
	}
	if (!(emptyIndex == sizeX * sizeY * sizeZ)) {
		meshReady = true;
	}
}

void Chunk::unload() {
	m_vertices.clear();
	m_uvs.clear();

	glBindVertexArray(m_vao);

	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);

	loaded = false;
}

void Chunk::uploadMesh() {
	
	if (!meshReady || !loaded)
		return;

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	std::vector<glm::vec3> data;
	data.insert(data.end(), m_vertices.begin(), m_vertices.end()); 
	data.insert(data.end(), m_normals.begin(), m_normals.end());
	data.insert(data.end(), m_uvs.begin(), m_uvs.end());

	m_numVerts = m_vertices.size();

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), &data[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const void*)(m_vertices.size() * sizeof(glm::vec3)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (const void*)((m_vertices.size() + m_normals.size()) * sizeof(glm::vec3)));

	m_vertices.clear();
	m_normals.clear();
	m_uvs.clear();

	data.clear();

	glBindVertexArray(0);

	meshReady = !meshReady;

}

void Chunk::getVAO(unsigned int cubeVAO) {
	this->cubeVAO = cubeVAO;
}

uint8_t Chunk::blockAt(int x, int y, int z) {
	if (x > sizeX - 1) return 0;
	if (y > sizeY - 1) return 0;
	if (z > sizeZ - 1) return 0;
	if (x < 0) return 0;
	if (y < 0) return 0;
	if (z < 0) return 0;

	return chunkInfo.blockArray[x][y][z];
}

Chunk::~Chunk() {
	//unload();
}
