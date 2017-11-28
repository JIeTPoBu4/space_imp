#ifndef _GAMEPLAY_STATE_H
#define _GAMEPLAY_STATE_H

#include <memory>
#include "GameState.h"
#include "Ship.h"
#include "Hud.h"
#include "Bullet.h"
#include "Asteroid.h"

class GameplayState : public GameState
{
public:
	GameplayState(Game* _game);
	virtual ~GameplayState();

	virtual void update(sf::Time dt) override;
	virtual void render() override;
	virtual void handleEvents() override;

private:
	bool gameRunning;
	int currentWave;
	float timeSinceLastShot;

	Ship ship;
	Hud hud;
	std::vector<std::shared_ptr<Asteroid>> asteroids;
	std::vector<std::shared_ptr<Bullet>> bullets;

	void handleCollisions();
	void createNewWave();
};

#endif

