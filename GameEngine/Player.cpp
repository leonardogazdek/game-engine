#include "Player.h"

#define JUMP_MAX_VELOCITY 6.0f
#define JUMP_DECCEL 0.05f


Player::Player() {
	int w, h;
	SDL_GetWindowSize(GameData().GetInstance()->window, &w, &h);
	playerX = 10.0f;
	playerY = h - 20.0f;
	deltaX = 0.0f;
	deltaY = 0.0f;
	jumpDelta = 0.0f;
	jumping = false;
}

void Player::HandleEvents(SDL_Event* event) {
	switch (event->type) {
		case SDL_KEYDOWN: {
			switch (event->key.keysym.sym) {
				case SDLK_UP: {
					if (jumpDelta == 0) {
						jumpDelta = JUMP_MAX_VELOCITY;
						jumping = true;
					}
					break;
				}
				case SDLK_LEFT: {
					deltaX = -3.0f;
					break;
				}
				case SDLK_RIGHT: {
					deltaX = 3.0f;
					break;
				}
				break;
			}
			break;
		}
		case SDL_KEYUP: {
			SDL_KeyCode verticalMovementKeys[] = { SDLK_DOWN, SDLK_UP };
			SDL_KeyCode horizontalMovementKeys[] = { SDLK_LEFT, SDLK_RIGHT };
			if (std::find(std::begin(verticalMovementKeys), std::end(verticalMovementKeys), event->key.keysym.sym) != std::end(verticalMovementKeys)) {
				deltaY = 0.0f;
			}
			if (std::find(std::begin(horizontalMovementKeys), std::end(horizontalMovementKeys), event->key.keysym.sym) != std::end(horizontalMovementKeys)) {
				deltaX = 0.0f;
			}
			break;
		}
	}
}

void Player::HandlePhysics(float dT) {
	if (jumping) {
		int w, h;
		SDL_GetWindowSize(GameData().GetInstance()->window, &w, &h);

		jumpDelta = jumpDelta - JUMP_DECCEL;
		if (jumpDelta < 0.0f && playerY > h - 20.0f) {
			jumpDelta = 0.0f;
			jumping = false;
		}
	}

	playerX = std::max(playerX + deltaX * dT, 0.0f);
	playerY = std::max(playerY - jumpDelta * dT, 0.0f);
}

void Player::HandleDrawing(SDL_Renderer* renderer) {
	SDL_Rect rect1{ (int)playerX, (int)playerY, 10, 10 };

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &rect1);
}