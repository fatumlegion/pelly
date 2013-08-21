#ifndef BLOCK_HPP
#define BLOCK_HPP
#include "BlockType.hpp"
struct Block
{
	sf::Sprite sprite;
	sf::FloatRect box;
	BlockType type;
};
#endif