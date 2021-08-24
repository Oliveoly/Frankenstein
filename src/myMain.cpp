#include "myMain.h"
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include <iostream>
#include "Ennemy.h"
#include "Walker.h"
#include "Firebreather.h"
#include "PowerUp.h"
#include "Fireball.h"

//TODO : g�n�raliser en une seule liste Elements
//liste des pointeurs vers les ennemis
std::vector<Ennemy*> ennemies;
//liste des pointeurs vers les powerups
std::vector<PowerUp*> powerups;
//liste des pointeurs vers les fireballs
std::vector<Fireball*> fireballs;

Hero* frank_ptr;


int myMain()
{

    //largeur de la fen�tre
    int width = 1000;
    //hauteur de la fen�tre
    int height = 600;

    std::vector<Ennemy*>::iterator ite;
    std::vector<PowerUp*>::iterator itp;
    std::vector<Fireball*>::iterator itx;

    sf::Clock timer;

    //�l�ments de jeu (h�ro, ennemis et power-ups)
    Hero frank(0, 0, 20);
    frank_ptr = &frank;
    Walker green1(100, 100, 20);
    Walker green2(150, 100, 20);
    Firebreather red1(200, 200, 20);
    ennemies.push_back(&green1);
    ennemies.push_back(&green2);
    ennemies.push_back(&red1);
    PowerUp meat(100, 50);
    PowerUp meat2(200, 50);
    powerups.push_back(&meat);
    powerups.push_back(&meat2);

    //textes
    sf::Font font;
    if (!font.loadFromFile("../../Ressources/Fonts/Minecraft.ttf"))
    {
        std::cout << "Erreur lors du chargement de Minecraft.ttf" << std::endl;
    }
    sf::Text text_HP;
    text_HP.setFont(font);
    text_HP.setCharacterSize(24);
    text_HP.setFillColor(sf::Color::White);

    sf::RenderWindow app(sf::VideoMode(width, height), "Frankenstein");
    app.setFramerateLimit(60);

    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                app.close();
            }
        }

        //gestion du comportement du joueur et des ennemis
        frank.handle_keyboard();
        for (ite = ennemies.begin(); ite != ennemies.end(); ++ite)
        {
            (*ite)->action();
        }
        for (itx = fireballs.begin(); itx != fireballs.end(); ++itx)
        {
            (*itx)->action();
        }

        //mise � jour des sprites : passage � la prochaine frame toutes les 250ms
        //TODO : g�n�raliser le update_sprite � tous les �l�ments
        frank.update_sprite();
        if (timer.getElapsedTime().asMilliseconds() >= 250)
        {
            for (ite = ennemies.begin(); ite != ennemies.end(); ++ite)
            {
                (*ite)->update_sprite();
            }
            for (itp = powerups.begin(); itp != powerups.end(); ++itp)
            {
                (*itp)->update_sprite();
            }
            for (itx = fireballs.begin(); itx != fireballs.end(); ++itx)
            {
                (*itx)->update_sprite();
            }
            //ball.update_sprite();
            timer.restart();
        }
        

        
        //affichage des sprites apr�s mise � jour de leur frame/position
        //TODO : g�n�raliser le draw � tous les elements
        app.draw(frank.get_sprite());

        for (itp = powerups.begin(); itp != powerups.end(); itp++){
            app.draw((*itp)->get_sprite());
        }
        for (ite = ennemies.begin(); ite != ennemies.end(); ++ite)
        {
            app.draw((*ite)->get_sprite());
        }
        for (itx = fireballs.begin(); itx != fireballs.end(); ++itx)
        {
            app.draw((*itx)->get_sprite());
        }

        //affichage des �l�ments textuels
        text_HP.setString(std::to_string(frank.get_currentHP()) + "/" + std::to_string(frank.get_maxHP()));
        app.draw(text_HP);

        app.display();
        app.clear();
    }

    return 0;
}