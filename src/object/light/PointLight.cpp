#include <glm/glm.hpp>

class Light {
public:
	glm::vec3 lightPosition;
	glm::vec3 lightAmbient;
	glm::vec3 lightDiffuse;
	glm::vec3 lightSpecular;

	float constant;
	float linear;
	float quadratic;

	Light(glm::vec3 lightPosition, glm::vec3 lightAmbient, glm::vec3 lightDiffuse, glm::vec3 lightSpecular, float constant, float linear, float quadratic) {
		this->lightPosition = lightPosition;
		this->lightAmbient = lightAmbient;
		this->lightDiffuse = lightDiffuse;
		this->lightSpecular = lightSpecular;
		this->constant = constant;
		this->linear = linear;
		this->quadratic = quadratic;
	}

};