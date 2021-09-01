#include "TextureManager.h"
#include <iostream>

TextureManager::TextureManager()
{
}

std::map<std::string, std::unique_ptr<sf::Texture>> TextureManager::textures;

// Get Texture by Name
sf::Texture* TextureManager::getTexture(std::string name)
{

    // See if we have already loaded this texture
    if (textures.find(name) != textures.end()) {
        return textures[name].get();
    }
    else {
        std::cout << "Erreur - texture non trouvée : " << name << std::endl;
        return NULL;
    }
}

// Assign a Texture a Name (for accessing via get) and path (to load from)
sf::Texture* TextureManager::loadTexture(std::string name, std::string path)
{
    // Haven't loaded it yet, time to create it
    std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();

    if (texture->loadFromFile(path))
    {
        textures.insert(std::make_pair(name, std::move(texture)));

        // Push to vector the order in which items were loaded into map, for accessing via index.
        return textures[name].get();
    }
    else
    {
        // Could not load the file
        std::cout << "Erreur - échec du chargement : " << path << std::endl;
        return NULL;
    }

}