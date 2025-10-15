#include "Bird.h"

Bird::Bird(GameDataRef data)
	:data(data)
{
	animationIterator = 0;

	animationFrames.push_back(data->assets.GetTexture("Bird Frame 1"));
	animationFrames.push_back(data->assets.GetTexture("Bird Frame 2"));
	animationFrames.push_back(data->assets.GetTexture("Bird Frame 3"));
	animationFrames.push_back(data->assets.GetTexture("Bird Frame 4"));


	birdSprite = std::make_unique<sf::Sprite>(animationFrames.at(animationIterator));
	
	birdSprite->setPosition(sf::Vector2f((data->window.getSize().x / 4) - 
		(birdSprite->getGlobalBounds().size.x / 2), (data->window.getSize().y / 2) - (birdSprite->getGlobalBounds().size.y / 2)
	));

	birdState = BIRD_STATE_STILL;

	sf::Vector2f origin = sf::Vector2f(birdSprite->getGlobalBounds().size.x / 2, birdSprite->getGlobalBounds().size.y / 2);
	birdSprite->setOrigin(origin);

	rotation = 0;
}

void Bird::Draw()
{
	data->window.draw(*birdSprite);
}

void Bird::Animate(float dt)
{
	if (clock.getElapsedTime().asSeconds() > BIRD_ANIMATION_DURATION / animationFrames.size())
	{
		if (animationIterator < animationFrames.size() - 1)
		{
			animationIterator++;
		}
		else
		{
			animationIterator = 0;
		}

		birdSprite->setTexture(animationFrames.at(animationIterator));
		clock.restart();
	}
}

void Bird::Update(float dt)
{
	if (birdState == BIRD_STATE_FALLING)
	{
		birdSprite->move({ 0, GRAVITY * dt });

		rotation += ROTATION_SPEED * dt;

		if (rotation > 25.0f)
		{
			rotation = 25.0f;
		}

		birdSprite->setRotation(sf::degrees(rotation));
	}
	else if (birdState == BIRD_STATE_FLYING)
	{
		birdSprite->move({0, -FLYING_SPEED * dt});

		rotation -= ROTATION_SPEED * dt;

		if (rotation < 25.0f)
		{
			rotation = -25.0f;
		}

		birdSprite->setRotation(sf::degrees(rotation));
	}

	if (movementClock.getElapsedTime().asSeconds() > FLYING_DURATION)
	{
		movementClock.restart();
		birdState = BIRD_STATE_FALLING;
	}
}

void Bird::Tap()
{
	movementClock.restart();
	birdState = BIRD_STATE_FLYING;
}

const sf::Sprite& Bird::GetSprite() const
{
	return *birdSprite;
}
