#include <string>
#include "../Platform.h"

#pragma once
class StateManager;

//Self Reference: This code was used in a previous assignment with minor changes.
//Reference: Pete Allen's Game State Example

/**
@class State
@brief A game state that contains one screen of the game such as a Menu or the game itself
*/
class State
{
public:

	/**
	@brief Create the State.
	
	@param [in,out] manager  - Pointer to the current state manager.
	@param [in,out] platform - Platform containing OS dependent data.
	 */
	State(StateManager* manager, Platform* platform);

	virtual ~State() {}

	/**
	@brief Handles any events such as keyboard/mouse input
	*/
	virtual bool eventHandler() = 0;

	/**
	@brief Update any internal values
	@param float - delta time
	*/
	virtual void update(float dt) = 0;

	/**
	@brief Render any sprites relevant to the state
	*/
	virtual void render() = 0;

	/**
	@brief Get this states name
	@return std::string - Name
	*/
	std::string getStateName() { return stateName; }
protected:
	///Pointer to state manager
	StateManager* stateManager;

	/// Platform class containing Window/Renderer and other OS dependent data
	Platform* platform;

	///This states name
	std::string stateName;
};