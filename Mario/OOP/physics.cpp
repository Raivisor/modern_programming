#include "physics.hpp"

#include "collision_handler.hpp"

using namespace sea;

bool Physics::moveHorizontal(DynamicEntity& entity, Level& level) {
	entity.setX(entity.getX() + entity.getVX());

	for(const auto& brick : level.getBricks()) {
		if(CollisionHandler::isCollision(entity, brick)) {
			entity.setX(entity.getX() - entity.getVX());
			return true;			
		}
	}

	return false;
}

Physics::moveVerical(DynamicEntity& entity, Level& level) {
	
}
