#pragma once

#include "level.hpp"
#include "render.hpp"
#include "physics.hpp"
#include "mario.hpp"
#include "input_manager.hpp"

namespace sea {
	class Game {
		public:
			Game();
			~Game() = default;
			void run();
		private:
			Level currentLevel;
			Render render;
			Physics physics;
			Mario mario;
			int score;
			bool running;
			int currentLevelNumber;

			void handleInput();
			void update();
			void renderFrame();
			void shiftWorld(float dx);
			void checkCollisions();
			void removeDeadObjects();
			void loadLevel(int levelNumber);
	};
}
