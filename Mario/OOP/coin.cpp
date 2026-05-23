#include "coin.hpp"

#include "config.hpp"
#include "level.hpp"
#include "physics.hpp"

using namespace sea;

Coin::Coin() : DynamicEntity(0, 0, 0, 0, EntityType::COIN, 0, 0) {}

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

char Coin::getSymbol() const {
	return Config::COIN_TYPE;
}
