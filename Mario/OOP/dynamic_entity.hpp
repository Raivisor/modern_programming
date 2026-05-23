#pragma once

#include "entity.hpp"

namespace sea {
	class Level;
	class Physics;
}

namespace sea {
	class DynamicEntity : public Entity {
		protected:
			float vx, vy;
			bool isAlive;
		public:
			DynamicEntity(float x, float y, float width, float height, 
					EntityType type, float vx, float vy);
			virtual ~DynamicEntity() = default;

			float getVX() const { return vx; }
			float getVY() const { return vy; }
			bool getIsAlive() const { return isAlive; }
			void setIsAlive(bool alive) { isAlive = alive; }

			void setVX(float newVX) { vx = newVX; }
			void setVY(float newVY) { vy = newVY; }

			bool hasGround(sea::Level& level) const;

			virtual void die() = 0;
			virtual void update(Level& level, Physics& physics) = 0;
	};
}
