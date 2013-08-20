#ifndef LEVELWORLD_HPP
#define LEVELWORLD_HPP
#include "GameWorld.hpp"
#include "AssetContainer.hpp"
#include "Player.hpp"
class LevelWorld : public GameWorld
{
private:
	Player *player;
	AssetContainer *ac;
public:
	LevelWorld();
	~LevelWorld();
	void input(sf::Event &event);
	void draw(sf::RenderWindow &rwin, float interp);
	void update(float dt);
};
#endif