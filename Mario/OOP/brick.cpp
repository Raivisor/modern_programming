#include "brick.hpp"

#include "config.hpp"

using namespace sea;

Brick::Brick() : Entity(0, 0, 0, 0, EntityType::BLOCK_WALL) {}

Brick::Brick(float x, float y, float width, float height, EntityType type)
	: Entity(x, y, width, height, type) {}

void Brick::onCollision(Entity& other) {
	if(other.getType() == EntityType::PLAYER && getType() == EntityType::BLOCK_QUESTION) {
		type = EntityType::BLOCK_DASH;
	}
}

char Brick::getSymbol() const {
	switch(type) {
		case EntityType::BLOCK_DASH: return Config::BLOCK_DASH;
		case EntityType::BLOCK_DOOR: return Config::BLOCK_DOOR;
		case EntityType::BLOCK_QUESTION: return Config::BLOCK_QUESTION;
		case EntityType::BLOCK_WALL: return Config::BLOCK_WALL;
		default: return ' ';
	}
}
