#include "LevelWorld.hpp"
#include "Application.hpp"

LevelWorld::LevelWorld()
{
	ac = new AssetContainer();
	ac->addTexture("player", "res/images/player.png");
	ac->addTexture("tiles", "res/images/tiles.png");
	
	player = new Player(*ac->getTexture("player"));
	
	vw_main.reset(sf::FloatRect(0, 0, Application::getSingleton()->getVideoMode().width, Application::getSingleton()->getVideoMode().height));
	
	xIndex = 0;
	yIndex = 0;
	
	for (int i = 0; i < 15; i++)
	{
		addGroundBlock(96 + i * 32, 160);
	}
	
	addSpringBlock(96 + 32, 160 - 32);
	
	for (int i = 0; i < 17; i++)
	{
		addGroundBlock(64 + i * 32, 448);
	}
}

LevelWorld::~LevelWorld()
{
	delete player;
	delete ac;
}

void LevelWorld::addGroundBlock(int x, int y)
{
	Block block;
	block.sprite.setTexture(*ac->getTexture("tiles"));
	block.sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	block.sprite.setPosition(x, y);
	block.box = sf::FloatRect(x, y, 32, 32);
	block.type = BlockType::Ground;
	cont_blocks[x / 32][y / 32] = block;
}

void LevelWorld::addSpringBlock(int x, int y)
{
	Block block;
	block.sprite.setTexture(*ac->getTexture("tiles"));
	block.sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
	block.sprite.setPosition(x, y);
	block.box = sf::FloatRect(x, y + 25, 32, 7);
	block.type = BlockType::Spring;
	cont_blocks[x / 32][y / 32] = block;
}

void LevelWorld::input(sf::Event &event)
{
	player->input(event);
}

bool LevelWorld::blockExists(int x, int y)
{
	if (cont_blocks.find(x) != cont_blocks.end())
	{
		if (cont_blocks[x].find(y) != cont_blocks[x].end())
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

void LevelWorld::draw(sf::RenderWindow &rwin, float interp)
{	
	xIndex = (vw_main.getCenter().x - (vw_main.getSize().x / 2)) / 32;
	yIndex = (vw_main.getCenter().y - (vw_main.getSize().y / 2)) / 32;

	for (int cx = xIndex - 1; cx < xIndex + 24; cx++)
	{
		for (int cy = yIndex - 1; cy < yIndex + 15; cy++)
		{
			rwin.draw(cont_blocks[cx][cy].sprite);
		}
	}
	
	player->draw(rwin, interp);
}

void LevelWorld::update(float dt)
{
	player->update(dt);

	/*int bottomPlayerCoord = player->getPosition().y / 32;
	int rightPlayerCoord = player->getPosition().x / 32;
	
	for (int i = rightPlayerCoord - 7; i < rightPlayerCoord + 7; i++)
	{
		//for (int j = bottomPlayerCoord; blockExists(i, j); j--)
		//{
			//printf("%i\n", j);
			player->touchBlock(cont_blocks[i][bottomPlayerCoord]);
		//}
	}*/
	
	xIndex = (vw_main.getCenter().x - (vw_main.getSize().x / 2)) / 32;
	yIndex = (vw_main.getCenter().y - (vw_main.getSize().y / 2)) / 32;

	for (int cx = xIndex - 1; cx < xIndex + 24; cx++)
	{
		for (int cy = yIndex - 1; cy < yIndex + 15; cy++)
		{
			player->touchBlock(cont_blocks[cx][cy]);
		}
	}
}
