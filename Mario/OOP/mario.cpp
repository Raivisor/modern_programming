#include "mario.hpp"

#include "brick.hpp"
#include "coin.hpp"
#include "config.hpp"
#include "collision_handler.hpp"
#include "enemy.hpp"
#include "input_manager.hpp"
#include "level.hpp"
#include "physics.hpp"

using namespace sea;

Mario::Mario(float x, float y, float width, float height,
		EntityType type, float vx, float vy)
	: DynamicEntity(x, y, width, height, type, vx, vy) {}

void Mario::die() {
	isAlive = false;
}

void Mario::update(Level& level, Physics& physics) {
	if(!isAlive) return;

	if (getY() > Config::MAP_HEIGHT) die();

	auto& input = InputManager::getInstance();
	vx = Config::ABS_SPEED * input.getDirection();

	Mario copy = *this;
	copy.setY(copy.getY() + 1);

	if(input.isJump() && copy.hasGround(level)) {
		vy = -Config::JUMP_FORCE;
	}

	physics.moveHorizontal(*this, level);
	physics.applyGravity(*this);
	physics.moveVertical(*this, level);
}

void Mario::onCollision(Entity& other) {
    switch (other.getType()) {
        case EntityType::ENEMY: {
            if (vy > 0 && getY() + getHeight() < other.getY() + other.getHeight() / 2) {
                if (auto* enemy = dynamic_cast<Enemy*>(&other)) {
                    enemy->die();
                    vy = -Config::JUMP_ON_ENEMY_FORCE; 
                }
            } else {
                die();
            }
            break;
        }
        case EntityType::COIN: {
            if (auto* coin = dynamic_cast<Coin*>(&other)) {
                coin->die();
            }
            break;
        }
        default:
            break;
    }
}

char Mario::getSymbol() const {
	return Config::PLAYER_TYPE;
}
