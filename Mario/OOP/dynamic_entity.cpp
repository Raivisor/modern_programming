#include "dynamic_entity.hpp"

using namespace sea;

DynamicEntity::DynamicEntity(float x, float y, float width, float height, EntityType type,
		float vx, float vy)
	: Entity(x, y, width, height, type), vx(vx), vy(vy), isAlive(true) {}
