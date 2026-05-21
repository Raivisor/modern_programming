#include "collision_handler.hpp"

using namespace sea;

bool CollisionHandler::isHorizontalCollision(const Entity& entity1, const Entity& entity2) {
	return (entity1.getX() < entity2.getX() + entity2.getWidth() &&
		entity2.getX() < entity1.getX() + entity1.getWidth());
}

bool CollisionHandler::isVerticalCollision(const Entity& entity1, const Entity& entity2) {
	return (entity1.getY() < entity2.getY() + entity2.getHeight() &&
		entity2.getY() < entity1.getY() + entity1.getHeight());
}
