#include <iostream>

#include "Texture.h"

Texture::Texture(std::string filename, Platform* platform, bool scaleByScreenSize, Vec2 dimensions)
{	
	this->dimensions = dimensions;
	load(filename, platform, scaleByScreenSize);
}
Texture::Texture(SDL_Surface* surface, Platform* platform, bool scaleByScreenSize, Vec2 dimensions)
{
	this->dimensions = dimensions;
	load(surface, platform, scaleByScreenSize);
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
}

bool Texture::load(std::string filename, Platform* platform, bool scaleByScreenSize)
{
	SDL_Surface *image = IMG_Load(filename.c_str());
	if (!image)
	{
		// We'll do a quick check here because it's easy to get filenames or directories wrong
		std::cout << "Can't find image named " << filename << " " << IMG_GetError() << std::endl;
		return false;
	}

	currentRenderer = platform->getRenderer();
	
	if (!scaleByScreenSize)
	{
		createTexture(*image);
	}
	else
	{
		createTexture(*image, platform);
	}

	SDL_FreeSurface(image);
	return true;
}

bool Texture::load(SDL_Surface* surface, Platform* platform, bool scaleByScreenSize)
{
	currentRenderer = platform->getRenderer();
	
	if (!scaleByScreenSize)
	{
		createTexture(*surface);
	}
	else
	{
		createTexture(*surface, platform);
	}

	SDL_FreeSurface(surface);
	return true;
}

bool Texture::createTexture(SDL_Surface& surface)
{
	texture = SDL_CreateTextureFromSurface(currentRenderer, &surface);

	// This is done because a float* and int* conflict.
	if (dimensions.x == 0.0f)
	{
		int tempDimensionsX;
		int tempDimensionsY;
		SDL_QueryTexture(texture, NULL, NULL, &tempDimensionsX, &tempDimensionsY);

		dimensions.x = (float)tempDimensionsX;
		dimensions.y = (float)tempDimensionsY;
	}

	return (texture ? true : false);
}

bool Texture::createTexture(SDL_Surface& surface, Platform* platform)
{
	texture = SDL_CreateTextureFromSurface(currentRenderer, &surface);

	if (dimensions.x == 0.0f)
	{
		// This is done because a float* and int* conflict.
		int tempDimensionsX;
		int tempDimensionsY;
		SDL_QueryTexture(texture, NULL, NULL, &tempDimensionsX, &tempDimensionsY);

		dimensions = Vec2((float)tempDimensionsX, (float)tempDimensionsY);
	}
	
	dimensions = Utility::scaleTo(dimensions, platform->getWindowSize());

	return (texture ? true : false);
}

void Texture::draw(Vec2 pos)
{
	SDL_Rect destRect;

	destRect.x = (int)pos.x;
	destRect.y = (int)pos.y;

	// Query the texture to get its original width and height
	destRect.w = (int)dimensions.x;
	destRect.h = (int)dimensions.y;

	// Here we are telling the renderer to copy the texture to our screen,
	// at the position of the rectangle we specify
	SDL_RenderCopy(currentRenderer, texture, NULL, &destRect);
}

void Texture::draw(Vec2 pos, bool facingRight)
{
	//Function assumes that the texture by default is facing right.
	SDL_RendererFlip flip = facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;


	SDL_Rect destRect;

	destRect.x = (int)pos.x;
	destRect.y = (int)pos.y;

	// Query the texture to get its original width and height
	destRect.w = (int)dimensions.x;
	destRect.h = (int)dimensions.y;

	// Here we are telling the renderer to copy the texture to our screen,
	// at the position of the rectangle we specify
	SDL_RenderCopyEx(currentRenderer, texture, NULL, &destRect, 0.00, NULL, flip);
}


void Texture::draw(Vec2 pos, float rotation)
{
	SDL_Rect destRect;

	destRect.x = (int)pos.x;
	destRect.y = (int)pos.y;

	// Query the texture to get its original width and height
	destRect.w = (int)dimensions.x;
	destRect.h = (int)dimensions.y;

	// Here we are telling the renderer to copy the texture to our screen,
	// at the position and rotation we specify
	SDL_RenderCopyEx(currentRenderer, texture, NULL, &destRect, rotation, NULL, SDL_FLIP_NONE);
}

void Texture::draw(Vec2 pos, float rotation, Vec2 pivot)
{
	SDL_Rect destRect;

	destRect.x = (int)pos.x;
	destRect.y = (int)pos.y;

	// Query the texture to get its original width and height
	destRect.w = (int)dimensions.x;
	destRect.h = (int)dimensions.y;
	
	SDL_Point pivotPoint;
	pivotPoint.x = (int)pivot.x;
	pivotPoint.y = (int)pivot.y;

	// Here we are telling the renderer to copy the texture to our screen,
	// at the position and rotation we specify
	SDL_RenderCopyEx(currentRenderer, texture, NULL, &destRect, rotation, &pivotPoint, SDL_FLIP_NONE);
}

Vec2 Texture::getDimensions()
{
	return dimensions;
}

void Texture::setDimensions(Vec2 newDimensions)
{
	dimensions = newDimensions;
}

SDL_Renderer* Texture::getRenderer()
{
	return currentRenderer;
}

void Texture::setColourTint(Colour c)
{
	//Set the texture colour tint or log an error.
	if (SDL_SetTextureColorMod(texture, c.r, c.g, c.b) != 0) 
	{
		Utility::log(Utility::W, "SDL_SetTextureColorMod failed in setColourTint");
	}
}