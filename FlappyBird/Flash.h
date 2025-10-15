#pragma once

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "DEFINITIONS.h"

class Flash
{
public:
	Flash(GameDataRef data);

	void Show(float dt);
	void Draw();

private:
	GameDataRef data;

	sf::RectangleShape shape;
	bool flashOn;
};
