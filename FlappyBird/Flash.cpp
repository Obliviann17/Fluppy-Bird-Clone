#include "Flash.h"

Flash::Flash(GameDataRef data)
	: data(data), flashOn(true)
{
	shape = sf::RectangleShape(sf::Vector2f(data->window.getSize()));
	shape.setFillColor(sf::Color(255, 255, 255, 0));

	//flashOn = true;
}

void Flash::Show(float dt)
{
	if (flashOn)
	{
		int alpha = shape.getFillColor().a + (FLASH_SPEED * dt); // maybe need to cast FLASH_SPEED to int

		if (alpha >= 255.0f)
		{
			alpha = 255.0f;
			flashOn = false;
		}

		shape.setFillColor(sf::Color(255, 255, 255, alpha));
	}
	else
	{
		int alpha = shape.getFillColor().a + (FLASH_SPEED * dt); // maybe need to cast FLASH_SPEED to int

		if (alpha >= 0.0f)
		{
			alpha = 0.0f;
			flashOn = false;
		}

		shape.setFillColor(sf::Color(255, 255, 255, alpha));
	}
}

void Flash::Draw()
{
	data->window.draw(shape);
}
