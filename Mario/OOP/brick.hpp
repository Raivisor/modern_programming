#pragma once

#include "entity.hpp"

namespace sea {
	class Brick : public Entity {
		public:
			Brick(float x, float y, float width, float height, EntityType type);
			
			void onCollision(Entity& other) override; 
	}
}
