#ifndef FACE_H
#define FACE_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace EFaceType {
	enum Face {
		Top,
		Bottom,
		Left,
		Right,
		Front,
		Back
	};
}

static std::vector<glm::vec3> CubeTopFace = {
	{ -0.5f,  0.5f, -0.5f },
	{  0.5f,  0.5f, -0.5f },
	{  0.5f,  0.5f,  0.5f },
	{  0.5f,  0.5f,  0.5f },
	{ -0.5f,  0.5f,  0.5f },
	{ -0.5f,  0.5f, -0.5f }
};

static std::vector<glm::vec3> CubeTopFaceFluid = {
	{ -0.5f,  0.4f, -0.5f },
	{  0.5f,  0.4f, -0.5f },
	{  0.5f,  0.4f,  0.5f },
	{  0.5f,  0.4f,  0.5f },
	{ -0.5f,  0.4f,  0.5f },
	{ -0.5f,  0.4f, -0.5f }
};

static std::vector<glm::vec3> CubeTopFaceNormals = {
	{ 0.0f,  1.0f,  0.0f },
	{ 0.0f,  1.0f,  0.0f },
	{ 0.0f,  1.0f,  0.0f },
	{ 0.0f,  1.0f,  0.0f },
	{ 0.0f,  1.0f,  0.0f },
	{ 0.0f,  1.0f,  0.0f }
};

static std::vector<glm::vec2> CubeTopFaceUVs = {
	{ 0.0f, 0.0f },
	{ 1.0f, 0.0f },
	{ 1.0f, 1.0f },
	{ 1.0f, 1.0f },
	{ 0.0f, 1.0f },
	{ 0.0f, 0.0f }
};

static std::vector<glm::vec3> CubeBottomFace = {
	{ -0.5f, -0.5f, -0.5f },
	{  0.5f, -0.5f, -0.5f },
	{  0.5f, -0.5f,  0.5f },
	{  0.5f, -0.5f,  0.5f },
	{ -0.5f, -0.5f,  0.5f },
	{ -0.5f, -0.5f, -0.5f }
};

static std::vector<glm::vec3> CubeBottomFaceNormals = {
	{ 0.0f, -1.0f, 0.0f },
	{ 0.0f, -1.0f, 0.0f },
	{ 0.0f, -1.0f, 0.0f },
	{ 0.0f, -1.0f, 0.0f },
	{ 0.0f, -1.0f, 0.0f },
	{ 0.0f, -1.0f, 0.0f }
};

static std::vector<glm::vec2> CubeBottomFaceUVs = {
	{ 0.0f, 0.0f },
	{ 1.0f, 0.0f },
	{ 1.0f, 1.0f },
	{ 1.0f, 1.0f },
	{ 0.0f, 1.0f },
	{ 0.0f, 0.0f }
};

static std::vector<glm::vec3> CubeLeftFace = {
	{ -0.5f,  0.5f,  0.5f },
	{ -0.5f,  0.5f, -0.5f },
	{ -0.5f, -0.5f, -0.5f },
	{ -0.5f, -0.5f, -0.5f },
	{ -0.5f, -0.5f,  0.5f },
	{ -0.5f,  0.5f,  0.5f }
};

static std::vector<glm::vec3> CubeLeftFaceFluid = {
	{ -0.5f,  0.4f,  0.5f },
	{ -0.5f,  0.4f, -0.5f },
	{ -0.5f, -0.5f, -0.5f },
	{ -0.5f, -0.5f, -0.5f },
	{ -0.5f, -0.5f,  0.5f },
	{ -0.5f,  0.4f,  0.5f }
};

static std::vector<glm::vec3> CubeLeftFaceNormals = {
	{ -1.0f, 0.0f, 0.0f },
	{ -1.0f, 0.0f, 0.0f },
	{ -1.0f, 0.0f, 0.0f },
	{ -1.0f, 0.0f, 0.0f },
	{ -1.0f, 0.0f, 0.0f },
	{ -1.0f, 0.0f, 0.0f }
};

static std::vector<glm::vec2> CubeLeftFaceUVs = {
	{ 0.0f, 0.0f },
	{ 1.0f, 0.0f },
	{ 1.0f, 1.0f },
	{ 1.0f, 1.0f },
	{ 0.0f, 1.0f },
	{ 0.0f, 0.0f }
};

