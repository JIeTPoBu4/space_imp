#include "MainMenuState.h"
#include <iostream>

MainMenuState::MainMenuState(Game *_game)
: GameState(_game), 
title(getText(80, 100.f, "asteroids")),
playButton(getText(40, 300.f, "play game", sf::Text::Style::Regular)),
highscoreButton(getText(40, 360.f, "high scores", sf::Text::Style::Regular)),
outButton(getText(40, 420.f, "out", sf::Text::Style::Regular))
{
}


MainMenuState::~MainMenuState()
{
}

void MainMenuState::render()
{
	window->clear();
	window->draw(title);
	window->draw(playButton);
	window->draw(highscoreButton);
	window->draw(outButton);
	window->display();
}

void MainMenuState::update(sf::Time dt) {}

void MainMenuState::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::EventType::Closed)
		{
			window->close();
		}
		if (event.type == sf::Event::EventType::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			if (playButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
			{
				game->changeState(Game::States::GAMEPLAY);
				break;
			}
			else if (highscoreButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
			{
				game->changeState(Game::States::HIGHSCORES);
				break;
			}
			else if (outButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
			{
				window->close();
				break;
			}
		}
	}
}