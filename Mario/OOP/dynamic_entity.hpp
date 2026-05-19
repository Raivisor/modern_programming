#pragma once

#include "entity.hpp"
#include "entity_type.hpp"

namespace sea {
	class DynamicEntity : public Entity {
		protected:
			float vx, vy;
			bool isAlive;
		private:
			DynamicEntity(float x, float y, float width, float height, EntityType type,
					float vx, float vy);
			virtual ~DynamicEntity() = default;

			float getVX() const { return vx; }
			float getVY() const { return vy; }
			bool isAlive() const { return isAlive; }

			void die() { isAlive = false; }

			virtual void update() = 0;
	};
}
