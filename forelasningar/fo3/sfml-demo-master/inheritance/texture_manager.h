#pragma once
#include "common.h"
#include <map>

/**
 * This is a class that keeps track of loaded textures, so that we don't load
 * more than one instance of each texture.
 *
 * This is what is known as a singleton class.
 */
class Texture_Manager {
public:
    /**
     * Get a texture. This might cause the texture to be loaded, or it might
     * return a texture that was loaded previously.
     */
    static sf::Texture *get(const string &name);

private:
    /**
     * Private constructor. Only we can create instances.
     */
    Texture_Manager() = default;

    /**
     * The one and only instance.
     */
    static Texture_Manager instance;

    /**
     * Keep track of loaded textures.
     */
    std::map<string, std::unique_ptr<sf::Texture>> textures;
};
