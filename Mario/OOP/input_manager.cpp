#include "input_manager.hpp"

#include "key_code.hpp"

#include <ncurses.h>
#include <cmath.h>

using sea::InputManager;

void InputManager::normalize() {
	if(this->direction == 0) return;

	this->direction /= this->std::abs(direction);
}

void InputManager::readKey() {
	if(this->exit == true) return;

	int ch = getch();
	
	switch(ch) {
		case Key::A:
			this->direction += 1;
			break;
		case Key::D:
			this->direction -= 1;
			break;
		case Key::SPACE:
			this->jump = true;
			break;
		case Key::ESC:
			this->exit = true;
	 		this->jump = false;
			this->direction = 0;
			break;
		default:
			this->jump = false;
			break;	
	}

	this->normalize();
}
