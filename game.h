#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
using namespace std;
#include "math.h"
#include "player.h"
#include "invader.h"
#include "monster.h"
#include "dragon.h"
#include "laser.h"
#include "flame.h"
#include "bullet.h"
#include "bomb.h"
#include "menu.h"
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;

class Game
{

public:
	Menu M;

	Sprite background;
	Texture bg_texture;
	Player *p;
	Bullet *boss;
	Enemy **dushman;
	Bomb *dhamaka;
	Laser *pew;
	Flame *burn;
	int bsize = 0;
	int bombSize;
	int invaderSize;
	int level = 1;
	int score;
	int lives = 5;
	bool showMonster = false;
	bool showDragon = false;

	bool pause = false;
	Sprite pauseSPR;
	Texture pauseTEX;

	bool gameOver = false;
	Sprite GOspr;
	Texture GOtex;

	// add other game attributes

	Game()
	{
		bsize = 0;
		bombSize = 0;
		boss = nullptr;
		dhamaka = nullptr;

		invaderSize = 5;
		dushman = new Enemy *[4];
		dushman[0] = new Alpha[invaderSize];
		dushman[1] = new Beta[invaderSize];
		dushman[2] = new Gamma[invaderSize];
		dushman[3] = new Monster();
		dushman[4] = new Dragon();

		pew = new Laser(dushman[3][0].spriteE.getPosition().x + 160, dushman[3][0].spriteE.getPosition().y + 250);
		burn = new Flame(dushman[4][0].spriteE.getPosition().x + 200, dushman[4][0].spriteE.getPosition().y + 250);

		p = new Player("img/player_ship.png");
		bg_texture.loadFromFile("img/tired3.jpg");
		background.setTexture(bg_texture);
		background.setScale(1.0, 1.0);

		GOtex.loadFromFile("img/gameOver2.png");
		GOspr.setTexture(GOtex);
		GOspr.setPosition(190, 140);
		GOspr.setScale(0.5, 0.5);

		pauseTEX.loadFromFile("img/pause3.png");
		pauseSPR.setTexture(pauseTEX);
		pauseSPR.setPosition(20, 140);

		Music liveSound;
		liveSound.openFromFile("audio/lives.wav");
		liveSound.setLoop(true);
		liveSound.setVolume(60);

		Music levelSound;
		levelSound.openFromFile("audio/level.wav");
		levelSound.setLoop(true);
		levelSound.setVolume(60);

		score = 0;
	}

