#include "Player.hpp"
#include <stdio.h>

Player::Player(sf::Texture &txtr)
{
	self.setTexture(txtr);
	
	pos = sf::Vector2f(300, 100);	
	xs = 0.0f;
	fric = 1.1f;
	grav = 0;
	currentRotation = 0;
	targetRotation = 0;
	moving = false;
	revGrav = false;
	inRotation = false;
	canRotate = false;
	canJump = false;

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
					if (canRotate == true)
					{
						grav = 0;
						if (revGrav == false)
						{
							currentRotation = 0;
							revGrav = true;
						}
						else
						{
							currentRotation = 180;
							revGrav = false;
						}
						inRotation = true;
						canRotate = false;
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
	
	if (inRotation) self.setRotation(currentRotation + interp);
	
	self.setPosition(posInterp);
	
	rwin.draw(self);
	
	if (!revGrav)
	{
		box = sf::FloatRect(pos.x - 16, pos.y - 32, 32, 32);
	}
	else
	{
		box = sf::FloatRect(pos.x - 16, pos.y, 32, 32);
	}
}

void Player::touchBlock(Block &b)
{
	//if (grav > 0)
	//{
		if (b.box.contains(pos) || (b.box.contains(pos.x - 16, pos.y)) || (b.box.contains(pos.x + 16, pos.y)))
		{
			if (b.type == BlockType::Ground)
			{
				if (revGrav == false)
				{
					if (grav > 0)
					{
						grav = 0;
						canRotate = true;
						pos.y = b.box.top;
						canJump = true;
					}
				}
				else
				{
					grav = 0;
					canRotate = true;
					pos.y = b.box.top + 32;
					canJump = true;
				}
			}
		}
	//}
	
	if (b.box.contains(pos.x - 16, pos.y - 5))
	{
		if (b.type == BlockType::Ground)
		{
			if (!revGrav)
			{
				pos.x -= xs * fric;
				xs = 0;
			}
		}
	}
	
	if (b.box.intersects(box))
	{
		if (b.type == BlockType::Spring)
		{
			if (canJump == true)
			{
				grav -= 20;
				canJump = false;
			}
		}
	}
}

void Player::update(float dt)
{
	if (revGrav)
		grav -= 1;
	else
		grav += 1;
	pos.y += grav;
	
	if (inRotation == true)
	{
		if (revGrav == true)
		{
			currentRotation += 10;
			if (currentRotation >= 180)
			{
				self.setRotation(180);
				inRotation = 0;
			}
		}
		else
		{
			currentRotation -= 10;
			if (currentRotation <= 0)
			{
				self.setRotation(0);
				inRotation = false;
			}
		}
	}
	
	if (right == true && left == false)
	{
		xs += 0.5f;
	}
	
	if (right == false && left == true)
	{
		xs -= 0.5f;
	}
	
	if ((right == false && left == false) || (right == true && left == true))
	{
		moving = false;
	}
	
	pos.x += xs;
	xs /= fric;
}