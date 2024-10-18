#pragma once
#include <SFML/Graphics.hpp>
#include<string.h>
#include "enemy.h"
using namespace sf;

class Invader : public Enemy {

public:

    
};

class Alpha : public Invader {

public:

    //Texture texA;
    //Sprite spriteA;
    
    Alpha(){
        texE.loadFromFile("img/enemy_3.png");
		spriteE.setTexture(texE);
		spriteE.setScale(0.6, 0.6);
    }
};


class Beta : public Invader {

public:

    //Texture texBeta;
    //Sprite spriteBeta;
    
    Beta(){
        texE.loadFromFile("img/enemy_2.png");
		spriteE.setTexture(texE);
		spriteE.setScale(0.7, 0.7);
    }
};


class Gamma : public Invader {

public:

    //Texture texG;
    //Sprite spriteG;
    
    Gamma(){
        texE.loadFromFile("img/enemy_1.png");
		spriteE.setTexture(texE);
		spriteE.setScale(0.7, 0.7);
    }
};