#pragma once

#include <SFML/Graphics.hpp>

#include "DEFINITIONS.h"
#include "Game.h"

class HUD
{
public:
	HUD(GameDataRef data);

	void Draw();
	void UpdateScore(int score);

private:
	GameDataRef data;

	std::unique_ptr<sf::Text> scoreText;
};

