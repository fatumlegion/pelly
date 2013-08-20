#include "Player.hpp"
#include <stdio.h>

Player::Player(sf::Texture &txtr)
{
	self.setTexture(txtr);
	
	pos = sf::Vector2f(164, 100);	
	xs = 0.0f;
	fric = 1.1f;
	grav = 0;
	moving = false;
	revGrav = false;
	
	self.setPosition(pos);
	self.setOrigin(self.getTextureRect().width / 2, self.getTextureRect().height);
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
				case sf::Keyboard::Space:
					grav = 0;
					if (revGrav == false)
					{
						self.setRotation(180);
						revGrav = true;
					}
					else
					{
						self.setRotation(0);
						revGrav = false;
					}
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
	if (grav != 0)
	{
		posInterp.y += interp;
	}
	
	self.setPosition(posInterp);
	rwin.draw(self);
}

void Player::touchBlock(Block &b)
{
	if (b.box.contains(pos) || (b.box.contains(pos.x - 16, pos.y)) || (b.box.contains(pos.x + 16, pos.y)))
	{
		grav = 0;
		if (!revGrav) pos.y = b.box.top;
		if (revGrav) pos.y = b.box.top + 32;
	}
	
	if (b.box.contains(pos.x - 16, pos.y - 3))
	{
		xs = 0;
	}
}

void Player::update(float dt)
{
	if (revGrav)
		grav -= 1;
	else
		grav += 1;
	pos.y += grav;
	
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
	
	if ((right == false && left == false) || (right == true && left == true))
	{
		moving = false;
	}
	
	pos.x += xs;
	xs /= fric;
}