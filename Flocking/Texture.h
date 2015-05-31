#include "dependencies/SDL.h"
#include "dependencies//SDL_image.h"
#include <string>

#include "Vec2.h"
#include "Utility.h"
#include "Platform.h"

#pragma once

//Self Reference: This code was used in a previous assignment with major changes (Due to scaling)

/**
@class Texture
@brief Encapsulates an SDL_Texture

Contains the ability to draw, load, etc.. Textures.
*/
class Texture
{
public:

	/**
	@brief Create a Texture.
	
	@param filename			 Path to image.
	@param [in,out] platform platform.
	@param scaleByScreenSize true to scale by screen size.
	@param dimensions		 The dimensions to draw at, if 0 the images dimensions are used.
	 */
	Texture(std::string filename, Platform* platform, bool scaleByScreenSize, Vec2 dimensions);

	/**
	@brief Create a Texture.
	
	@param [in,out] surface  - A surface to convert into a texture (This is freed internally)
	@param [in,out] platform platform.
	@param scaleByScreenSize true to scale by screen size.
	@param dimensions		 The dimensions to draw at, if 0 the images dimensions are used.
	 */
	Texture(SDL_Surface* surface, Platform* platform, bool scaleByScreenSize, Vec2 dimensions);

	~Texture();

	/**
	@brief Gets the Dimensions of the stored texture
	@return Vec2 - Dimensions of Sprite
	*/
	Vec2 getDimensions();

	/**
	 @brief Sets the dimensions of the stored texture.
	
	 @param newDimensions The new dimensions.
	 */
	void setDimensions(Vec2 newDimensions);

	/**
	@brief Draw the Sprite
	@param Vec2 - Position to draw at
	*/
	void draw(Vec2 pos);

	/**
	@brief Draw the Sprite
	@param Vec2 - Position to draw at
	@param bool - Whether the sprite shouldn't be flipped (True doesn't flip, false does)
	*/
	void draw(Vec2 pos, bool facingRight);

	/**
	@brief Draw the Sprite
	@param Vec2 - Position to draw at
	@param float - Rotation of the sprite in degrees (Around middle of sprite)
	*/
	void draw(Vec2 pos, float rotation);

	/**
	@brief Draw the Sprite
	@param Vec2 - Position to draw at
	@param float - Rotation of the sprite in degrees around pivot point
	@param Vec2 - Pivot point to rotate around
	*/
	void draw(Vec2 pos, float rotation, Vec2 pivot);

	/**
	@brief Load Image.
	
	@param parameter1		 - Path to image.
	@param [in,out] platform - platform.
	@param scaleByScreenSize true to scale by screen size.
	
	@return true if it succeeds, false if it fails.
	 */
	bool load(std::string, Platform*platform, bool scaleByScreenSize);

	/**
	@brief Load Image.
	
	@param [in,out] parameter1 - A surface to convert into a texture (This is freed internally)
	@param [in,out] platform   platform.
	@param scaleByScreenSize   true to scale by screen size.
	
	@return true if it succeeds, false if it fails.
	 */
	bool load(SDL_Surface*, Platform* platform, bool scaleByScreenSize);

	/**
	@brief Apply a tint to the texture (Warning this applied to all textures sharing if this is a pointer)
	@param Colour - Colour tint to apply
	*/
	void setColourTint(Colour colour);

	/**
	@brief Get the renderer used for this sprite
	@return SDL_Renderer* - The renderer used in the creation of this Texture
	*/
	SDL_Renderer* getRenderer();
private:
	/// Stored Dimensions of the Texture
	Vec2 dimensions;

	/// Texture data
	SDL_Texture* texture;

	/// Renderer
	SDL_Renderer* currentRenderer;

	/**
	@brief Create a texture from a passed in surface.

	@param [in,out] surface  - Image Surface.

	@return bool - Whether it was successful.
	*/
	bool createTexture(SDL_Surface& surface);

	/**
	@brief Create a texture from a passed in surface.
	
	@param [in,out] surface  - Image Surface.
	@param [in,out] platform If non-null, the platform.
	
	@return bool - Whether it was successful.
	 */
	bool createTexture(SDL_Surface& surface, Platform* platform);
};

