#include <glm/glm.hpp>

class Light {
public:
	glm::vec3 lightDirection;
	glm::vec3 lightPosition;
	glm::vec3 lightAmbient;
	glm::vec3 lightDiffuse;
	glm::vec3 lightSpecular;

	glm::vec3 lightCutOff;
	glm::vec3 lightOuterCutOff;

	float constant;
	float linear;
	float quadratic;

	Light(glm::vec3 lightDirection, glm::vec3 lightPosition, glm::vec3 lightAmbient, glm::vec3 lightDiffuse, glm::vec3 lightSpecular, glm::vec3 lightCutOff, glm::vec3 lightOuterCutoff, float constant, float linear, float quadratic) {
		this->lightDirection = lightDirection;
		this->lightPosition = lightPosition;
		this->lightAmbient = lightAmbient;
		this->lightDiffuse = lightDiffuse;
		this->lightSpecular = lightSpecular;
		this->lightCutOff = lightCutOff;
		this->lightOuterCutOff = lightOuterCutOff;
		this->constant = constant;
		this->linear = linear;
		this->quadratic = quadratic;
	}

};