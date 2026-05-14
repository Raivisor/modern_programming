#pragma once

#include "collision.hpp"
#include "constants.hpp"
#include "gameContext.hpp"
#include "objects.hpp"
#include "types.hpp"

namespace physics {
	void ApplyGravity(types::Object* obj);

	void MoveObjectVertical(GameContext::Context* ctx, types::Object* obj);

	void MoveObjectHorizontal(GameContext::Context* ctx, types::Object* obj);
}
