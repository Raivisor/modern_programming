#pragma once

#include "entity_type.hpp"

namespace sea {
	class Entity {
		protected:
			float x, y;
			float width, height;
			EntityType type;
		public:
			Entity(float x, float y, float width, float height, EntityType type);
			virtual ~Entity() = default;
			
			float getX() const { return x; }
			float getY() const { return y; }
			float getWidth() const { return width; }
			float getHeight() const { return height; }
			EntityType  getType() const { return type; }

			void setX(float newX);
			void setY(float newY);
			void setPos(float newX, float newY);

			virtual void onCollision(Entity& entity) {}
			virtual char getSymbol() const = 0;
	};
}
