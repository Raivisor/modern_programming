#pragma once

#include "game_object.hpp"

namespace sea {
	class Physics {
		public:
			void moveObjectHorizontal(sea::GameObject& obj);
			void moveObjectVertical(sea::GameObject& obj);
	};
}
