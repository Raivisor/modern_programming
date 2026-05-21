#include "coin.hpp"

#include "config.hpp"

using namespace sea;

Coin::Coin(float x, float y, float width, float height,
		EntityType type, float vx, float vy)
	: DynamicEntity(x, y, width, height, type, vx, vy) {}

void Coin::die() {
	isAlive = false;
}

void Coin::update(Level& level, Physics& physics) {
	if(!isAlive) return;

	bool hitWall = physics.moveHorizontal(*this, level);
	if(hitWall) {
		vx = -vx;
	}

	physics.applyGravity(*this);
	physics.moveVertical(*this, level);

	if(y + height< 0 || y > Config::MAP_HEIGHT) {
		die();
	}
}

char Coin::getSymbol() {
	return Config::COIN_TYPE;
}
