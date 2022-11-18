#pragma once
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
using std::unordered_map;
using std::string;

class TextureManager
{
	static unordered_map<string, sf::Texture> textures;
	static string imagesDirectory;
	static void LoadTexture(string textureName); // LoadTexture("space")
public:
	static sf::Texture& GetTexture(string textureName); // GetTexture("space")
	static void SetImagesDirectory(string directoryPath);
	static void Clear(); // Call this once at end of main()
};

