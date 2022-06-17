#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../lib/stb_image.h"

#include "Texture.h"

unsigned int Texture::LoadTextures(std::vector<std::string> textures) {

	std::string basePath = "res/textures/";

	int x = 16;
	int y = 16;

	int layers = textures.size();
	uint8_t* texels = (GLubyte*)malloc(x * y * 4 * layers * sizeof(uint8_t));

	for (int i = 0; i < layers; i++) {

		std::string path = basePath + textures[i];

		int xR = 0;
		int yR = 0;
		int cR = 0;

		unsigned char* texture = stbi_load(path.c_str(), &xR, &yR, &cR, STBI_rgb_alpha);

		memcpy(texels + (i * x * y * 4), texture, x * y * 4);

		stbi_image_free(texture);

	}

	unsigned int textureArray = 0;

	glGenTextures(1, &textureArray);
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);

	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, x, y, layers, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, x, y, layers, GL_RGBA, GL_UNSIGNED_BYTE, texels);
	

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

	free(texels);

	return textureArray;

}