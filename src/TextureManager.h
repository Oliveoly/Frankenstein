#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class TextureManager
{
public:
    // Get texutre by name specified in loadTexture, or return null
    static sf::Texture* getTexture(std::string const name);

    // Loads the texture and returns a pointer to it
    // If it is already loaded, this function just returns it
    // If it cannot find the file, returns NULL
    static sf::Texture* loadTexture(std::string const name, std::string const path);
};

#endif