#include "TextureManager.h"

unordered_map<string, sf::Texture> TextureManager::textures;
string TextureManager::imagesDirectory = "images/";

void TextureManager::LoadTexture(string fileName) {

	string path = imagesDirectory;	// Could change, but in this case is correct
	path += (fileName + ".png");

	textures[fileName].loadFromFile(path);
}

sf::Texture& TextureManager::GetTexture(string textureName) {
	// if texture doesn't exist in map, load first, then return it
	if (textures.find(textureName) == textures.end()) {	// Didn't find, so attempts to load file
		LoadTexture(textureName);
	}

	return textures[textureName];
}

void TextureManager::SetImagesDirectory(string dirPath) {
	imagesDirectory = dirPath;
}

void TextureManager::Clear() {
	textures.clear(); // get rid of all stored objects
}