#pragma once

#include <SFML/Graphics.hpp>

class Collision
{
public:
	Collision();

	bool CheckSpriteCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
	bool CheckSpriteCollision(const sf::Sprite& sprite1, float scale1, const sf::Sprite& sprite2, float scale2);
};

