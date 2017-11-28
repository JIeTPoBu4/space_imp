#define _USE_MATH_DEFINES

#include "Ship.h"
#include <math.h>
#include <iostream>

Ship::Ship()
: lives(numberOfLives), timeSinceRespawn(0.f), score(0)
{
	shape.setPointCount(3);
	shape.setPoint(0, sf::Vector2f(0, 0));
	shape.setPoint(1, sf::Vector2f(-5.f, 20.f));
	shape.setPoint(2, sf::Vector2f(5.f, 20.f));
	shape.setOrigin(0, -20 * 2/3);
	shape.setPosition(400, 290);
	shape.setRotation(90);
	shape.setFillColor(sf::Color::Black);
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(1);
	ashape = &shape;
	speed.x = 0;
	speed.y = 0;
}

Ship::~Ship()
{
}

void Ship::update(sf::Time dt)
{
	if (isRespawning())
	{
		shape.setOutlineThickness(0.2f);
	}
	else
	{
		shape.setOutlineThickness(1.f);
	}
	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		acceleration = 130.f * dt.asSeconds();
		speed.x -= sin(direction) * acceleration;
		speed.y += cos(direction) * acceleration;
	}
	else
	{
		acceleration = 0;
		speed.x *= 59.f * dt.asSeconds();
		speed.y *= 59.f * dt.asSeconds();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		shape.rotate(-200.f * dt.asSeconds());
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		shape.rotate(200.f * dt.asSeconds());
	}
	*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		speed.x = 200;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		speed.x = -200;
	}
	else {
		speed.x = 0;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		speed.y = -200;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		speed.y = 200;
	}
	else {
		speed.y = 0;
	}

	sf::Vector2f pos = shape.getPosition();
	direction = static_cast<float>(shape.getRotation() * M_PI / 180 - M_PI);
	shape.move(speed * dt.asSeconds());
	if (pos.x < 0)
	{
		shape.setPosition(0, pos.y);
	}
	else if (pos.x > 800)
	{
		shape.setPosition(800, pos.y);
	}
	else if (pos.y < 0)
	{
		reset();
		decrementLives();

		if(lives <= 0)
			return;
	}
	else if (pos.y > 600)
	{
		reset();
		decrementLives();

		if(lives <= 0)
			return;
	}
	timeSinceRespawn += dt.asSeconds();
}

void Ship::reset()
{
	shape.setPosition(400, 290);
	shape.setRotation(90);
	speed.x = 0;
	speed.y = 0;
	timeSinceRespawn = 0.f;
}

bool Ship::isRespawning()
{
	if (timeSinceRespawn < respawnTime) return true;
	else return false;
}