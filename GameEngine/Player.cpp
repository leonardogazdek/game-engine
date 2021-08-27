#include "Player.h"

#define JUMP_MAX_VELOCITY 10.0f
#define JUMP_DECCEL 0.05f

#define GRAVITY 3.0f




Player::Player(SDL_Renderer* renderer) {
	this->renderer = renderer;
	playerX = 10.0f;
	playerY = 200.0f;
	deltaX = 0.0f;
	deltaY = 0.0f;
	jumpDelta = 0.0f;
	movementKeysPressed = 0;

	playerRect.x = (int)playerX;
	playerRect.y = (int)playerY;
	playerRect.w = 100;
	playerRect.h = 200;

	canJump = false;

	imageTexture = IMG_Load("character.png");

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
					movementKeysPressed++;
					break;
				}
				case SDLK_RIGHT: {
					deltaX = 3.0f;
					movementKeysPressed++;
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

	jumpDelta = std::max(jumpDelta - JUMP_DECCEL, 0.0f);

	SDL_Rect tempRect{ (int)tempX, (int)tempY, 100, 200 };
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
		playerRect.x = (int)playerX;
	}
	if (tempY < 520.0f && (!collisionFound || (collisionFound && (intersectRect.w < intersectRect.h)))) {
		playerY = tempY;
		playerRect.y = (int)playerY;
		canJump = false;
	}
	else {
		canJump = true;
	}
	

}

void Player::HandleDrawing() {
	SDL_RenderCopy(renderer, playerTexture, NULL, &playerRect);

}