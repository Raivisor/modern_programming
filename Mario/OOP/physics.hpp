#pragma once

#include "dynamic_entity.hpp"
#include "level.hpp"

namespace sea {
	class Physics {
		public:
			bool moveHorizontal(sea::DynamicEntity& entity, sea::Level& level);
			bool moveVertical(sea::DynamicEntity& entity, sea::Level& level);
	};
}
