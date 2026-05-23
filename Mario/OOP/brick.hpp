#pragma once

#include "entity.hpp"
#include "entity_type.hpp"

namespace sea {
	class Brick : public Entity {
		public:
			Brick();
			Brick(float x, float y, float width, float height, EntityType type);
			
			void onCollision(Entity& other) override;
			char getSymbol() const override;
	};
}
