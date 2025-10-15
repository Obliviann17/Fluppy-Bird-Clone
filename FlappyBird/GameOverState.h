#pragma once

#include <SFML/Graphics.hpp>

#include "State.h"
#include "Game.h"

class GameOverState : public State
{
public:
	GameOverState(GameDataRef data, int score);

	void Init() override;
	void HandleInput() override;
	void Update(float dt) override;
	void Draw(float dt) override;

	virtual void Pause() override;
	virtual void Resume() override;

private:
	GameDataRef data;

	std::unique_ptr<sf::Sprite> background;

	std::unique_ptr<sf::Sprite> gameOverTitle;
	std::unique_ptr<sf::Sprite> gameOverContainer;
	std::unique_ptr<sf::Sprite> retryButton;
	std::unique_ptr<sf::Sprite> medal;

	std::unique_ptr<sf::Text> scoreText;
	std::unique_ptr<sf::Text> highScoreText;

	int score;
	int highScore;
};

