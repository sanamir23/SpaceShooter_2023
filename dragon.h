#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
#include "enemy.h"
#include <string.h>
using namespace sf;


class Dragon : public Enemy
{
public:

    int x, y;

    Dragon ()
    {   
        this->x = 180;
		this->y = 0;

        texE.loadFromFile("img/bestD.png");
		spriteE.setTexture(texE);
		spriteE.setPosition(x, y);
		spriteE.setScale(0.7, 0.7);
    }
};