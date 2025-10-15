#include "SplashState.h"
#include "MainMenuState.h"
#include "DEFINITIONS.h"

#include <iostream>

SplashState::SplashState(GameDataRef data)
	: data(data)
{ }

void SplashState::Init()
{
	data->assets.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
	background = std::make_unique<sf::Sprite>(data->assets.GetTexture("Splash State Background"));
	background->setPosition(sf::Vector2f(SCREEN_WIDTH / 3.0f - 70, SCREEN_HEIGHT / 2.0f - 60));
}

void SplashState::HandleInput()
{
		while (const std::optional event = data->window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				data->window.close();
		}
}

void SplashState::Update(float dt)
{
	if (clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
	{
		data->machine.AddState(StateRef(new MainMenuState(data)), true);
	}
}

void SplashState::Draw(float dt)
{
	data->window.clear();

	data->window.draw(*background);
	data->window.display();
}

void SplashState::Pause()
{ }

void SplashState::Resume()
{ }

