#include "myMain.h"
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include <iostream>
#include "Ennemy.h"
#include "Walker.h"
#include "Firebreather.h"
#include "PowerUp.h"
#include "Freezer.h"
#include "TextureManager.h"


//la liste des �l�ments du jeu : joueur, ennemis, power-ups, pi�ges...
std::vector<std::unique_ptr<Element>> elements;
//la liste des �l�ments cr��s lors d'une it�ration sur la liste ci-dessus
//ils seront ajout�s � elements � la fin de l'it�ration, et new_elements est alors vid�e
std::vector<std::unique_ptr<Element>> new_elements;
//largeur de la fen�tre
int width = 1000;
//hauteur de la fen�tre
int height = 600;

int myMain()
{
    std::vector<std::unique_ptr<Element>>::iterator it;

    sf::Clock timer;

    //chargement des textures
    TextureManager::loadTexture("puddle", "../../Ressources/puddle.png");
    TextureManager::loadTexture("fireball", "../../Ressources/fireball.png");
    TextureManager::loadTexture("meat", "../../Ressources/meat.png");
    TextureManager::loadTexture("frozen_meat", "../../Ressources/frozen_meat.png");
    TextureManager::loadTexture("fire_meat", "../../Ressources/fire_meat.png");
    TextureManager::loadTexture("firebreather", "../../Ressources/zombieRed.png");
    TextureManager::loadTexture("freezer", "../../Ressources/zombieBlue.png");
    TextureManager::loadTexture("hero", "../../Ressources/scientist.png");
    TextureManager::loadTexture("iceball", "../../Ressources/iceball.png");
    TextureManager::loadTexture("walker", "../../Ressources/zombie.png");

    //�l�ments de jeu (h�ro, ennemis et power-ups)
    std::unique_ptr<Hero> frank = std::make_unique<Hero>(500, 500, 20);
    Hero const* frank_ptr = frank.get();
    std::unique_ptr<Walker> green1 = std::make_unique<Walker>(100, 100, 20);
    std::unique_ptr<Walker> green2 = std::make_unique<Walker>(150, 100, 20);
    std::unique_ptr<Firebreather> red1 = std::make_unique<Firebreather>(200, 200, 20);
    std::unique_ptr<PowerUp> meat1 = std::make_unique<PowerUp>(100, 50, "speed");
    std::unique_ptr<PowerUp> meat2 = std::make_unique<PowerUp>(200, 50, "speed");
    std::unique_ptr<Freezer> blue1 = std::make_unique<Freezer>(100, 50, 20);
    
    // /!\ on d�place les pointeurs dans le liste : ils ne sont plus accessibles individuellement !
    elements.push_back(std::move(frank));
    elements.push_back(std::move(green1));
    elements.push_back(std::move(green2));
    elements.push_back(std::move(red1));
    elements.push_back(std::move(meat1));
    elements.push_back(std::move(meat2));
    elements.push_back(std::move(blue1));

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
        for (it = elements.begin(); it != elements.end(); it++)
        {
            (*it)->action();
        }

        elements.erase(std::remove_if(elements.begin(), elements.end(), [](const std::unique_ptr<Element> &e) {return e->get_to_destroy(); }), elements.end());

        //ajout des nouveaux �l�ments cr��s lors de la boucle pr�c�dente � la liste elements
        std::move(new_elements.begin(), new_elements.end(), std::back_inserter(elements));
        new_elements.clear();

        //mise � jour des sprites : passage � la prochaine frame toutes les 250ms
        if (timer.getElapsedTime().asMilliseconds() >= 250)
        {
            //frank->update_sprite();
            for (it = elements.begin(); it != elements.end(); it++)
            {
                (*it)->update_sprite();
            }
            timer.restart();
        }
        
        //affichage des sprites apr�s mise � jour de leur frame/position
        for (it = elements.begin(); it != elements.end(); it++)
        {
            app.draw((*it)->get_sprite());
        }

        //affichage des �l�ments textuels
        text_HP.setString(std::to_string(std::max(frank_ptr->get_currentHP(), 0)) + "/" + std::to_string(frank_ptr->get_maxHP()));
        text_danger.setString("monstrification : " + std::to_string(frank_ptr->get_modif()) + " / 10");
        if ( (frank_ptr->get_currentHP() <=0) || (frank_ptr->get_modif() >= 10) ) {
            text_GameOver.setString("GAME OVER");
        }
        app.draw(text_HP);
        app.draw(text_danger);
        app.draw(text_GameOver);

        app.display();
        app.clear();
    }

    return 0;
}