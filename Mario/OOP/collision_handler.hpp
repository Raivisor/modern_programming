#pragma once

#include "entity.hpp"

namespace sea {
	class CollisionHandler {
		public:
			static bool isHorizontalCollision(const Entity& a, const Entity& b);

			static bool isVerticalCollision(const Entity& a, const Entity& b);

			static bool isCollisionDoor(const Entity& a, const Entity& b);

			static bool isCollisionQuestion(const Entity& a, const Entity& b);

			static bool isCollision(const Entity& a, const Entity& b);
	};
}
