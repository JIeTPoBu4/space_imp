#ifndef _SHIP_H
#define _SHIP_H

#include "Entity.h"

class Ship : public Entity
{
public:
	Ship();
	~Ship();

	void reset();
	void decrementLives() { lives--; }

	int getLives() const { return lives; }
	sf::Vector2f getPosition() const { return shape.getPosition(); }
	float getDirection() const { return direction; }
	unsigned int getScore() { return score; }
	bool engineOn(){ return ((speed.x != 0) || (speed.y != 0)); }
	bool isRespawning();
	void updateScore(int sc) { score += sc; }
	virtual void update(sf::Time dt) override;

private:
	sf::ConvexShape shape;
	static const int numberOfLives = 3;
	const float respawnTime = 2.f;
	float timeSinceRespawn;
	float direction;
	int lives;
	unsigned score;
};

#endif