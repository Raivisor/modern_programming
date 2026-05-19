#pragma once

namespace sea {
	class InputManager{
		private:
			int direction;
			bool jump;
			bool exit;

			InputManager() : direction(0), jump(false), exit(false) {};
			~InputManager() = default;

			void normalize();
		public:
			InputManager(const InputManager&) = delete;
			InputManager& operator=(const InputManager&) = delete;

			static InputManager& getInstance() {
				static InputManager instance;
				return instance;
			}

			void readKey();

			int getDirection() const { return direction; }
			bool isJump() const { return jump; }
			bool isExit() const {return exit; }
	};
}
