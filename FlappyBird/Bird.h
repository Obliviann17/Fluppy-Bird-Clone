#pragma once

#include <SFML/Graphics.hpp>

#include "DEFINITIONS.h"
#include "Game.h"
#include <vector>

class Bird
{
public:
	Bird(GameDataRef data);

	void Draw();

	void Animate(float dt);

	void Update(float dt);
	void Tap();

	const sf::Sprite& GetSprite() const;

private:
	GameDataRef data;

	std::unique_ptr<sf::Sprite> birdSprite;
	std::vector<sf::Texture> animationFrames;

	unsigned int animationIterator;

	sf::Clock clock;

	sf::Clock movementClock;

	int birdState;

	float rotation;
};

