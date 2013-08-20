#include "LevelWorld.hpp"

LevelWorld::LevelWorld()
{
	ac = new AssetContainer();
	ac->addTexture("player", "res/images/player.png");
	
	player = new Player(*ac->getTexture("player"));
}

LevelWorld::~LevelWorld()
{
	delete player;
	delete ac;
}

void LevelWorld::input(sf::Event &event)
{
	player->input(event);
}

void LevelWorld::draw(sf::RenderWindow &rwin, float interp)
{
	player->draw(rwin, interp);
}

void LevelWorld::update(float dt)
{
	player->update(dt);
}
