#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
#include "enemy.h"
#include <string.h>
using namespace sf;

class Laser
{
public:

    Sprite spriteL;
    Texture texL;
    int x, y;

    Laser() {}

    Laser (int z1, int z2)
    {   
        this->x = z1;
		this->y = z2;
        
        texL.loadFromFile("img/laserRed07.png");
		spriteL.setTexture(texL);
		spriteL.setPosition(x, y);
		spriteL.setScale(2.0, 11.0);
    }
};