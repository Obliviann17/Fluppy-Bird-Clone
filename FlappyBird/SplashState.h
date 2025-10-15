#pragma once

#include <SFML/Graphics.hpp>

#include "State.h"
#include "Game.h"

class SplashState : public State
{
public:
	SplashState(GameDataRef data);

	void Init() override;
	void HandleInput() override;
	void Update(float dt) override;
	void Draw(float dt) override;

	virtual void Pause() override;
	virtual void Resume() override;

private:
	GameDataRef data;

	sf::Clock clock;
	sf::Texture backgroundTexture;
	std::unique_ptr<sf::Sprite> background;
};

