#pragma once

#include "entity.hpp"

namespace sea {
	class Enemy : public DynamicEntity {
		private:
			float speed;
		public:
			Enemy(float x, float y, float width, float height, ObjectType type, float speed);

			void update();
	};
}