static std::vector<glm::vec3> CubeRightFace = {
	{  0.5f,  0.5f,  0.5f },
	{  0.5f,  0.5f, -0.5f },
	{  0.5f, -0.5f, -0.5f },
	{  0.5f, -0.5f, -0.5f },
	{  0.5f, -0.5f,  0.5f },
	{  0.5f,  0.5f,  0.5f },
};

static std::vector<glm::vec3> CubeRightFaceFluid = {
	{  0.5f,  0.4f,  0.5f },
	{  0.5f,  0.4f, -0.5f },
	{  0.5f, -0.5f, -0.5f },
	{  0.5f, -0.5f, -0.5f },
	{  0.5f, -0.5f,  0.5f },
	{  0.5f,  0.4f,  0.5f },
};

static std::vector<glm::vec3> CubeRightFaceNormals = {
	{ 1.0f, 0.0f, 0.0f },
	{ 1.0f, 0.0f, 0.0f },
	{ 1.0f, 0.0f, 0.0f },
	{ 1.0f, 0.0f, 0.0f },
	{ 1.0f, 0.0f, 0.0f },
	{ 1.0f, 0.0f, 0.0f }
};

static std::vector<glm::vec2> CubeRightFaceUVs = {
	{ 0.0f, 0.0f },
	{ 1.0f, 0.0f },
	{ 1.0f, 1.0f },
	{ 1.0f, 1.0f },
	{ 0.0f, 1.0f },
	{ 0.0f, 0.0f }
};

static std::vector<glm::vec3> CubeFrontFace = {
	{ -0.5f, -0.5f,  0.5f },
	{  0.5f, -0.5f,  0.5f },
	{  0.5f,  0.5f,  0.5f },
	{  0.5f,  0.5f,  0.5f },
	{ -0.5f,  0.5f,  0.5f },
	{ -0.5f, -0.5f,  0.5f }
};

static std::vector<glm::vec3> CubeFrontFaceFluid = {
	{ -0.5f, -0.5f,  0.5f },
	{  0.5f, -0.5f,  0.5f },
	{  0.5f,  0.4f,  0.5f },
	{  0.5f,  0.4f,  0.5f },
	{ -0.5f,  0.4f,  0.5f },
	{ -0.5f, -0.5f,  0.5f }
};

static std::vector<glm::vec3> CubeFrontFaceNormals = {
	{ 0.0f,  0.0f,  1.0f },
	{ 0.0f,  0.0f,  1.0f },
	{ 0.0f,  0.0f,  1.0f },
	{ 0.0f,  0.0f,  1.0f },
	{ 0.0f,  0.0f,  1.0f },
	{ 0.0f,  0.0f,  1.0f }
};

static std::vector<glm::vec2> CubeFrontFaceUVs = {
	{ 1.0f, 1.0f },
	{ 0.0f, 1.0f },
	{ 0.0f, 0.0f },
	{ 0.0f, 0.0f },
	{ 1.0f, 0.0f },
	{ 1.0f, 1.0f }
};

static std::vector<glm::vec3> CubeBackFace = {
	{ -0.5f, -0.5f, -0.5f },
	{  0.5f, -0.5f, -0.5f },
	{  0.5f,  0.5f, -0.5f },
	{  0.5f,  0.5f, -0.5f },
	{ -0.5f,  0.5f, -0.5f },
	{ -0.5f, -0.5f, -0.5f }
};

static std::vector<glm::vec3> CubeBackFaceFluid = {
	{ -0.5f, -0.5f, -0.5f },
	{  0.5f, -0.5f, -0.5f },
	{  0.5f,  0.4f, -0.5f },
	{  0.5f,  0.4f, -0.5f },
	{ -0.5f,  0.4f, -0.5f },
	{ -0.5f, -0.5f, -0.5f }
};

static std::vector<glm::vec3> CubeBackFaceNormals = {
	{ 0.0f,  0.0f, -1.0f },
	{ 0.0f,  0.0f, -1.0f },
	{ 0.0f,  0.0f, -1.0f },
	{ 0.0f,  0.0f, -1.0f },
	{ 0.0f,  0.0f, -1.0f },
	{ 0.0f,  0.0f, -1.0f }
};

static std::vector<glm::vec2> CubeBackFaceUVs = {
	{ 1.0f, 1.0f },
	{ 0.0f, 1.0f },
	{ 0.0f, 0.0f },
	{ 0.0f, 0.0f },
	{ 1.0f, 0.0f },
	{ 1.0f, 1.0f }
};

#endif