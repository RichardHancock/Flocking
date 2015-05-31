#pragma once

#include "Vec2.h"
#include "Texture.h"

class Boid
{
public:
	Boid(Vec2 pos, Texture* texture, unsigned int id);

	void update(float dt);

	void render();

	Vec2 getVelocity() { return velocity; }

	void setVelocity(Vec2 velocity) { this->velocity = velocity; }

	Vec2 getPos() { return pos; }

	void setPos(Vec2 pos) { this->pos = pos; }

	unsigned int getID() { return id; }
private:

	Vec2 pos;

	Vec2 velocity;

	Texture* texture;

	unsigned int id;
};