	void start_game()
	{

		bool end = 0;
		M.display_menu(end);
		if (end)
			return;

		setRectangle();

		Music bgMusic;
		bgMusic.openFromFile("audio/aud98.wav");
		bgMusic.setLoop(true);
		bgMusic.setVolume(40);
		bgMusic.play();

		Music dragon;
		dragon.openFromFile("audio/dragon.wav");
		dragon.setLoop(true);
		dragon.setVolume(60);

		Music monster;
		monster.openFromFile("audio/monster.wav");
		monster.setLoop(true);
		monster.setVolume(60);

		srand(time(0));
		RenderWindow window(VideoMode(780, 780), title);
		Clock clock;
		float timer = 0.0;
		float badTimes = 0.0;
		float endOfTime = 0.0;
		float waqt = 0.0;
		float waqt2 = 0.0;
		float waqt3 = 0.0;

		while (window.isOpen())
		{
			float time = clock.getElapsedTime().asSeconds();
			clock.restart();
			timer += time;
			badTimes += time;
			endOfTime += time;

			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				else if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Space)
					{
						pause = !pause;
					}
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::Left))	 // If left key is pressed
				p->move("l");							 // Player will move to left
			if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
				p->move("r");							 // player will move to right
			if (Keyboard::isKeyPressed(Keyboard::Up))	 // If up key is pressed
				p->move("u");							 // player will move upwards
			if (Keyboard::isKeyPressed(Keyboard::Down))	 // If down key is pressed
				p->move("d");							 // player will move downwards

			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				p->move("r1");
				// tex.Loadfromfile("img/r.png");
				// sprite.setTexture(tex);
			}

			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				p->move("r2");
				// tex.Loadfromfile("img/rb.png");
				// sprite.setTexture(tex);
			}

			if (Keyboard::isKeyPressed(Keyboard::Q))
			{
				p->move("r3");
				// tex.Loadfromfile("img/l.png");
				// sprite.setTexture(tex);
			}

			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				p->move("r4");
				// tex.Loadfromfile("img/lb.png");
				// sprite.setTexture(tex);
			}

			////////////////////////////////////////////////
			/////  Call your functions here            ////
			//////////////////////////////////////////////

			if (!pause)
			{

				destroyEnemy();
				fireBullet();
				fireBomb();
				manageLevel();
				manageLives();

				for (int i = 0; i < bsize; i++)
				{
					if (boss[i].spriteb.getPosition().y <= 0)
						destroyBullet(i);
				}

				if (endOfTime > 2)
				{
					enemyLaser();
					endOfTime = 0;
				}

				if (badTimes > 0.5)
				{
					shootBullet();
					badTimes = 0;
				}
			}

			else
			{

				sf::Font font;
				font.loadFromFile("font/BF.ttf");

				sf::Text pauseT;
				pauseT.setFont(font);
				pauseT.setString("PRESS SPACE KEY TO RESUME");
				pauseT.setCharacterSize(20);
				pauseT.setFillColor(sf::Color::White);
				pauseT.setPosition(180, 300);

				window.draw(pauseT);
			}

			window.clear(Color::Black); // clears the screen
			window.draw(background);	// setting background
			window.draw(p->sprite);		// setting player on screen

			for (int i = 0; i < bsize; i++)
			{
				window.draw(boss[i].spriteb);
			}

			for (int i = 0; i < bombSize; i++)
			{
				window.draw(dhamaka[i].spriteBomb);
			}

			for (int i = 0; i < invaderSize; i++)
			{
				window.draw(dushman[0][i].spriteE);
				window.draw(dushman[1][i].spriteE);
				window.draw(dushman[2][i].spriteE);
			}

			if (showMonster == true)
			{
				monster.play();
				waqt += time;

				if (waqt > 10)
				{
					showMonster = false;
					waqt = 0;
					level++;
					showDragon = true;
					monster.stop();
				}
				
				window.draw(dushman[3][0].spriteE);
				window.draw(pew->spriteL);
			}

			if (showDragon == true)
			{
				dragon.play();
				waqt2 += time;

				if (waqt2 > 10)
				{
					showDragon = false;
					waqt2 = 0;
					dragon.stop();
					window.close();
					gameOver = true;
				}
				window.draw(dushman[4][0].spriteE);
				window.draw(burn->spriteF);
			}

			while (gameOver == true) // shows game over image and game halts
			{
				waqt3 += time;

				if (waqt3 > 10)
				{
					gameOver = false;
					waqt3 = 0;
					window.close();
					highScore(score);
				}

				window.clear(Color::White);
				window.draw(GOspr);
				window.display();
				bgMusic.stop();
			}

			sf::Font font;
			font.loadFromFile("font/BF.ttf");

			sf::Text score_display;
			score_display.setFont(font);
			score_display.setString("SCORE: " + to_string(score));
			score_display.setCharacterSize(20);
			score_display.setFillColor(Color::White);
			score_display.setPosition(0, 0);
			window.draw(score_display);

			sf::Text level_display;
			level_display.setFont(font);
			level_display.setString("LEVEL: " + to_string(level));
			level_display.setCharacterSize(20);
			level_display.setFillColor(Color::White);
			level_display.setPosition(645, 0);
			window.draw(level_display);

			sf::Text lives_display;
			lives_display.setFont(font);
			lives_display.setString("LIVES: " + to_string(lives));
			lives_display.setCharacterSize(20);
			lives_display.setFillColor(Color::White);
			lives_display.setPosition(0, 610);
			window.draw(lives_display);

			window.display(); // Displaying all the sprites
		}
	}

	void highScore(int score)
	{
		string scr = to_string(score);
		sf::RenderWindow window(sf::VideoMode(780, 780), "ENTER PLAYER NAME");

		sf::Font font;
		font.loadFromFile("font/BF.ttf");

		Text text;
		text.setFont(font);
		text.setCharacterSize(30);
		text.setPosition(330, 350);
		text.setFillColor(sf::Color::White);
		text.setString("");

		Texture tex;
		tex.loadFromFile("img/A2.jpg");
		Sprite sprite;
		sprite.setTexture(tex);
		sprite.setScale(1.16, 1.0);

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				if (event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode < 128)
					{
						if (event.text.unicode == '\b') // backspace key
						{
							std::string str = text.getString();
							if (!str.empty())
								str.erase(str.size() - 1);
							text.setString(str);
						}
						else if (event.text.unicode == ' ') // spacebar key
						{
							text.setString(text.getString() + ' ');
						}
						else
						{
							text.setString(text.getString() + static_cast<char>(event.text.unicode));
						}
					}
				}

				if (event.type == Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Enter)
					{
						std::string str = text.getString().toAnsiString();
						M.add(str, scr);
						window.close();
					}
				}
			}

			window.draw(sprite);

			Text highText1;
			highText1.setFont(font);
			highText1.setString("SPACE SHOOTER");
			highText1.setPosition(80, 100); // displaying score text on
			highText1.setFillColor(Color::White);
			highText1.setCharacterSize(50);
			window.draw(highText1);

			highText1.setPosition(84, 100); // displaying score text on
			highText1.setFillColor(Color::Cyan);
			window.draw(highText1);

			highText1.setFont(font);
			highText1.setString("ENTER PLAYER NAME");
			highText1.setPosition(137, 250); // displaying score text on
			highText1.setFillColor(Color::White);
			highText1.setCharacterSize(30);
			window.draw(highText1);

			highText1.setPosition(141, 250); // displaying score text on
			highText1.setFillColor(Color::Magenta);
			window.draw(highText1);

			window.draw(text);

			window.display();
		}
	}

	void destroyEnemy()
	{
		for (int j = 0; j < invaderSize; j++)
		{
			for (int i = 0; i < bsize; i++)
			{
				if ((boss[i].spriteb.getGlobalBounds().intersects(dushman[0][j].spriteE.getGlobalBounds())))
				{
					destroyBullet(i);
					dushman[0][j].spriteE.setPosition(950, 950);
					score += 10;
				}

				else if ((boss[i].spriteb.getGlobalBounds().intersects(dushman[1][j].spriteE.getGlobalBounds())))
				{
					destroyBullet(i);
					dushman[1][j].spriteE.setPosition(950, 950);
					score += 30;
				}

				else if ((boss[i].spriteb.getGlobalBounds().intersects(dushman[2][j].spriteE.getGlobalBounds())))
				{
					destroyBullet(i);
					dushman[2][j].spriteE.setPosition(950, 950);
					score += 50;
				}
			}
		}
	}

	void manageLevel()
	{

		bool check = true;

		// Check if all enemies have been destroyed
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < invaderSize; j++)
			{
				if (dushman[i][j].spriteE.getPosition().x != 950 || dushman[i][j].spriteE.getPosition().y != 950)
				{
					check = false;
					break;
				}
			}

			if (!check)
			{
				break;
			}
		}

		// If all enemies have been destroyed, move to the next level
		if (check)
		{

			level++;

			switch (level)
			{
			case 2:
				setTriangle();
				break;

			case 3:
				setCircle();
				break;

			case 4:
				setX();
				break;

			case 5:
				setDiamond();
				break;

			case 6:
				setHeart();
				break;

			case 7:
				showMonster = true;
				dushman[0][4].spriteE.setPosition(1000, 1000);
				break;

			default:
				break;
			}
		}
	}

	void setRectangle()
	{
		int x_spacing = 153; // horizontal spacing between dushman objects
		int y_spacing = 110; // vertical spacing between dushman objects

		// Top row of dushman objects
		for (int i = 0; i < 5; i++)
		{
			dushman[0][i].spriteE.setPosition(i * x_spacing + 50, 155);
		}

		// Middle row of dushman objects
		for (int i = 0; i < 5; i++)
		{
			dushman[1][i].spriteE.setPosition(i * x_spacing + 50, 155 + y_spacing);
		}

		// Bottom row of dushman objects
		for (int i = 0; i < 5; i++)
		{
			dushman[2][i].spriteE.setPosition(i * x_spacing + 50, 50 + 2 * y_spacing + 120);
		}

		// Left column of dushman objects
		for (int i = 0; i < 3; i++)
		{
			dushman[i][0].spriteE.setPosition(40, (i + 1) * y_spacing + 50);
		}

		// Right column of dushman objects
		for (int i = 0; i < 3; i++)
		{
			dushman[i][4].spriteE.setPosition(40 + 4 * x_spacing, (i + 1) * y_spacing + 50);
		}

		// Center dushman object
		dushman[1][2].spriteE.setPosition(55 + 2 * x_spacing, 160 + y_spacing);
	}

	void setX()
	{
		int window_width = 780;
		int window_height = 780;
		int x_spacing = 80;
		int y_spacing = 60;
		for (int i = 0; i < 5; i++)
		{
			dushman[2][i].spriteE.setPosition(950, 950);
		}
		// Top-left to bottom-right diagonal of X
		for (int i = 0; i < 5; i++)
		{
			dushman[0][i].spriteE.setPosition((900 - 5 * x_spacing) / 2 + i * 1.25 * x_spacing - 50, (600 - 5 * y_spacing) / 2 + i * y_spacing - 50);
		}

		// Top-right to bottom-left diagonal of X
		for (int i = 0; i < 5; i++)
		{
			dushman[1][i].spriteE.setPosition((350 + x_spacing) / 2 + i * 1.25 * x_spacing, (700 - 5 * y_spacing) / 2 + (4 - i) * y_spacing - 100);
		}
	}

	void setDiamond()
	{
		for (int i = 0; i < 5; i++)
			dushman[0][i].spriteE.setPosition(340 + i * 60, i * 60);
		for (int i = 0; i < 5; i++)
			dushman[1][i].spriteE.setPosition(250 - i * 60, i * 60);

		dushman[2][0].spriteE.setPosition(130, 280);
		dushman[2][1].spriteE.setPosition(200, 350);
		dushman[2][2].spriteE.setPosition(520, 250);
		dushman[2][3].spriteE.setPosition(460, 310);
		dushman[2][4].spriteE.setPosition(950, 950);

		dushman[1][4].spriteE.setPosition(290, 350);
		dushman[0][4].spriteE.setPosition(360, 350);
	}

	void setTriangle()
	{
		int window_width = 780;
		int window_height = 780;
		int x_spacing = 50;
		int y_spacing = 80;

		// Bottom row of triangle
		for (int i = 0; i < 5; i++)
		{
			dushman[0][i].spriteE.setPosition((window_width - 700) / 2 + i * 150, window_height - 400);
		}

		// Right side of triangle
		for (int i = 0; i < 5; i++)
		{
			dushman[1][i].spriteE.setPosition((900 - 3 * x_spacing) / 2 + i * x_spacing, (400 - 5 * y_spacing) / 2 + i * y_spacing);
		}

		// Left side of triangle
		for (int i = 0; i < 5; i++)
		{
			dushman[2][i].spriteE.setPosition((350 + 5 * x_spacing) / 2 - i * x_spacing, (500 - 5.5 * y_spacing) / 2 + i * y_spacing);
		}
	}

	void setCircle()
	{
		int window_width = 780;
		int window_height = 780;
		int num_dushman = 15;
		float radius = std::min(window_width, window_height) * 0.25;
		float angle_step = 2.0 * 3.14 / num_dushman;
		float angle = 0.0;

		float y_offset = 150.0; // move up by 50 pixels

		for (int i = 0; i < num_dushman; i++)
		{
			angle = angle_step * i;
			float x = window_width / 2.0 + radius * std::cos(angle);
			float y = window_height - y_offset - (window_height / 2.0 + radius * std::sin(angle));
			dushman[i / 5][i % 5].spriteE.setPosition(x, y);
		}
	}

	void setHeart()

	{
		dushman[1][0].spriteE.setPosition(210, 50);
		dushman[1][1].spriteE.setPosition(340, 100);
		dushman[1][2].spriteE.setPosition(470, 50);
		dushman[1][3].spriteE.setPosition(160, 100);
		dushman[1][4].spriteE.setPosition(520, 100);

		dushman[0][0].spriteE.setPosition(270, 90);
		dushman[0][1].spriteE.setPosition(400, 90);
		dushman[0][2].spriteE.setPosition(190, 160);
		dushman[0][3].spriteE.setPosition(230, 230);
		dushman[0][4].spriteE.setPosition(280, 290);

		dushman[2][0].spriteE.setPosition(360, 330);
		dushman[2][1].spriteE.setPosition(400, 300);
		dushman[2][2].spriteE.setPosition(450, 260);
		dushman[2][3].spriteE.setPosition(490, 230);
		dushman[2][4].spriteE.setPosition(510, 190);
	}

	void fireBullet()
	{
		if (bsize > 0)
		{
			for (int i = 0; i < bsize; i++)
			{
				boss[i].spriteb.move(0, -.5);
			}
		}
	}

	void fireBomb()
	{
		if (bombSize > 0)
		{
			for (int i = 0; i < bombSize; i++)
			{
				dhamaka[i].spriteBomb.move(0, .05);
			}
		}
	}

	void destroyBullet(int indexToDelete)
	{
		Bullet *temp = boss;
		boss = new Bullet[bsize - 1];
		for (int i = 0, j = 0; i < bsize; i++)
		{
			if (i != indexToDelete)
			{
				boss[j] = temp[i];
				j++;
			}
		}
		if (temp)
			delete[] temp;
		bsize--;
	}

	void deleteDhamaka(int indexToDelete)
	{
		Bomb *oops = dhamaka;

		this->bombSize--;

		dhamaka = new Bomb[bombSize];

		int j = 0;
		for (int i = 0; i < bombSize + 1; i++)
		{
			if (i != indexToDelete)
			{
				dhamaka[j] = oops[i];
				j++;
			}
		}
		if (oops)
			delete[] oops;
	}

	void manageLives()
	{

		for (int i = 0; i < bombSize; i++)
		{
			if (dhamaka[i].spriteBomb.getPosition().y > 780)
				deleteDhamaka(i);

			else if ((dhamaka[i].spriteBomb.getGlobalBounds().intersects(p->sprite.getGlobalBounds())))
			{
				this->lives--;
				p->sprite.setPosition(340, 540);
				deleteDhamaka(i);
				return;
			}

			else
				continue;
		}

		for (int i = 0; i < invaderSize; i++)
		{
			if ((dushman[0][i].spriteE.getGlobalBounds().intersects(p->sprite.getGlobalBounds())))
			{
				this->lives--;
				p->sprite.setPosition(340, 540);
				return;
			}

			else if (dushman[1][i].spriteE.getGlobalBounds().intersects(p->sprite.getGlobalBounds()))
			{
				this->lives--;
				
				p->sprite.setPosition(340, 540);
				return;
			}

			else if (dushman[2][i].spriteE.getGlobalBounds().intersects(p->sprite.getGlobalBounds()))
			{
				this->lives--;
			
				p->sprite.setPosition(340, 540);
				return;
			}
		}

		if (showMonster)
			if (p->sprite.getGlobalBounds().intersects(pew->spriteL.getGlobalBounds()))
			{
				this->lives--;
				
				p->sprite.setPosition(650, 540);
			}

		if (showDragon)
			if (p->sprite.getGlobalBounds().intersects(burn->spriteF.getGlobalBounds()))
			{
				this->lives--;
				
				p->sprite.setPosition(650, 540);
			}

		if (lives == 0)
		{
			gameOver = true;
			p->sprite.setPosition(950, 950);
		}
	}

	void enemyLaser()
	{
		int t = rand() % 3;
		int v = rand() % 5;

		Bomb BAM(dushman[t][v].spriteE.getPosition().x + 10, dushman[t][v].spriteE.getPosition().y + 20);

		Bomb *temp = dhamaka;

		dhamaka = new Bomb[bombSize + 1];

		for (int i = 0; i < bombSize; i++)
		{
			dhamaka[i] = temp[i];
		}

		dhamaka[bombSize] = BAM;
		bombSize++;
		if (temp)
			delete[] temp;
	}

	void shootBullet()
	{
		Bullet goli(p->sprite.getPosition().x, p->sprite.getPosition().y);

		Bullet *temp = boss;
		boss = new Bullet[bsize + 1];

		boss[bsize] = goli;

		for (int i = 0; i < bsize; i++)
			boss[i] = temp[i];
		bsize++;
		if (temp)
			delete[] temp;
	}
};
