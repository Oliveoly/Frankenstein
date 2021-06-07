#include "myMain.h"
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include <iostream>
#include "Ennemy.h"
#include <list>
#include "PowerUp.h"


//largeur de la fenêtre
int width = 1000;
//hauteur de la fenêtre
int height = 600;
//liste des pointeurs vers les ennemis
std::list<Ennemy*> ennemies;
//iterateur de la liste
std::list<Ennemy*>::iterator it;
//liste des pointeurs vers les powerups
std::list<PowerUp*> powerups;
//iterateur de la liste
std::list<PowerUp*>::iterator itp;


int myMain()
{
    //ne peuvent être instancié avant la boucle main, sinon erreur fatale
    Hero frank(0, 0, 20);
    Ennemy knight1(100, 100, 20);
    Ennemy knight2(150, 100, 20);
    ennemies.push_back(&knight1);
    ennemies.push_back(&knight2);
    PowerUp meat(100, 50);
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
        for (it = ennemies.begin(); it != ennemies.end(); ++it)
        {
            (*it)->update_sprite();
        }
        meat.update_sprite();
        
        
        app.draw(frank.get_sprite());
        app.draw(meat.get_sprite());
        for (it = ennemies.begin(); it != ennemies.end(); ++it)
        {
            app.draw((*it)->get_sprite());
        }
        app.display();
        app.clear();
    }

    return 0;
}