#include "enemy.hpp"

#include "config.hpp"
#include "level.hpp"
#include "physics.hpp"

using namespace sea;

Enemy::Enemy() : DynamicEntity(0, 0, 0, 0, EntityType::ENEMY, 0, 0) {}

Enemy::Enemy(float x, float y, float width, float height, 
		EntityType type, float vx, float vy)
	: DynamicEntity(x, y, width, height, type, vx, vy) {}

void Enemy::die() { isAlive = false; } 

void Enemy::update(Level& level, Physics& physics) {
	if (!isAlive) return;

	bool hitWall = physics.moveHorizontal(*this, level);
	if(hitWall) {
		vx = -vx;	
	}

	Enemy future = *this;
	future.setX(future.getX() + future.getVX());
	future.setY(future.getY() + 2);

	if(!future.hasGround(level)) {
		vx = -vx;
	}

	physics.applyGravity(*this);
	physics.moveVertical(*this, level);
}

char Enemy::getSymbol() const {
	return Config::ENEMY_TYPE;
}
