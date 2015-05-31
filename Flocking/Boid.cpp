#include "Boid.h"

#include <algorithm>

Boid::Boid(Vec2 pos, Texture* texture, unsigned int id)
	: pos(pos), texture(texture), id(id), velocity(0.0f), maxSpeed(200.0f)
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

void Boid::setVelocity(Vec2 newVelocity)
{
	Vec2 temp;

	//Store the smallest number between the new velocity and the maxSpeed
	temp.x = std::min(std::abs(newVelocity.x), maxSpeed);
	//if the new velocity is positive or negative it flips the previous number to be correct 
	velocity.x = (newVelocity.x >= 0.00f ? temp.x : -temp.x);
	
	temp.y = std::min(std::abs(newVelocity.y), maxSpeed);
	velocity.y = (newVelocity.y >= 0.00f ? temp.y : -temp.y);

	//Much more elegant than a mass of if statements
}