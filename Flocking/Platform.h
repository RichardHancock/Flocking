#pragma once

#include "dependencies/SDL.h"
#include "dependencies/SDL_image.h"
#include "dependencies/SDL_mixer.h"
#include "dependencies/SDL_ttf.h"
#include "Vec2.h"

//Quick Pre-processor key 
#ifdef _WIN32
	//Windows 32/64 bit
#elif __ANDROID__
	//Android (Is also covered by __linux__ preprocessor so must be before it)
#elif EMSCRIPTEN
	//Emscripten (Web Browsers), not sure if this is correct macro
	// Cant develop for Emscripten as it lacks support for a few major SDL 2 add ons.
#elif __APPLE__
	//Mac OSX and iOS (Probably wont be used as I can't test either)
#elif __linux__
	//Linux Kernel
#endif

/** @brief Class that handles the initialization of SDL 2 (and its add ons) across all supported platforms */
class Platform
{
public:
	/** @brief Default constructor. */
	Platform();

	/** @brief Destructor, Calls SDL's cleanup features for itself and its add ons. */
	~Platform();

	/**
	@brief Initialises the SDL library and its plugins, for the current platform
	@return bool - Was successful
	*/
	bool initSDL();

	/**
	 @brief Gets the renderer.
	
	 @return null if it fails, else the renderer.
	 */
	SDL_Renderer* getRenderer() { return renderer; }

	/**
	 @brief Gets the window.
	
	 @return null if it fails, else the window.
	 */
	SDL_Window* getWindow() { return window; }

	/**
	 @brief Gets window size.
	
	 @return The window size.
	 */
	Vec2 getWindowSize() { return windowSize; }

	
private:
	/** @brief The renderer. */
	SDL_Renderer* renderer;

	/** @brief The window. */
	SDL_Window* window;

	/** @brief Size of the window. */
	Vec2 windowSize;

	//The resolution everything is scaled from
	const Vec2 scale;
};