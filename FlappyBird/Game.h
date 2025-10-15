#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

struct GameData
{
	StateMachine machine;
	sf::RenderWindow window;
	AssetManager assets;
	InputManager input;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game
{
public:
	Game(int width, int height, const std::string& title);
	~Game();

private:
	const float dt = 1.0f / 60.0f;
	sf::Clock clock;

	GameDataRef data = std::make_shared<GameData>();

	void Run();
};

