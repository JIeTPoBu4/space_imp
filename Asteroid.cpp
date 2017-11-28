#include "Asteroid.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cstdlib>

std::map<Asteroid::Size, int> Asteroid::radiuses = { { BIG, 55 }, { MEDIUM, 35 }, { SMALL, 15 } };

Asteroid::Asteroid()
:size(BIG), shape(new sf::ConvexShape()), alive(true)
{
	shape->setPosition(1800.f - static_cast<float>(rand() % 801), static_cast<float>(rand() % 601));
	shape->setFillColor(sf::Color::Black);
	shape->setOutlineColor(sf::Color::White);
	shape->setOutlineThickness(1);

	float speedx = -abs(static_cast<float>(rand() % 40 - initialVelocity));
	int sign = rand() % 2;
	if (sign == 0) sign = -1;
	float speedy = sign * (initialVelocity - abs(static_cast<float>(rand() % 40 - initialVelocity))) % 20;
	speed = sf::Vector2f(speedx, speedy);
	generateShape();
	ashape = shape;
}

Asteroid::Asteroid(Size _size, sf::Vector2f _speed, sf::Vector2f _position)
:size(_size), shape(new sf::ConvexShape()), alive(true)
{
	shape->setPosition(_position);
	shape->setFillColor(sf::Color::Black);
	shape->setOutlineColor(sf::Color::White);
	shape->setOutlineThickness(1);
	speed = _speed;
	generateShape();
	ashape = shape;
}

Asteroid::~Asteroid()
{
	delete shape;
}

void Asteroid::update(sf::Time dt)
{
	shape->move(speed.x * dt.asSeconds(), speed.y * dt.asSeconds());
	sf::FloatRect bounds = shape->getGlobalBounds();
	if (bounds.left + bounds.width < 0)
	{
		shape->move(1000.f + bounds.width, static_cast<float>(rand() % 601));
	}
	else if (bounds.left - bounds.width > 800)
	{
		if(size == SMALL || size == MEDIUM) {
			alive = false;
		}
	}	
	else if (bounds.top - 0.1 * bounds.height < 0)
	{
		alive = false;
	}

	else if (bounds.top > 600)
	{
		alive = false;
	}
}

void Asteroid::generateShape()
{
	std::vector<float> points;
	shape->setPointCount(numberOfSides);
	for (int i = 0; i < numberOfSides; i++)
	{
		points.push_back(static_cast<float>(rand() * 2 * M_PI / (RAND_MAX + 1)));
	}
	std::sort(points.begin(), points.end());
	for (int i = 0; i < numberOfSides; i++)
	{
		shape->setPoint(i, sf::Vector2f(radiuses.at(size) * sin(points.at(i)), 
			radiuses.at(size) * cos(points.at(i))));
	}
}