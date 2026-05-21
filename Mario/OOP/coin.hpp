#pragma once

#include "dynamic_entity.hpp"
#include "physics.hpp"

namespace sea {
	class Coin : public DynamicEntity {
		public:
			Coin(float x, float y, float width, float height,
				EntityType type, float vx, float vy);

			void die() override;
			void update(sea::Level& level, sea::Physics& physics) override;
			char getSymbol() override;
	}
}
