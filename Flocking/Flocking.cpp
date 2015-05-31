#include "Flocking.h"
#include "Utility.h"

FlockingSystem::FlockingSystem(Texture* texture)
{
	this->texture = texture;
	initBoids();
}

FlockingSystem::~FlockingSystem()
{
	for (auto boid : boids)
	{
		delete boid;
	}
	boids.clear();

	delete texture;
}

void FlockingSystem::update(float dt)
{
	applyRules(dt);

	/*
	for (auto boid : boids)
	{
		boid->update(dt);
	}
	*/
}

void FlockingSystem::render()
{
	for (auto boid : boids)
	{
		boid->render();
	}
}

void FlockingSystem::initBoids()
{
	for (int i = 0; i < 15; i++)
	{
		Vec2 pos(Utility::randomFloat(0.0f, 640.0f), Utility::randomFloat(0.0f, 480.0f));
		
		Boid* boid = new Boid(pos, texture, i);
		boids.push_back(boid);
	}
}

void FlockingSystem::applyRules(float dt)
{
	for (auto boid : boids)
	{
		Vec2 v1 = cohesion(boid);
		Vec2 v2 = seperation(boid);
		Vec2 v3 = alignment(boid);
		//Vec2 v3 = 0;

		boid->setVelocity(boid->getVelocity() + v1 + v2 + v3);
		
		boid->update(dt);
	}
}

Vec2 FlockingSystem::cohesion(Boid* boid)
{
	Vec2 result = 0;

	for (auto curBoid : boids)
	{
		if (curBoid->getID() != boid->getID())
		{
			result += curBoid->getPos();
		}
	}

	result /= ((float)boids.size() - 1.0f);

	return (result - boid->getPos()) / 100;
}

Vec2 FlockingSystem::seperation(Boid* boid)
{
	Vec2 result = 0;

	for (auto curBoid : boids)
	{
		if (curBoid->getID() != boid->getID())
		{
			/*
			float length = (curBoid->getPos() - boid->getPos()).getLength();
			
			if (length < 10)
			{
				result -= (curBoid->getPos() - boid->getPos());
			}
			*/
			/*if the Boid is closer than 10 pixels to another Boid on the x axis (using absolute values)*/
			if (std::abs(boid->getPos().x - curBoid->getPos().x) < 10)
			{
				result.x = result.x - (curBoid->getPos().x - boid->getPos().x);
			}

			/*if the Boid is closer than 10 pixels to another Boid on the y axis (using absolute values)*/
			if (std::abs(boid->getPos().y - curBoid->getPos().y) < 10)
			{
				result.y = result.y - (curBoid->getPos().y - boid->getPos().y);
			}
		}
	}

	return result;
}

Vec2 FlockingSystem::alignment(Boid* boid)
{
	Vec2 result = 0;

	for (auto curBoid : boids)
	{
		if (curBoid->getID() != boid->getID())
		{
			result = result + curBoid->getVelocity();
		}
	}

	result = result / (float)(boids.size() - 1);

	result = (result - boid->getVelocity()) / 8;
	return result;
	//return (result - boid->getVelocity()) / 8;
}