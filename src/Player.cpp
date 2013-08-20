#include "Player.hpp"

Player::Player(sf::Texture &txtr)
{
	self.setTexture(txtr);
	
	pos = sf::Vector2f(100, 100);
	
	self.setPosition(pos);
	
	xs = 0.0f;
	fric = 1.1f;
	
	moving = false;
}

Player::~Player()
{

}

void Player::input(sf::Event &event)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Right:
					right = true;
				break;
				case sf::Keyboard::Left:
					left = true;
				break;
			}
		break;
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
				case sf::Keyboard::Right:
					right = false;
				break;
				case sf::Keyboard::Left:
					left = false;
				break;
			}
		break;
	}
}

void Player::draw(sf::RenderWindow &rwin, float interp)
{
	sf::Vector2f posInterp = pos;
	
	if (moving == true)
	{
		posInterp.x += interp;
	}
	self.setPosition(posInterp);
	rwin.draw(self);
}

void Player::update(float dt)
{
	if (right == true && left == false)
	{
		xs += 0.5f;
		moving = true;
	}
	
	if (right == false && left == true)
	{
		xs -= 0.5f;
		moving = true;
	}
	
	if (right == false && left == false)
	{
		moving = false;
	}
	
	pos.x += xs;
	xs /= fric;
}