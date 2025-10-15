#include "HUD.h"

HUD::HUD(GameDataRef data)
	:data(data)
{
	scoreText = std::make_unique<sf::Text>(data->assets.GetFont("Flappy Font"));

	scoreText->setString("0");
	scoreText->setCharacterSize(128);
	scoreText->setFillColor(sf::Color::White);

	scoreText->setOrigin(sf::Vector2f(scoreText->getGlobalBounds().size.x / 2, scoreText->getGlobalBounds().size.y / 2));
	scoreText->setPosition(sf::Vector2f(data->window.getSize().x / 2, data->window.getSize().y / 5));
}

void HUD::Draw()
{
	data->window.draw(*scoreText);
}

void HUD::UpdateScore(int score)
{
	scoreText->setString(std::to_string(score));
}
