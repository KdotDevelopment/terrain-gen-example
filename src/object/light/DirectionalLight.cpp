#include <glm/glm.hpp>

class Light {
public:
	glm::vec3 lightDirection;
	glm::vec3 lightAmbient;
	glm::vec3 lightDiffuse;
	glm::vec3 lightSpecular;

	Light(glm::vec3 lightDirection, glm::vec3 lightAmbient, glm::vec3 lightDiffuse, glm::vec3 lightSpecular) {
		this->lightDirection = lightDirection;
		this->lightAmbient = lightAmbient;
		this->lightDiffuse = lightDiffuse;
		this->lightSpecular = lightSpecular;
	}

};