#include "player.h"

Player::Player() {

}

Player::Player(glm::vec3 spawnPos) {
	camera = Camera(spawnPos);
}