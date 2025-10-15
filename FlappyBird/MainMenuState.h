#pragma once

#include <SFML/Graphics.hpp>

#include "State.h"
#include "Game.h"

class MainMenuState : public State
{
public:
	MainMenuState(GameDataRef data);

	void Init() override;
	void HandleInput() override;
	void Update(float dt) override;
	void Draw(float dt) override;

	virtual void Pause() override;
	virtual void Resume() override;

private:
	GameDataRef data;

	std::unique_ptr<sf::Sprite> background;
	std::unique_ptr<sf::Sprite> title;
	std::unique_ptr<sf::Sprite> playButton;
};

