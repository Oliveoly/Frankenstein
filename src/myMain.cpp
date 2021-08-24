#include "myMain.h"
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include <iostream>
#include "Ennemy.h"
#include "Walker.h"
#include "Firebreather.h"
#include "PowerUp.h"
#include "Fireball.h"

//la liste des �l�ments du jeu : joueur, ennemis, power-ups, pi�ges...
std::vector<Element*> elements;
//la liste des �l�ments cr��s lors d'une it�ration sur la liste ci-dessus
//ils seront ajout�s � elements � la fin de l'it�ration, et new_elements est alors vid�e
std::vector<Element*> new_elements;
//largeur de la fen�tre
int width = 1000;
//hauteur de la fen�tre
int height = 600;

Hero* frank_ptr;

int myMain()
{
    

    std::vector<Element*>::iterator it;

    sf::Clock timer;

    //�l�ments de jeu (h�ro, ennemis et power-ups)
    Hero frank(0, 0, 20);
    frank_ptr = &frank;
    Walker green1(100, 100, 20);
    Walker green2(150, 100, 20);
    Firebreather red1(200, 200, 20);
    PowerUp meat(100, 50);
    PowerUp meat2(200, 50);

    elements.push_back(&green1);
    elements.push_back(&green2);
    elements.push_back(&red1);
    elements.push_back(&meat);
    elements.push_back(&meat2);

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
        for (it = elements.begin(); it != elements.end(); it++)
        {
            (*it)->action();
        }

        //ajout des nouveaux �l�ments cr��s lors de la boucle pr�c�dente � la liste elements
        elements.insert(elements.end(), new_elements.begin(), new_elements.end());
        new_elements.clear();

        //mise � jour des sprites : passage � la prochaine frame toutes les 250ms
        frank.update_sprite();
        if (timer.getElapsedTime().asMilliseconds() >= 250)
        {
            for (it = elements.begin(); it != elements.end(); it++)
            {
                (*it)->update_sprite();
            }
            timer.restart();
        }
        
        //affichage des sprites apr�s mise � jour de leur frame/position
        app.draw(frank.get_sprite());
        for (it = elements.begin(); it != elements.end(); it++)
        {
            app.draw((*it)->get_sprite());
        }

        //affichage des �l�ments textuels
        text_HP.setString(std::to_string(frank.get_currentHP()) + "/" + std::to_string(frank.get_maxHP()));
        app.draw(text_HP);

        app.display();
        app.clear();
    }

    return 0;
}