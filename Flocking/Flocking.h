#pragma once

#include <vector>

#include "Boid.h"
#include "Texture.h"

class FlockingSystem
{
public:
	FlockingSystem(Texture* texture, Vec2 boundries);

	~FlockingSystem();

	void update(float dt);

	void render();

private:

	void applyRules(float dt);

	void initBoids();

	Vec2 cohesion(Boid* boid);

	Vec2 seperation(Boid* boid);

	Vec2 alignment(Boid* boid);

	Vec2 keepInBounds(Boid* boid);

	std::vector<Boid*> boids;

	Texture* texture;

	Vec2 boundries;
};