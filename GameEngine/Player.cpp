#include "Player.h"

#define JUMP_MAX_VELOCITY 10.0f
#define JUMP_DECCEL 0.15f

#define GRAVITY 3.0f

Player::Player(SDL_Renderer* renderer, int x, int y) {
	this->renderer = renderer;
	playerX = static_cast<float>(x);
	playerY = static_cast<float>(y);
	deltaX = 0.0f;
	deltaY = 0.0f;
	jumpDelta = 0.0f;

	playerRect.x = static_cast<int>(playerX);
	playerRect.y = static_cast<int>(playerY);
	playerRect.w = 100;
	playerRect.h = 200;

	canJump = false;

	imageTexture = IMG_Load("textures/character.png");

	playerTexture = SDL_CreateTextureFromSurface(renderer, imageTexture);
}

Player::~Player() {
	SDL_DestroyTexture(playerTexture);
}

void Player::HandleEvents(SDL_Event* event) {
	switch (event->type) {
		case SDL_KEYDOWN: {
			switch (event->key.keysym.sym) {
				case SDLK_UP: {
					if (canJump) {
						jumpDelta = JUMP_MAX_VELOCITY;
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

void Player::HandlePhysics(float dT, Obstacles* obstacles) {
	float tempX = std::max(playerX + deltaX * dT, 0.0f);
	float tempY = std::max(playerY + (GRAVITY - jumpDelta) * dT, 0.0f);

	jumpDelta = std::max(jumpDelta - JUMP_DECCEL * dT, 0.0f);

	SDL_Rect tempRect{ static_cast<int>(tempX), static_cast<int>(tempY), 100, 200 };
	bool collisionFound = false;
	SDL_Rect intersectRect;
	for (Obstacle &o : *(obstacles->GetObstacles())) {
		if (SDL_IntersectRect(&tempRect, o.GetRect(), &intersectRect)) {
			collisionFound = true;
			std::cout << intersectRect.w <<"," << intersectRect.h << std::endl;
			break;
		}
	}

	if (!collisionFound || (collisionFound && (intersectRect.w > intersectRect.h))) {
		playerX = tempX;
		playerRect.x = static_cast<int>(playerX);
	}
	if (tempY < (720 - playerRect.h) && (!collisionFound || (collisionFound && (intersectRect.w < intersectRect.h)))) {
		playerY = tempY;
		playerRect.y = static_cast<int>(playerY);
		canJump = false;
	}
	else {
		canJump = true;
	}
	

}

void Player::HandleDrawing() {
	SDL_RenderCopy(renderer, playerTexture, NULL, &playerRect);

}