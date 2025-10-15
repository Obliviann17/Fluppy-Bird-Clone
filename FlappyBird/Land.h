#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "Game.h"

class Land
{
public:
	Land(GameDataRef data);

	void MoveLand(float dt);
	void DrawLand();

	const std::vector<sf::Sprite>& GetSprites() const;

private:
	GameDataRef data;
	
	std::vector<sf::Sprite> landSprites;
};

