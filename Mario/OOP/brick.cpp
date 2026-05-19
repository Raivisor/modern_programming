#include "brick.hpp"

using namespace sea;

Brick::Brick(float x, float y, float width, float height, ObjectType type)
	: Entity(x, y, width, height, type) {}

void Brick::onCollision(Entity& other) {
	if(other.getType() == EntityType::PLAYER && getType() == EntityType::BLOCK_QUESTION) {
		type = EntityType::BLOCK_DASH;
		//спавн монетки
	}

	if(other.getType() == EntityType::PLAYER && getType() == EntityType::BLOCK_DOOR) {
	
	}
}
