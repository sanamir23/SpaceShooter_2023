#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
#include "enemy.h"
#include <string.h>
using namespace sf;

class Monster : public Enemy
{
public:

    int x, y;

    Monster ()
    {   
        this->x = 210;
		this->y = 0;

        texE.loadFromFile("img/monster1.png");
		spriteE.setTexture(texE);
		spriteE.setPosition(x, y);
		spriteE.setScale(0.5, 0.5);
    }
};