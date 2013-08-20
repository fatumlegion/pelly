#ifndef LEVELWORLD_HPP
#define LEVELWORLD_HPP
#include "GameWorld.hpp"
#include "AssetContainer.hpp"
#include "Player.hpp"
#include "Block.hpp"
#include <vector>

class LevelWorld : public GameWorld
{
private:
	Player *player;
	AssetContainer *ac;
	std::vector<Block> cont_blocks;
public:
	LevelWorld();
	~LevelWorld();
	void input(sf::Event &event);
	void draw(sf::RenderWindow &rwin, float interp);
	void update(float dt);
};
#endif