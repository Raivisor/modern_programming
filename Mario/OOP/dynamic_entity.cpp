#include "dynamic_entity.hpp"

#include "collision_handler.hpp"
#include "level.hpp"
#include "physics.hpp"

using namespace sea;

DynamicEntity::DynamicEntity(float x, float y, float width, float height, EntityType type,
		float vx, float vy)
	: Entity(x, y, width, height, type), vx(vx), vy(vy), isAlive(true) {}

bool DynamicEntity::hasGround(Level& level) const {
	const Brick* bricks = level.getBricks();
	int brickCount = level.getBrickCount();

	for(int i = 0; i < brickCount; i++) {
		if(CollisionHandler::isCollision(*this, bricks[i])) {
			return true;
		}
	}

	return false;
}
