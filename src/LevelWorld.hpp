#ifndef LEVELWORLD_HPP
#define LEVELWORLD_HPP
#include "GameWorld.hpp"
#include "AssetContainer.hpp"
#include "Player.hpp"
#include "BlockType.hpp"
#include "Block.hpp"
#include <map>

struct Spring
{
	sf::Sprite sprite;
};

class LevelWorld : public GameWorld
{
private:
	Player *player;
	AssetContainer *ac;
	std::map<int, std::map<int, Block> > cont_blocks;
	bool blockExists(int x, int y);
	
	void addGroundBlock(int x, int y);
	void addSpringBlock(int x, int y);
	
	sf::View vw_main;
	int xIndex, yIndex;
public:
	LevelWorld();
	~LevelWorld();
	void input(sf::Event &event);
	void draw(sf::RenderWindow &rwin, float interp);
	void update(float dt);
};
#endif