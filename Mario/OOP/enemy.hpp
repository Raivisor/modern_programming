#pragma once

#include "dynamic_entity.hpp"
#include "physics.hpp"

namespace sea {
	class Enemy : public DynamicEntity {
		public:
			Enemy(float x, float y, float width, float height, 
				EntityType type, float vx, float vy);

			void die() override;
			void update(sea::Level& level, sea::Physics& physics) override;
	};
}
