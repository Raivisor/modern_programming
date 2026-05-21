#include "mario.hpp"

#include "input_manager.hpp"
#include "config.hpp"
#include "collision_handler.hpp"
#include "brick.hpp"
#include "enemy.hpp"
#include "coin.hpp"

using namespace sea;

Mario::Mario(float x, float y, float width, float height,
		EntityType type, float vx, float vy)
	: DynamicEntity(x, y, width, height, type, vx, vy) {}

void Mario::die() {
	isAlive = false;
}

void Mario::update(Level& level, Physics& physics) {
	auto& input = InputManager::getInstance();
	vx = Config::ABS_SPEED * input.getDirection();

	if(input.isJump() && hasGround(level)) {
		vy = -Config::JUMP_FORCE;
	}

	physics.applyGravity(*this);
	physics.moveHorizontal(*this, level);
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
                // Добавить очки (лучше через Game, можно через статический счётчик или событие)
                // Предположим, есть глобальный счётчик или метод Game::addScore
                // Game::getInstance().addScore(Config::COIN_SCORE);
            }
            break;
        }
        default:
            break;
    }
}

char Mario::getSymbol() {
	return Config::PLAYER_TYPE;
}
