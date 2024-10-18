#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include "game.h"
using namespace std;
using namespace sf;

const char title1[] = "MENU";

class Menu
{
public:
    Texture menuBackground;
    bool showInstructions = false;
    Sprite menuBg;
    bool showScores = false;
    string *score;
    string *name;
    int size = 0;
    fstream file;

    Menu()
    {

        string playerName;

        file.open("score.txt", ios::in | ios::app);

        while (!file.eof())
        {

            getline(file, playerName);
            size++;
        }
        file.close();
        file.open("score.txt", ios::in);

        int index = 0;
        name = new string[size];
        score = new string[size];

        while (index < size)
        {
            getline(file, name[index], ',');
            getline(file, score[index]);
            index++;
        }
        file.close();

        menuBackground.loadFromFile("img/tired5.jpg");
        menuBg.setTexture(menuBackground);
        menuBg.setScale(0.9, 1.15);
    }

    void add(string naam, string number)
    {

        string *tempName = new string[size + 1];
        string *tempScore = new string[size + 1];

        for (int i = 0; i < size; i++)
        {
            tempName[i] = name[i];
            tempScore[i] = score[i];
        }
        tempName[size] = naam;
        tempScore[size] = number;
        name = tempName;
        score = tempScore;
        size++;

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size - i - 1; j++)
            {
                if (score[j] < score[j + 1])
                {
                    string tempName = name[j];
                    name[j] = name[j + 1];
                    name[j + 1] = tempName;
                    string tempScore = score[j];
                    score[j] = score[j + 1];
                    score[j + 1] = tempScore;
                }
            }
        }

        file.open("score.txt", ios::out);
        for (int i = 0; i < size; i++)
        {
            file << name[i] << "," << score[i];
            if (i != size - 1)
                file << endl;
        }
        file.close();
    }

    void display_menu(bool &end)
    {
        RenderWindow menu(VideoMode(780, 780), title1);
        Music intro;
        intro.openFromFile("audio/intro.wav");
        intro.setLoop(true);
        intro.setVolume(50);
        intro.play();

        while (menu.isOpen())
        {

            Event e;
            while (menu.pollEvent(e))
            {
                if (e.type == Event::Closed)
                {
                    end = 1;
                    menu.close();
                    intro.stop();
                }

                if (e.type == Event::KeyPressed)
                {
                    if (e.key.code == Keyboard::Escape)
                    {
                        end = 1;
                        menu.close();
                        intro.stop();
                    }

                    if (e.key.code == Keyboard::Enter) // if enter key is pressed on game window
                        showInstructions = false;

                    if (e.key.code == Keyboard::R)
                        showScores = false;
                }

                if (e.type == Event::MouseButtonPressed)
                    if (e.mouseButton.button == Mouse::Left)
                    {

                        if (Mouse::getPosition(menu).x > 350 && Mouse::getPosition(menu).x < 450 && Mouse::getPosition(menu).y > 250 && Mouse::getPosition(menu).y < 300) // area for start, if clicked in this part
                        {
                            end = 0;
                            menu.close();
                            intro.stop();
                        }

                        if (Mouse::getPosition(menu).x > 350 && Mouse::getPosition(menu).x < 500 && Mouse::getPosition(menu).y > 350 && Mouse::getPosition(menu).y < 400) // if clicked in this area,
                            showInstructions = true;                                                                                                                      // instruction manual will open

                        if (Mouse::getPosition(menu).x > 350 && Mouse::getPosition(menu).x < 400 && Mouse::getPosition(menu).y > 470 && Mouse::getPosition(menu).y < 530)
                        {
                            end = 1;
                            exit(0);
                            intro.stop();
                        }

                        if (Mouse::getPosition(menu).x > 200 && Mouse::getPosition(menu).x < 450 && Mouse::getPosition(menu).y > 540 && Mouse::getPosition(menu).y < 610)
                        {
                            showScores = true;
                        }
                    }
            }

            sf::Font font;
            font.loadFromFile("font/BF.ttf");

            if (showScores == true)
            {
                menu.clear(Color::Black);
                menu.draw(menuBg);

                sf::Text title2;
                title2.setFont(font);
                title2.setString("HIGH SCORES");
                title2.setCharacterSize(50);
                title2.setPosition(155, 100);
                title2.setFillColor(Color::Black);
                menu.draw(title2);

                title2.setFillColor(Color::Magenta);
                title2.setPosition(160, 100);
                menu.draw(title2);

                sf::Text plyr1;
                plyr1.setFont(font);
                plyr1.setString(name[0]);
                plyr1.setCharacterSize(30);
                plyr1.setFillColor(Color::Black);
                plyr1.setPosition(250, 250);
                menu.draw(plyr1);

                plyr1.setPosition(254, 251);
                plyr1.setFillColor(Color::White);
                menu.draw(plyr1);

                sf::Text scr1;
                scr1.setFont(font);
                scr1.setString(score[0]);
                scr1.setCharacterSize(30);
                scr1.setFillColor(Color::Black);
                scr1.setPosition(450, 250);
                menu.draw(scr1);

                scr1.setPosition(454, 251);
                scr1.setFillColor(Color::White);
                menu.draw(scr1);

                sf::Text plyr2;
                plyr2.setFont(font);
                plyr2.setString(name[1]);
                plyr2.setCharacterSize(30);
                plyr2.setFillColor(Color::Black);
                plyr2.setPosition(250, 350);
                menu.draw(plyr2);

                plyr2.setPosition(254, 351);
                plyr2.setFillColor(Color::White);
                menu.draw(plyr2);

                sf::Text scr2;
                scr2.setFont(font);
                scr2.setString(score[1]);
                scr2.setCharacterSize(30);
                scr2.setFillColor(Color::Black);
                scr2.setPosition(450, 350);
                menu.draw(scr2);

                scr2.setPosition(454, 351);
                scr2.setFillColor(Color::White);
                menu.draw(scr2);

                sf::Text plyr3;
                plyr3.setFont(font);
                plyr3.setString(name[2]);
                plyr3.setCharacterSize(30);
                plyr3.setFillColor(Color::Black);
                plyr3.setPosition(250, 450);
                menu.draw(plyr3);

                plyr3.setPosition(254, 451);
                plyr3.setFillColor(Color::White);
                menu.draw(plyr3);

                sf::Text scr3;
                scr3.setFont(font);
                scr3.setString(score[2]);
                scr3.setCharacterSize(30);
                scr3.setFillColor(Color::Black);
                scr3.setPosition(450, 450);
                menu.draw(scr3);

                scr3.setPosition(454, 451);
                scr3.setFillColor(Color::White);
                menu.draw(scr3);

                menu.display();
            }

            else
            {

                if (showInstructions == true) // displaying instructions in menu
                {
                    menu.clear(Color::Black);
                    menu.draw(menuBg);

                    sf::Text instructions;
                    instructions.setFont(font);
                    instructions.setString(" Right Key = Move right \n\n\n Left Key = Move left \n\n\n Up Key = Move up \n\n\n Down Key = Move down \n\n\n A/Q/W/S = Rotate ship \n\n\n Escape Key = Exit Game \n\n\n Space Key = Pause Game \n\n\n Press ENTER to return to menu");
                    instructions.setCharacterSize(24);

                    instructions.setFillColor(Color::Black); // for text background
                    instructions.setPosition(10, 0);
                    menu.draw(instructions);

                    instructions.setFillColor(Color::White); // text colour and format
                    instructions.setPosition(13, 1);
                    menu.draw(instructions);
                    menu.display();
                }

                else
                {
                    menu.clear(Color::Black);
                    menu.draw(menuBg);

                    sf::Text gametitle;
                    gametitle.setFont(font);
                    gametitle.setString("SPACE SHOOTER");
                    gametitle.setCharacterSize(50);
                    gametitle.setPosition(80, 100);
                    gametitle.setFillColor(Color::Black);
                    menu.draw(gametitle);

                    gametitle.setFillColor(Color::Magenta);
                    gametitle.setPosition(85, 100);
                    menu.draw(gametitle);

                    sf::Text playgame;
                    playgame.setFont(font);
                    playgame.setString("START");
                    playgame.setCharacterSize(30);
                    playgame.setFillColor(Color::Black);
                    playgame.setPosition(320, 250);
                    menu.draw(playgame);

                    playgame.setPosition(324, 251);
                    playgame.setFillColor(Color::White);
                    menu.draw(playgame);

                    sf::Text Instructions;
                    Instructions.setFont(font);
                    Instructions.setString("HELP");
                    Instructions.setCharacterSize(30);
                    Instructions.setFillColor(Color::Black);
                    Instructions.setPosition(330, 350);
                    menu.draw(Instructions);

                    Instructions.setPosition(334, 351);
                    Instructions.setFillColor(Color::White);
                    menu.draw(Instructions);

                    sf::Text exitgame;
                    exitgame.setFont(font);
                    exitgame.setString("EXIT");
                    exitgame.setCharacterSize(30);
                    exitgame.setFillColor(Color::Black);
                    exitgame.setPosition(335, 450);
                    menu.draw(exitgame);

                    exitgame.setPosition(339, 451);
                    exitgame.setFillColor(Color::White);
                    menu.draw(exitgame);

                    sf::Text highscores;
                    highscores.setFont(font);
                    highscores.setString("HIGH SCORES");
                    highscores.setCharacterSize(30);
                    highscores.setFillColor(Color::Black);
                    highscores.setPosition(240, 550);
                    menu.draw(highscores);

                    highscores.setPosition(244, 551);
                    highscores.setFillColor(Color::White);
                    menu.draw(highscores);

                    if (Mouse::getPosition(menu).x > 350 && Mouse::getPosition(menu).x < 450 && Mouse::getPosition(menu).y > 250 && Mouse::getPosition(menu).y < 300)
                    {
                        playgame.setFillColor(Color::Cyan);
                    }

                    if (Mouse::getPosition(menu).x > 350 && Mouse::getPosition(menu).x < 450 && Mouse::getPosition(menu).y > 350 && Mouse::getPosition(menu).y < 400)
                    {
                        Instructions.setFillColor(Color::Cyan);
                    }

                    if (Mouse::getPosition(menu).x > 350 && Mouse::getPosition(menu).x < 400 && Mouse::getPosition(menu).y > 470 && Mouse::getPosition(menu).y < 530)
                    {
                        exitgame.setFillColor(Color::Cyan);
                    }

                    if (Mouse::getPosition(menu).x > 200 && Mouse::getPosition(menu).x < 450 && Mouse::getPosition(menu).y > 540 && Mouse::getPosition(menu).y < 610)
                    {
                        highscores.setFillColor(Color::Cyan);
                    }

                    menu.draw(playgame);
                    menu.draw(Instructions);
                    menu.draw(exitgame);
                    menu.draw(highscores);

                    menu.display();
                }
            }
        }
    }
};
