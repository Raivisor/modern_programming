#pragma once

#include "entity.hpp"

namespace sea {
	class CollisionHandler {
		public:
			static bool isHorizontalCollision(const Entity& entity1, const Entity& entity2);

			static bool isVerticalCollision(const Entity& entity1, const Entity& entity2);
	}
}
