#include "GameState.h"

GameState::GameState(StateManager* manager, Platform* platform)
	: State(manager,platform)
{
	stateName = "Game State";

	Texture* texture = new Texture("boid.png", platform, false, Vec2(4,4));

	flocking = new FlockingSystem(texture, platform->getWindowSize());
}

GameState::~GameState()
{
	delete flocking;
}

bool GameState::eventHandler()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			return true;
			break;

		case SDL_KEYDOWN:

			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				return true;
				break;
			}
			break;
		}
	}
	return false;
}

void GameState::update(float dt)
{
	flocking->update(dt);
}

void GameState::render()
{
	flocking->render();
}