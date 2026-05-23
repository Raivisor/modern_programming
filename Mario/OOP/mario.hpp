#pragma once

#include "dynamic_entity.hpp"

namespace sea {
	class Level;
	class Physics;
}

namespace sea {
	class Mario : public DynamicEntity {
		public:
			Mario(float x, float y, float width, float height,
				EntityType type, float vx, float vy);
			
			void die() override;
			void update(Level& level, Physics& physics) override;
			void onCollision(Entity& other) override;
			char getSymbol() const override;
	};
}
