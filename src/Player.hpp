#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>
#include "Block.hpp"
class Player
{
private:
	sf::Sprite self;
	bool right, left, moving, canJump, revGrav, canRotate, inRotation;
	sf::Vector2f pos;
	float xs, fric, grav, currentRotation, targetRotation;
	sf::FloatRect box;
public:
	Player(sf::Texture &txtr);
	~Player();
	void input(sf::Event &event);
	void draw(sf::RenderWindow &rwin, float interp);
	void update(float dt);
	
	void touchBlock(Block &b);
	
	sf::Vector2f getPosition() { return self.getPosition(); }
};
#endif