#include "myMain.h"
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include <iostream>
#include "Ennemy.h"
#include "Walker.h"
#include "Firebreather.h"
#include "PowerUp.h"
#include "Freezer.h"

//la liste des éléments du jeu : joueur, ennemis, power-ups, pièges...
std::vector<Element*> elements;
//la liste des éléments créés lors d'une itération sur la liste ci-dessus
//ils seront ajoutés à elements à la fin de l'itération, et new_elements est alors vidée
std::vector<Element*> new_elements;
//largeur de la fenêtre
int width = 1000;
//hauteur de la fenêtre
int height = 600;

Hero* frank_ptr;

int myMain()
{
    std::vector<Element*>::iterator it;

    sf::Clock timer;

    //éléments de jeu (héro, ennemis et power-ups)
    Hero frank(0, 0, 20);
    frank_ptr = &frank;
    Walker green1(100, 100, 20);
    Walker green2(150, 100, 20);
    Firebreather red1(200, 200, 20);
    PowerUp meat(100, 50);
    PowerUp meat2(200, 50);
    Freezer blue1(100, 300, 20);

    elements.push_back(&green1);
    elements.push_back(&green2);
    elements.push_back(&red1);
    elements.push_back(&meat);
    elements.push_back(&meat2);
    elements.push_back(&blue1);

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
    sf::Text text_danger;
    text_danger.setFont(font);
    text_danger.setCharacterSize(24);
    text_danger.setFillColor(sf::Color::Red);
    text_danger.setPosition(700, 0);
    sf::Text text_GameOver;
    text_GameOver.setFont(font);
    text_GameOver.setCharacterSize(50);
    text_GameOver.setFillColor(sf::Color::White);
    text_GameOver.setPosition(350, 350);
    
    

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

        //ajout des nouveaux éléments créés lors de la boucle précédente à la liste elements
        elements.insert(elements.end(), new_elements.begin(), new_elements.end());
        new_elements.clear();

        //mise à jour des sprites : passage à la prochaine frame toutes les 250ms
        if (timer.getElapsedTime().asMilliseconds() >= 250)
        {
            frank.update_sprite();
            for (it = elements.begin(); it != elements.end(); it++)
            {
                (*it)->update_sprite();
            }
            timer.restart();
        }
        
        //affichage des sprites après mise à jour de leur frame/position
        app.draw(frank.get_sprite());
        for (it = elements.begin(); it != elements.end(); it++)
        {
            app.draw((*it)->get_sprite());
        }

        //affichage des éléments textuels
        text_HP.setString(std::to_string(std::max(frank.get_currentHP(), 0)) + "/" + std::to_string(frank.get_maxHP()));
        text_danger.setString("monstrification : " + std::to_string(frank.get_modif()) + " / 10");
        if (frank.get_currentHP()<=0) {
            text_GameOver.setString("Vous etes mort!");
        }
        app.draw(text_HP);
        app.draw(text_danger);
        app.draw(text_GameOver);

        app.display();
        app.clear();
    }

    return 0;
}