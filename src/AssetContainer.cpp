#include "AssetContainer.hpp"
#ifdef __APPLE__
	#include "ResourceDirectory.hpp"
#endif
#include <stdio.h>

AssetContainer::AssetContainer()
{

}

AssetContainer::~AssetContainer()
{
	cont_textures.clear();
}

void AssetContainer::addTexture(std::string name, std::string path)
{
	cont_textures[name] = new sf::Texture();
	#ifdef __APPLE__
		cont_textures[name]->loadFromFile(getRPath() + "/" + path.c_str());
	#else
		cont_textures[name]->loadFromFile(path.c_str());
	#endif
}

void AssetContainer::addMusic(std::string name, std::string path)
{
	cont_music[name] = new sf::Music();
	cont_music[name]->openFromFile(path.c_str());
}

void AssetContainer::addFont(std::string name, std::string path)
{
	cont_fonts[name] = new sf::Font();
	cont_fonts[name]->loadFromFile(path.c_str());
}


sf::Texture *AssetContainer::getTexture(std::string name)
{
	if (!cont_textures[name])
		printf("Texture %s doesn't exist.\n", name.c_str());
	return cont_textures[name];
}

sf::Music *AssetContainer::getMusic(std::string name)
{
	if (!cont_music[name])
		printf("Music %s doesn't exist.\n", name.c_str());
	return cont_music[name];
}

sf::Font* AssetContainer::getFont(std::string name)
{
	if (!cont_fonts[name])
		printf("Font %s doesn't exist.\n", name.c_str());
	return cont_fonts[name];
}
