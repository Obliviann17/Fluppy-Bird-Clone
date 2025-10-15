#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Game.h"
#include "DEFINITIONS.h"

class Pipe
{
public:
	Pipe(GameDataRef data);
	~Pipe();

	void SpawnBottomPipe();
	void SpawnTopPipe();
	void SpawnInvisiblePipe();
	void SpawnScoringPipe();

	void MovePipes(float dt);
	void DrawPipes();
	void RandomizePipeOffset();

	const std::vector<sf::Sprite>& GetSprites() const;
	std::vector<sf::Sprite>& GetScoringSprites();

private:
	GameDataRef data;
	std::vector<sf::Sprite> pipeSprites;
	std::vector<sf::Sprite> scoringPipes;

	int landHeight;
	int pipeSpawnYOffset;
};

