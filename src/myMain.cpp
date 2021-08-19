#include "myMain.h"
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include <iostream>
#include "Ennemy.h"
#include "Walker.h"
#include "Firebreather.h"
#include "PowerUp.h"

//liste des pointeurs vers les ennemis
std::vector<Ennemy*> ennemies;
//liste des pointeurs vers les powerups
std::vector<PowerUp*> powerups;
Hero* frank_ptr;


int myMain()
{

    //largeur de la fen�tre
    int width = 1000;
    //hauteur de la fen�tre
    int height = 600;

    std::vector<Ennemy*>::iterator ite;
    std::vector<PowerUp*>::iterator itp;

    sf::Clock timer;

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

        //mise � jour des sprites : passage � la prochaine frame toutes les 250ms
        //TODO : g�n�raliser le update_sprite � tous les �l�ments
        frank.update_sprite();
        if (timer.getElapsedTime().asMilliseconds() >= 250)
        {
            for (ite = ennemies.begin(); ite != ennemies.end(); ++ite)
            {
                (*ite)->update_sprite();
            }
            meat.update_sprite();
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

        app.display();
        app.clear();
    }

    return 0;
}