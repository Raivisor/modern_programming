#include "collision_handler.hpp"

using namespace sea;

bool CollisionHandler::isHorizontalCollision(const Entity& a, const Entity& b) {
	return (a.getX() < b.getX() + b.getWidth() &&
		b.getX() < a.getX() + a.getWidth());
}

bool CollisionHandler::isVerticalCollision(const Entity& a, const Entity& b) {
	return (a.getY() < b.getY() + b.getHeight() &&
		b.getY() < a.getY() + a.getHeight());
}

bool CollisionHandler::isCollisionDoor(const Entity& a, const Entity& b) {
	if (a.getX() + a.getWidth() <= b.getX()) return false;
	if (a.getX() >= b.getX() + b.getWidth()) return false;
	return (a.getY() + a.getHeight() >= b.getY() - 0.5f && 
		a.getY() + a.getHeight() <= b.getY());
}

bool CollisionHandler::isCollisionQuestion(const Entity& a, const Entity& b) {
	if (a.getX() + a.getWidth() <= b.getX()) return false;
	if (a.getX() >= b.getX() + b.getWidth()) return false;
	return (a.getY() <= b.getY() + b.getHeight() + 0.5f &&
		a.getY() >= b.getY() + b.getHeight());
}

bool CollisionHandler::isCollision(const Entity& a, const Entity& b) {
	return isHorizontalCollision(a, b) && isVerticalCollision(a, b);
}
