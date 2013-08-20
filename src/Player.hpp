#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>
class Player
{
private:
	sf::Sprite self;
	bool right, left, moving;
	sf::Vector2f pos;
	float xs, fric;
public:
	Player(sf::Texture &txtr);
	~Player();
	void input(sf::Event &event);
	void draw(sf::RenderWindow &rwin, float interp);
	void update(float dt);
};
#endif