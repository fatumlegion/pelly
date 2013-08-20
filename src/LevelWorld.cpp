#include "LevelWorld.hpp"

LevelWorld::LevelWorld()
{
	ac = new AssetContainer();
	ac->addTexture("player", "res/images/player.png");
	ac->addTexture("tiles", "res/images/tiles.png");
	
	player = new Player(*ac->getTexture("player"));
	
	for (int i = 0; i < 15; i++)
	{
		Block block;
		block.sprite.setTexture(*ac->getTexture("tiles"));
		block.sprite.setPosition(100 + i * 32, 164);
		block.box = sf::FloatRect(100 + i * 32, 164, 32, 32);
		cont_blocks.push_back(block);
	}
	
	Block block;
	block.sprite.setTexture(*ac->getTexture("tiles"));
	block.sprite.setPosition(100, 132);
	block.box = sf::FloatRect(100, 132, 32, 32);
	cont_blocks.push_back(block);
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
	for (int i = 0; i < cont_blocks.size(); i++)
	{
		rwin.draw(cont_blocks[i].sprite);
	}
}

void LevelWorld::update(float dt)
{
	player->update(dt);
	for (int i = 0; i < cont_blocks.size(); i++)
	{
		player->touchBlock(cont_blocks[i]);
	}
}
