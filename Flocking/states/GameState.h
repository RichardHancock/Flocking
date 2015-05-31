#include <string>
#include "../Platform.h"
#include "State.h"
#include "../Flocking.h"

#pragma once

class GameState : public State
{
public:
	GameState(StateManager* manager, Platform* platform);

	~GameState();
	/**
	@brief Handles any events such as keyboard/mouse input
	*/
	virtual bool eventHandler();

	/**
	@brief Update any internal values
	@param float - delta time
	*/
	virtual void update(float dt);

	/**
	@brief Render any sprites relevant to the state
	*/
	virtual void render();
protected:

	FlockingSystem* flocking;
};