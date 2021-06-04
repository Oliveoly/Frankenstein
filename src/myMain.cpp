#include "myMain.h"
#include <SFML/Graphics.hpp>
#include "Character.h"
#include <iostream>
#include "Ennemy.h"


//dimensions de la fenêtre
int width = 1000;
int height = 600;


int myMain()
{
    //ne peuvent être instancié avant la boucle main, sinon erreur fatale
    Character frank(0, 0, 20);
    Ennemy knight(100, 100, 20);

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
        knight.update_sprite();
        
        sf::CircleShape cercle = frank.get_shape();
        cercle.setFillColor(sf::Color::Red); //l'attribut color n'est pas transmis -> pas vraiment un attribut de la classe ?
        app.draw(cercle);
        app.draw(frank.get_sprite());
        app.draw(knight.get_sprite());
        app.display();
        app.clear();
    }

    return 0;
}