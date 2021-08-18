#include "myMain.h"
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include <iostream>
#include "Ennemy.h"
#include "PowerUp.h"



//liste des pointeurs vers les ennemis
std::vector<Ennemy*> ennemies;
//liste des pointeurs vers les powerups
std::vector<PowerUp*> powerups;



int myMain()
{

    //largeur de la fen�tre
    int width = 1000;
    //hauteur de la fen�tre
    int height = 600;

    sf::Clock timer;

    Hero frank(0, 0, 20);
    Ennemy knight1(100, 100, 20);
    Ennemy knight2(150, 100, 20);
    ennemies.push_back(&knight1);
    ennemies.push_back(&knight2);
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


        frank.handle_keyboard();

        //mise � jour des sprites : passage � la prochaine frame toutes les 250ms
        //TODO : g�n�raliser le update_sprite � tous les �l�ments
        if (timer.getElapsedTime().asMilliseconds() >= 250)
        {
            std::vector<Ennemy*>::iterator it;
            for (it = ennemies.begin(); it != ennemies.end(); ++it)
            {
                (*it)->update_sprite();
            }
            meat.update_sprite();
            timer.restart();
        }

        
        
        //affichage des sprites mis � jour
        //TODO : g�n�raliser le draw � tous les elements
        app.draw(frank.get_sprite());
        std::vector<PowerUp*>::iterator itp;
        for (itp = powerups.begin(); itp != powerups.end(); itp++){
            app.draw((*itp)->get_sprite());
        }
        std::vector<Ennemy*>::iterator it;

        for (it = ennemies.begin(); it != ennemies.end(); ++it)
        {
            app.draw((*it)->get_sprite());
        }
        app.display();
        app.clear();
    }

    return 0;
}