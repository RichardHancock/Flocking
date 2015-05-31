#include "Boid.h"

Boid::Boid(Vec2 pos, Texture* texture, unsigned int id)
	: pos(pos), texture(texture), id(id), velocity(0.0f)
{

}

void Boid::update(float dt)
{
	pos += velocity  * dt;
}

void Boid::render()
{
	texture->draw(pos);
}

