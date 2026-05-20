#pragma once

#include "dynamic_entity.hpp"
#include "level.hpp"

namespace sea {
	class Physics {
		public:
			bool moveHorizontal(sea::DynamicEntity& entity, sea::Level& level);
			void applyGravity(sea::DynamicEntity& entity);
			bool moveVertical(sea::DynamicEntity& entity, sea::Level& level);
	};
}
