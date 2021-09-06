#include "TextureManager.h"
#include <iostream>

// The textures that are loaded
static std::map<std::string, sf::Texture*> textures;

// Get Texture by Name
sf::Texture* TextureManager::getTexture(std::string const name)
{

    // See if we have already loaded this texture
    if (textures.find(name) != textures.end()) {
        return textures[name];
    }
    else {
        std::cout << "Erreur - texture non trouvée : " << name << std::endl;
        return nullptr;
    }
}

// Assign a Texture a Name (for accessing via get) and path (to load from)
sf::Texture* TextureManager::loadTexture(std::string const name, std::string const path)
{
    // Haven't loaded it yet, time to create it
    auto texture = new sf::Texture();

    if (texture->loadFromFile(path))
    {
        textures.insert(std::make_pair(name, texture));

        // Push to vector the order in which items were loaded into map, for accessing via index.
        return texture;
    }
    else
    {
        // Could not load the file
        std::cout << "Erreur - échec du chargement : " << path << std::endl;
        return nullptr;
    }

}