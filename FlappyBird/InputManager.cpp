#include "InputManager.h"

InputManager::InputManager()
{ }

InputManager::~InputManager()
{ }

bool InputManager::IsSpriteClicked(sf::Sprite& object, sf::Mouse::Button button, sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(button))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::FloatRect bounds = object.getGlobalBounds();

		if (bounds.contains(static_cast<sf::Vector2f>(mousePos)))
		{
			return true;
		}
	}
	return false;
}

sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& window)
{
	return sf::Mouse::getPosition(window);
}
