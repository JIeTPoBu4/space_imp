#include "GameOverState.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

GameOverState::GameOverState(Game* _game, unsigned _score)
: score(_score), 
GameState(_game),
title(getText(60, 75.f, "YOUR SCORE:" + std::to_string(score))),
nameField(getText(45, 250.f)),
enterNameText(getText(25, 210.f, "ENTER YOUR NAME:", sf::Text::Style::Regular)),
confirmButton(getText(35, 350.f, "confirm")),
cancelButton(getText(35, 415.f, "cancel"))
{
}


GameOverState::~GameOverState()
{
}

void GameOverState::render()
{
	window->clear();
	window->draw(title);
	window->draw(nameField);
	window->draw(enterNameText);
	window->draw(confirmButton);
	window->draw(cancelButton);
	window->display();
}


void GameOverState::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::EventType::Closed)
		{
			window->close();
		}
		if(event.type == sf::Event::EventType::TextEntered && event.text.unicode < 128)
		{
			if (event.text.unicode == '\b' && !name.empty())
			{
				name.pop_back();
			}
			else if (name.size() < 15 && event.text.unicode > 8)
			{
				name += event.text.unicode;
			}
			nameField.setString(name);
			centerText(nameField, 250.f);
		}
		if (event.type == sf::Event::EventType::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			if (confirmButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
			{
				addScore();
				game->changeState(Game::States::HIGHSCORES);
				break;
			}
			if (cancelButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
			{
				game->changeState(Game::States::MAIN_MENU);
				break;
			}
		}
	}

}

void GameOverState::addScore()
{
	/*
	std::fstream out("./HighScoreFile",std::ios::out | std::ios::in | std::ios::ate);

	if(!out) {
		std::cerr << "Error:can`t open stream!\n";
		return;
	}

	char buf[256];
	char b_name[256];

	while(!out.eof())
	{
		out.getline(buf, sizeof buf);
		bool name_f = false;
		bool score_f =false;

		for(int i = 0; buf[i] ; i++) 
		{

		}
	}

	out << "name=" << name << "&" << "score=" << score << ";\n";

	out.close();
	*/
}