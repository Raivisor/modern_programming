#pragma once

#include "dynamic_entity.hpp"
#include "level.hpp"
#include "physics.hpp"

namespace sea {
	class Mario : public DynamicEntity {
		public:
			Mario(float x, float y, float width, float height,
				EntityType type, float vx, float vy);
			
			void die() override;
			void update(sea::Level& level, sea::Physics& physics) override;
			void OnCollision(sea::Entity& other) override;
			char getSymbol() override;
	}
}
