#include "MainMenuState.h"
#include "GameState.h"
#include "DEFINITIONS.h"

#include <iostream>

MainMenuState::MainMenuState(GameDataRef data)
	:data(data)
{ }

void MainMenuState::Init()
{
	data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
	data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);
	data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);

	background = std::make_unique<sf::Sprite>(data->assets.GetTexture("Main Menu Background"));
	title = std::make_unique<sf::Sprite>(data->assets.GetTexture("Game Title"));
	playButton = std::make_unique<sf::Sprite>(data->assets.GetTexture("Play Button"));

	title->setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f - 310, SCREEN_HEIGHT / 6.0f - 100));
	playButton->setPosition(sf::Vector2f(SCREEN_WIDTH / 3.0f - 20, SCREEN_HEIGHT / 2.0f - 40));
}

void MainMenuState::HandleInput()
{
	while (const std::optional event = data->window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			data->window.close();

		if (data->input.IsSpriteClicked(*playButton, sf::Mouse::Button::Left, data->window))
			data->machine.AddState(StateRef(new GameState(data)), true);
	}
}

void MainMenuState::Update(float dt)
{
}

void MainMenuState::Draw(float dt)
{
	data->window.clear();

	data->window.draw(*background);
	data->window.draw(*title);
	data->window.draw(*playButton);

	data->window.display();
}

void MainMenuState::Pause()
{ }

void MainMenuState::Resume()
{ }

