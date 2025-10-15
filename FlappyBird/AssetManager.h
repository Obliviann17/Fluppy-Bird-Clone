#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <map>

class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	void LoadTexture(const std::string& name, const std::string& fileName);
	// додати перевірку на out_of_range
	sf::Texture& GetTexture(const std::string& name);

	void LoadFont(const std::string& name, const std::string& fileName);
	// додати перевірку на out_of_range
	sf::Font& GetFont(const std::string& name);

private:
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::Font> fonts;
};

