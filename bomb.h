#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
#include <string.h>
using namespace sf;

class Bomb
{

public:

    Sprite spriteBomb;
    Texture texBomb;
    int x, y;

    Bomb () {}

    Bomb (int z1, int z2){
		
		this->x = z1 + 34;
		this->y = z2;

        texBomb.loadFromFile("img/laserRed11.png");
		spriteBomb.setTexture(texBomb);
		spriteBomb.setPosition(x, y);
		spriteBomb.setScale(0.75, 0.75);
    }

    void operator=(const Bomb &gola)
	{
		this->x = gola.spriteBomb.getPosition().x;
		this->y = gola.spriteBomb.getPosition().y;

		texBomb.loadFromFile("img/laserRed11.png");
		spriteBomb.setTexture(texBomb);
		spriteBomb.setPosition(x, y);
		spriteBomb.setScale(0.75, 0.75);
	}
};