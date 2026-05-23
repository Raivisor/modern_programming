#include "physics.hpp"

#include "collision_handler.hpp"
#include "config.hpp"

using namespace sea;

bool Physics::moveHorizontal(DynamicEntity& entity, Level& level) {
	entity.setX(entity.getX() + entity.getVX());
	
	const Brick* bricks = level.getBricks();
	int brickCount = level.getBrickCount();

	for(int i = 0; i < brickCount; i++) {
		if(CollisionHandler::isCollision(entity, bricks[i])) {
			entity.setX(entity.getX() - entity.getVX());
			return true;
		}
	}

	return false;
}

void Physics::applyGravity(DynamicEntity& entity) {
	entity.setVY(entity.getVY() + Config::GRAVITY);
}

bool Physics::moveVertical(DynamicEntity& entity, Level& level) {
	entity.setY(entity.getY() + entity.getVY());

	const Brick* bricks = level.getBricks();
	int brickCount = level.getBrickCount();
	
	for(int i = 0; i < brickCount; i++) {
		if(CollisionHandler::isCollision(entity, bricks[i])) {
			entity.setY(entity.getY() - entity.getVY());
			entity.setVY(0);
			return true; 
		}
	}

	return false;
}
