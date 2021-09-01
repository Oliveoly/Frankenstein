#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class TextureManager
{
    // The textures that are loaded
    static std::map<std::string, std::unique_ptr<sf::Texture>> textures;

    // Constructor that is not used
    TextureManager();
public:
    // Get texutre by name specified in loadTexture, or return null
    static sf::Texture* getTexture(std::string name);

    // Loads the texture and returns a pointer to it
    // If it is already loaded, this function just returns it
    // If it cannot find the file, returns NULL
    static sf::Texture* loadTexture(std::string name, std::string path);
};

#endif