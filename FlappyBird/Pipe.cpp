#include "Pipe.h"
#include "DEFINITIONS.h"
#include <iostream>

Pipe::Pipe(GameDataRef data)
	: data(data)
{
	landHeight = data->assets.GetTexture("Land").getSize().y;
	pipeSpawnYOffset = 0;
}

Pipe::~Pipe()
{ }

void Pipe::SpawnBottomPipe()
{
	sf::Sprite sprite(data->assets.GetTexture("Pipe Up"));

	auto windowSize = data->window.getSize();
	auto bounds = sprite.getGlobalBounds();

	sprite.setPosition(sf::Vector2f(static_cast<float>(windowSize.x),
		static_cast<float>(windowSize.y) - bounds.size.y - pipeSpawnYOffset));

	pipeSprites.push_back(sprite);
}

void Pipe::SpawnTopPipe()
{
	sf::Sprite sprite(data->assets.GetTexture("Pipe Down"));

	auto windowSize = data->window.getSize();
	auto bounds = sprite.getGlobalBounds();

	sprite.setPosition(sf::Vector2f(static_cast<float>(windowSize.x), -pipeSpawnYOffset));

	pipeSprites.push_back(sprite);
}

void Pipe::SpawnInvisiblePipe()
{
	sf::Sprite sprite(data->assets.GetTexture("Pipe Up"));

	auto windowSize = data->window.getSize();
	auto bounds = sprite.getGlobalBounds();
	
	sprite.setPosition(sf::Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y) + bounds.size.y + pipeSpawnYOffset));

	sprite.setColor(sf::Color::Black);

	pipeSprites.push_back(sprite);
}

void Pipe::SpawnScoringPipe()
{
	sf::Sprite sprite(data->assets.GetTexture("Scoring Pipe"));

	auto windowSize = data->window.getSize();
	auto bounds = sprite.getGlobalBounds();

	sprite.setPosition(sf::Vector2f(static_cast<float>(windowSize.x), 0));

	scoringPipes.push_back(sprite);
}


void Pipe::MovePipes(float dt)
{
	for (size_t i = 0; i < pipeSprites.size(); i++)
	{
		if (pipeSprites.at(i).getPosition().x < 0 - pipeSprites.at(i).getGlobalBounds().size.x)
		{
			pipeSprites.erase(pipeSprites.begin() + i);
		}
		else
		{
			float movement = PIPE_MOVEMENT_SPEED * dt;

			pipeSprites.at(i).move({ -movement, 0 });
		}
	}

	for (size_t i = 0; i < scoringPipes.size(); i++)
	{
		if (scoringPipes.at(i).getPosition().x < 0 - scoringPipes.at(i).getGlobalBounds().size.x)
		{
			scoringPipes.erase(scoringPipes.begin() + i);
		}
		else
		{
			float movement = PIPE_MOVEMENT_SPEED * dt;

			scoringPipes.at(i).move({ -movement, 0 });
		}
	}
}

void Pipe::DrawPipes()
{
	for (unsigned short i = 0; i < pipeSprites.size(); i++)
	{
		data->window.draw(pipeSprites.at(i));
	}
}

void Pipe::RandomizePipeOffset()
{
	pipeSpawnYOffset = rand() % (landHeight + 1);
}

const std::vector<sf::Sprite>& Pipe::GetSprites() const
{
	return pipeSprites;
}

std::vector<sf::Sprite>& Pipe::GetScoringSprites()
{
	return scoringPipes;
}
