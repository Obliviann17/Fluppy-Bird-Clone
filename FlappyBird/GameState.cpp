#include "GameState.h"
#include "DEFINITIONS.h"
#include "GameOverState.h"

#include <iostream>

GameState::GameState(GameDataRef data)
	:data(data), score(0), gameState(GameStates::eReady)
{ }

void GameState::Init()
{
	if (!hitSoundBuffer.loadFromFile(HIT_SOUND_FILEPATH))
	{
		std::cout << "Error loading Hit sound!" << std::endl;
	}
	if (!pointSoundBuffer.loadFromFile(POINT_SOUND_FILEPATH))
	{
		std::cout << "Error loading Hit sound!" << std::endl;
	}
	if (!wingSoundBuffer.loadFromFile(WING_SOUND_FILEPATH))
	{
		std::cout << "Error loading Hit sound!" << std::endl;
	}

	hitSound = std::make_unique<sf::Sound>(hitSoundBuffer);
	pointSound = std::make_unique<sf::Sound>(pointSoundBuffer);
	wingSound = std::make_unique<sf::Sound>(wingSoundBuffer);


	data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
	background = std::make_unique<sf::Sprite>(data->assets.GetTexture("Game Background"));

	data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
	data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
	data->assets.LoadTexture("Land", LAND_FILEPATH);
	data->assets.LoadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
	data->assets.LoadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
	data->assets.LoadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
	data->assets.LoadTexture("Bird Frame 4", BIRD_FRAME_4_FILEPATH);
	data->assets.LoadTexture("Scoring Pipe", SCORING_PIPE_FILEPATH);
	data->assets.LoadFont("Flappy Font", FLAPPY_FONT_FILEPATH);

	pipe = std::make_unique<Pipe>(data);
	land = std::make_unique<Land>(data);
	bird = std::make_unique<Bird>(data);
	flash = std::make_unique<Flash>(data);
	hud = std::make_unique<HUD>(data);



	hud->UpdateScore(score);
}

void GameState::HandleInput()
{
	while (const std::optional event = data->window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			data->window.close();

		if (data->input.IsSpriteClicked(*background, sf::Mouse::Button::Left, data->window))
		{
			if (gameState != GameStates::eGameOver)
			{
				gameState = GameStates::ePlaying;
				bird->Tap();

				wingSound->play();
			}
		}
	}
}

void GameState::Update(float dt)
{
	if (gameState != GameStates::eGameOver)
	{
		bird->Animate(dt);
		land->MoveLand(dt);
	}

	if (gameState == GameStates::ePlaying)
	{
		pipe->MovePipes(dt);

		if (clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY)
		{
			pipe->RandomizePipeOffset();
			pipe->SpawnInvisiblePipe();
			pipe->SpawnBottomPipe();
			pipe->SpawnTopPipe();
			pipe->SpawnScoringPipe();

			clock.restart();
		}

		bird->Update(dt);


		// Collisions with land
		std::vector<sf::Sprite> landSprites = land->GetSprites();

		for (size_t i = 0; i < landSprites.size(); i++)
		{
			if (collision.CheckSpriteCollision(bird->GetSprite(), 0.7f, landSprites.at(i), 1.0f))
			{
				gameState = GameStates::eGameOver;
				clock.restart();

				hitSound->play();
			}
		}

		// Collisions with pipes
		std::vector<sf::Sprite> pipeSprites = pipe->GetSprites();
		for (size_t i = 0; i < pipeSprites.size(); i++)
		{
			if (collision.CheckSpriteCollision(bird->GetSprite(), 0.8f, pipeSprites.at(i), 1.0f))
			{
				gameState = GameStates::eGameOver;
				clock.restart();

				hitSound->play();
			}
		}


		// Scoring, collisions with scoring(invisible) pipes
		if(gameState == GameStates::ePlaying)
		{
			std::vector<sf::Sprite>& scoringSprites = pipe->GetScoringSprites();
			for (size_t i = 0; i < scoringSprites.size(); i++)
			{
				if (collision.CheckSpriteCollision(bird->GetSprite(), 0.2f, scoringSprites.at(i), 1.0f))
				{
					score++;

					hud->UpdateScore(score);

					scoringSprites.erase(scoringSprites.begin() + i);

					pointSound->play();
				}
			}
		}
	}


	if(gameState == GameStates::eGameOver)
	{
		flash->Show(dt);

		if (clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APPEARS)
		{
			data->machine.AddState(StateRef(new GameOverState(data, score)), true);
		}
	}


}

void GameState::Draw(float dt)
{
	data->window.clear();

	data->window.draw(*background);
	pipe->DrawPipes();
	land->DrawLand();
	bird->Draw();
	flash->Draw();
	hud->Draw();

	data->window.display();
}

void GameState::Pause()
{ }

void GameState::Resume()
{ }
