#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../camera.h"

class Player {
public:
	Player();
	Player(glm::vec3 spawnPos);

	Camera camera;

private:
	
};