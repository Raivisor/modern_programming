#include "entity.hpp"

using namespace sea;

Entity::Entity(float x, float y, float width, float height, EntityType type)
	: x(x), y(y), width(width), height(height), type(type) {}

void Entity::setX(float newX) { x = newX; }

void Entity::setY(float newY) { y = newY; }

void Entity::setPos(float newX, float newY) { x = newX; y = newY; }
