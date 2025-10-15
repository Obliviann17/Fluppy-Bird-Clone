#include "Collision.h"

Collision::Collision()
{
}

bool Collision::CheckSpriteCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2)
{
	return sprite1.getGlobalBounds().findIntersection(sprite2.getGlobalBounds()).has_value();
}

bool Collision::CheckSpriteCollision(const sf::Sprite& sprite1, float scale1, const sf::Sprite& sprite2, float scale2)
{
	auto s1 = sprite1;
	auto s2 = sprite2;

	s1.setScale({ scale1, scale1 });
	s2.setScale({ scale2, scale2 });

	return s1.getGlobalBounds().findIntersection(s2.getGlobalBounds()).has_value();
}
