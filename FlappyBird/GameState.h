#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "State.h"
#include "Game.h"
#include "Pipe.h"
#include "Land.h"
#include "Bird.h"
#include "Collision.h"
#include "Flash.h"
#include "HUD.h"

class GameState : public State
{
public:
	GameState(GameDataRef data);

	void Init() override;
	void HandleInput() override;
	void Update(float dt) override;
	void Draw(float dt) override;

	virtual void Pause() override;
	virtual void Resume() override;

private:
	GameDataRef data;

	std::unique_ptr<sf::Sprite> background;
	std::unique_ptr<Pipe> pipe;
	std::unique_ptr<Land> land;
	std::unique_ptr<Bird> bird;
	std::unique_ptr<Flash> flash;
	std::unique_ptr<HUD> hud;

	Collision collision;

	sf::Clock clock;

	int gameState;

	int score;

	sf::SoundBuffer hitSoundBuffer;
	sf::SoundBuffer pointSoundBuffer;
	sf::SoundBuffer wingSoundBuffer;

	std::unique_ptr<sf::Sound> hitSound;
	std::unique_ptr<sf::Sound> pointSound;
	std::unique_ptr<sf::Sound> wingSound;
};

