#pragma once

#include "dynamic_entity.hpp"
#include "level.hpp"

namespace sea {
	class DynamicEntity;
	class Level;
}

namespace sea {
	class Physics {
		public:
			bool moveHorizontal(DynamicEntity& entity, Level& level);
			void applyGravity(DynamicEntity& entity);
			bool moveVertical(DynamicEntity& entity, Level& level);
	};
}
