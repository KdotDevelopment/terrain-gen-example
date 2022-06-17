#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "Face.h"

class Cube {
public:
	Cube(glm::vec3 coordsInChunk, uint8_t blockType);

	void addFace(EFaceType::Face face);
	std::vector<glm::vec3> m_translateIntoChunk(std::vector<glm::vec3> verts, glm::vec3 trans);

	uint8_t m_blockType;
	glm::vec3 m_coordsInChunk;
	void getMesh(std::vector<glm::vec3>& verts, std::vector<glm::vec3>& normals, std::vector<glm::vec3>& uvs);
	void clear();
	
private:
	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec3> m_uvs;
};