#include "enemy.hpp"

using namespace sea;

Enemy::Enemy(float x, float y, float width, float height, 
		Entitytype, float vx, float vy)
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
	future.setY(future.getY() + 1);

	if(!future.hasGround(level)) {
		vy = -vy;
	}

	physics.applyGravity(*this);
	physics.moveVertical(*this, level);
}
