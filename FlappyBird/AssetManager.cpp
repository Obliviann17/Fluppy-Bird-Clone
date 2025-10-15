#include "AssetManager.h"

AssetManager::AssetManager()
{ }

AssetManager::~AssetManager()
{ }

void AssetManager::LoadTexture(const std::string& name, const std::string& fileName)
{
	sf::Texture tex;

	if (!tex.loadFromFile(fileName))
	{
		throw std::runtime_error("Failed to open texture: " + fileName);
	}
	//this->textures.emplace(name, std::move(tex));
	this->textures[name] = std::move(tex);
}

sf::Texture& AssetManager::GetTexture(const std::string& name)
{
	return this->textures.at(name);
}

void AssetManager::LoadFont(const std::string& name, const std::string& fileName)
{
	sf::Font font;

	if (!font.openFromFile(fileName))
	{

		throw std::runtime_error("Failed to open font: " + fileName);
	}
	this->fonts.emplace(name, std::move(font));
}

sf::Font& AssetManager::GetFont(const std::string& name)
{
	return this->fonts.at(name);
}
