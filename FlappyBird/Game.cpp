#include "Game.h"
#include "SplashState.h"

#include <stdlib.h>
#include <time.h>

Game::Game(int width, int height, const std::string& title)
{
	srand(static_cast<unsigned>(time(nullptr)));

	data->window.create(sf::VideoMode(sf::Vector2u(static_cast<unsigned>(width),
		static_cast<unsigned>(height))), title, sf::Style::Close | sf::Style::Titlebar);
	data->machine.AddState(StateRef(new SplashState(this->data)));

	this->Run();
}

Game::~Game()
{ }

void Game::Run()
{
	float newTime, frameTime, interpolation;

	float currentTime = this->clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	while (this->data->window.isOpen())
	{
		this->data->machine.ProcessStateChanges();
		
		newTime = this->clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= dt)
		{
			this->data->machine.GetActiveState()->HandleInput();
			this->data->machine.GetActiveState()->Update(dt);

			accumulator -= dt;
		}

		interpolation = accumulator / dt;
		this->data->machine.GetActiveState()->Draw(interpolation);
	}
}
