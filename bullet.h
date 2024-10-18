#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
#include <string.h>
using namespace sf;

class Bullet
{

public:
	Sprite spriteb;
	Texture tex;
	int x, y;

	Bullet() {
		tex.loadFromFile("img/laserBlue01.png");

	}

	Bullet(int x1, int y1)
	{
		this->x = x1 + 34;
		this->y = y1 - 50;

		tex.loadFromFile("img/laserBlue01.png");
		spriteb.setTexture(tex);
		spriteb.setPosition(x, y);
		spriteb.setScale(0.75, 0.75);
	}

	void operator=(const Bullet &goli)
	{	
		this->x = goli.spriteb.getPosition().x;
		this->y = goli.spriteb.getPosition().y;

		spriteb.setTexture(tex);
		spriteb.setPosition(x, y);
		spriteb.setScale(0.75, 0.75);
	}
};
