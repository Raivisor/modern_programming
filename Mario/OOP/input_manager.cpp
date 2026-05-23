#include "input_manager.hpp"

#include "key_code.hpp"

#include <ncurses.h>
#include <cmath>

using sea::InputManager;

void InputManager::normalize() {
	if(direction == 0) return;

	direction /= std::abs(direction);
}

void InputManager::readKey() {
	if(exit == true) return;

	int ch = getch();
	
	switch(ch) {
		case Key::A:
			direction -= 1;
			break;
		case Key::D:
			direction += 1;
			break;
		case Key::SPACE:
			jump = true;
			break;
		case Key::ESC:
			exit = true;
	 		jump = false;
			direction = 0;
			break;
		default:
			jump = false;
			break;	
	}

	normalize();
}
