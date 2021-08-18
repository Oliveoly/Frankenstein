#include "myMain.h"
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include <iostream>
#include "Ennemy.h"
#include "PowerUp.h"



//largeur de la fenêtre
int width = 1000;
//hauteur de la fenêtre
int height = 600;
//liste des pointeurs vers les ennemis
std::vector<Ennemy*> ennemies;
//iterateur de la liste
std::vector<Ennemy*>::iterator it;
//liste des pointeurs vers les powerups
std::vector<PowerUp*> powerups;
//iterateur de la liste
std::vector<PowerUp*>::iterator itp;
sf::Clock timer;



int myMain()
{
    
    
    //ne peuvent être instancié avant la boucle main, sinon erreur fatale
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

        //mise à jour des sprites : passage à la prochaine frame toutes les 250ms
        //TODO : généraliser le update_sprite à tous les éléments
        if (timer.getElapsedTime().asMilliseconds() >= 250)
        {
            for (it = ennemies.begin(); it != ennemies.end(); ++it)
            {
                (*it)->update_sprite();
            }
            meat.update_sprite();
            timer.restart();
        }

        
        
        //affichage des sprites mis à jour
        //TODO : généraliser le draw à tous les elements
        app.draw(frank.get_sprite());
        for (itp = powerups.begin(); itp != powerups.end(); itp++){
            app.draw((*itp)->get_sprite());
        }
        
        for (it = ennemies.begin(); it != ennemies.end(); ++it)
        {
            app.draw((*it)->get_sprite());
        }
        app.display();
        app.clear();
    }

    return 0;
}