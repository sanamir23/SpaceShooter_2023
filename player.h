#pragma once
#include <SFML/Graphics.hpp>
#include <string.h>
using namespace sf;

class Player
{

public:
	Texture tex;
	Sprite sprite;
	float speed = 0.5;
	int x, y;

	Player(std::string png_path)
	{
		tex.loadFromFile(png_path);
		sprite.setTexture(tex);
		x = 340;
		y = 540;
		sprite.setPosition(x, y);
		sprite.setScale(0.75, 0.75);
	}

	void move(std::string s)
	{
		float delta_x = 0, delta_y = 0;

		if (sprite.getPosition().y >= 780)
		{
			sprite.setPosition(sprite.getPosition().x, 0);
		}

		else if (sprite.getPosition().y <= 0)
		{
			sprite.setPosition(sprite.getPosition().x, 780);
		}

		if (sprite.getPosition().x >= 780)
		{
			sprite.setPosition(0, sprite.getPosition().y);
		}

		else if (sprite.getPosition().x <= 0)
		{
			sprite.setPosition(780, sprite.getPosition().y);
		}

		if (s == "l")
			delta_x = -1; // move the player left
		else if (s == "r")
			delta_x = 1; // move the player right
		else if (s == "u")
			delta_y = -1;
		else if (s == "d")
			delta_y = 1;

		else if (s == "r1")
		{
			tex.loadFromFile("img/r.png");
			sprite.setTexture(tex);
		}

		else if (s == "r2")
		{
			tex.loadFromFile("img/rb.png");
			sprite.setTexture(tex);
		}

		else if (s == "r3")
		{
			tex.loadFromFile("img/l.png");
			sprite.setTexture(tex);
		}

		else if (s == "r4")
		{
			tex.loadFromFile("img/lb.png");
			sprite.setTexture(tex);
		}

		delta_x *= speed;
		delta_y *= speed;

		sprite.move(delta_x, delta_y);
	}
};
