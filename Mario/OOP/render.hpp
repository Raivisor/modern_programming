#pragma once

#include "entity.hpp"

namespace sea {
	class Render {
		private:
			char** map;
			int width;
			int height;

			bool isOnMap(int x, int y) const;
		public:
			Render(int width, int height);
			~Render();

			void clearMap();
			void putEntityOnMap(const sea::Entity& type);
			void putScoreOnMap(int score);
			void refreshMap();
	};
}
