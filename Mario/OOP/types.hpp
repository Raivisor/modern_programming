#pragma once

namespace types {
	struct Object {
		float x, y;
		float width, height;
		float verticalSpeed;
		float horizontalSpeed;
		float IsFly;
		char type;
	};

	struct Brick {
		float x,y;
		float width, height;
		char type;
	};

	struct Enemy {
		float x, y;
		float width, height;
		char type;
		float speed;
	};
}
