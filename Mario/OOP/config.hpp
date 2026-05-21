#pragma once

namespace sea {
	class Config {
		public:
			static constexpr int MAP_WIDTH = 195;
			static constexpr int MAP_HEIGHT = 50;
			static constexpr float ABS_SPEED = 1;
			static constexpr float ENEMY_SPEED = 0.3335f;
			static constexpr float COIN_SPEED = 0.5f;
			static constexpr float JUMP_FORCE = 1;
			static constexpr float GRAVITY = 0.05;
			static constexpr float COIN_JUMP_FORCE = -0.7f;
			static constexpr int MAX_LEVEL = 3;
			static constexpr int COIN_SCORE = 100;
			static constexpr int ENEMY_SCORE = 50;
			static constexpr char BLOCK_WALL = '#';
			static constexpr char BLOCK_QUESTION = '?';
			static constexpr char BLOCK_DASH = '-';
			static constexpr char BLOCK_DOOR = '+';
			static constexpr char ENEMY_TYPE = 'o';
			static constexpr char COIN_TYPE = '$';
			static constexpr char PLAYER_TYPE = '@';
	};
}
