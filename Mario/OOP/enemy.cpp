#include "enemy.hpp"

using namespace sea;

Enemy::Enemy(float x, float y, float width, float height, ObjectType type, float speed)
	: GameObject(float x, float y, float width, float height, ObjectType type) {
	this->speed = speed;	
}

void Enemy::update() {
	x += speed;n = int(input())
}
