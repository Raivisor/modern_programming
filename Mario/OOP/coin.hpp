#pragma once

#include "dynamic_entity.hpp"

namespace sea {
	class Level;
	class Physics;
}

namespace sea {
	class Coin : public DynamicEntity {
		public:
			Coin();
			Coin(float x, float y, float width, float height,
				EntityType type, float vx, float vy);

			void die() override;
			void update(sea::Level& level, sea::Physics& physics) override;
			char getSymbol() const override;
	};
}
