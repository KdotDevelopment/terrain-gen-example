#include "Face.h"
#include "Cube.h"
#include "Block.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Cube::Cube(glm::vec3 coordsInChunk, uint8_t blockType) {
	m_blockType = blockType;
	m_coordsInChunk = coordsInChunk;
}

void Cube::addFace(EFaceType::Face face) {
	std::vector<glm::vec3> verts;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	switch (face) {
		case EFaceType::Top:
		{
			if (m_blockType == EBlockType::Water) {
				verts = CubeTopFaceFluid;
			}
			else {
				verts = CubeTopFace;
			}
			normals = CubeTopFaceNormals;
			uvs = CubeTopFaceUVs;

			break;
		}
		case EFaceType::Bottom:
		{
			verts = CubeBottomFace;
			normals = CubeBottomFaceNormals;
			uvs = CubeBottomFaceUVs;

			break;
		}
		case EFaceType::Left:
		{
			if (m_blockType == EBlockType::Water) {
				verts = CubeLeftFaceFluid;
			}
			else {
				verts = CubeLeftFace;
			}
			normals = CubeLeftFaceNormals;
			uvs = CubeLeftFaceUVs;

			break;
		}
		case EFaceType::Right:
		{
			if (m_blockType == EBlockType::Water) {
				verts = CubeRightFaceFluid;
			}
			else {
				verts = CubeRightFace;
			}
			normals = CubeRightFaceNormals;
			uvs = CubeRightFaceUVs;

			break;
		}
		case EFaceType::Front:
		{
			if (m_blockType == EBlockType::Water) {
				verts = CubeFrontFaceFluid;
			}
			else {
				verts = CubeFrontFace;
			}
			normals = CubeFrontFaceNormals;
			uvs = CubeFrontFaceUVs;

			break;
		}
		case EFaceType::Back:
		{
			if (m_blockType == EBlockType::Water) {
				verts = CubeBackFaceFluid;
			}
			else {
				verts = CubeBackFace;
			}
			normals = CubeBackFaceNormals;
			uvs = CubeBackFaceUVs;

			break;
		}
	}

	verts = m_translateIntoChunk(verts, m_coordsInChunk);
	m_vertices.insert(m_vertices.end(), verts.begin(), verts.end());

	m_normals.insert(m_normals.end(), normals.begin(), normals.end());

	std::shared_ptr<CBlockEntry> block = CBlockDictionary::GetInstance()->BlockEntries[m_blockType];
	uint16_t tex = block->FaceTextures[(uint16_t)face];

	std::vector<glm::vec3> uvws = {
		{ uvs[0].x, uvs[0].y, (float)tex },
		{ uvs[1].x, uvs[1].y, (float)tex },
		{ uvs[2].x, uvs[2].y, (float)tex },
		{ uvs[3].x, uvs[3].y, (float)tex },
		{ uvs[4].x, uvs[4].y, (float)tex },
		{ uvs[5].x, uvs[5].y, (float)tex },
	};

	m_uvs.insert(m_uvs.end(), uvws.begin(), uvws.end());
}

void Cube::getMesh(std::vector<glm::vec3>& verts, std::vector<glm::vec3>& normals, std::vector<glm::vec3>& uvs) {
	verts = m_vertices;
	normals = m_normals;
	uvs = m_uvs;
}

void Cube::clear() {
	m_vertices.clear();
	m_normals.clear();
	m_uvs.clear();
}

std::vector<glm::vec3> Cube::m_translateIntoChunk(std::vector<glm::vec3> verts, glm::vec3 trans) {
	for (int i = 0; i < verts.size(); i++) {
		verts[i].x += trans.x;
		verts[i].y += trans.y;
		verts[i].z += trans.z;
	}

	return verts;
}
