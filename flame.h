#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
#include "enemy.h"
#include <string.h>
using namespace sf;

class Flame
{
public:

    Sprite spriteF;
    Texture texF;
    int x, y;

    Flame() {}

    Flame (int z1, int z2)
    {   
        this->x = z1;
		this->y = z2;

        texF.loadFromFile("img/laserGreen07.png");
		spriteF.setTexture(texF);
		spriteF.setPosition(x, y);
		spriteF.setScale(1.5, 6.7);
    }
};