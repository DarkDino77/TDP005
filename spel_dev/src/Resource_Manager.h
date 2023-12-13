#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

class World;

/**
 * @class Resource_Manager
 * @brief Manages all textures and sounds.
 *
 * The Resource_Manager class handles the loading of textures and sounds.
 * It also provides an easy way of accessing these textures and playing the sounds.
 */
class Resource_Manager {
public:
    /**
     * @brief The constructor for the Resource_Manager object.
     */
    Resource_Manager();

    /**
     * @brief Used to get a sprite from the resource manager.
     *
     * @param category The sprite category of to get the texture from.
     * @return A reference to the target texture (if any).
     */
    sf::Texture& get_sprite(std::string const& category);

    /**
     * @brief Used to get the loaded font.
     * @return A reference to the font.
     */
    sf::Font& get_font();

    /**
     * @brief Used to access the background-sprite to draw in the world.
     * @return A reference to the background sprite.
     */
    sf::Sprite& get_background_sprite();

    /**
     * @brief Used to access the mouse cursor texture.
     * @return A reference to the texture of the mouse cursor.
     */
    sf::Texture& get_mouse_cursor_texture();

    /**
     * @brief Plays a sound in the given category.
     * @param sound_name The name of the sound category.
     */
    void play_sound(std::string const& sound_name);

private:
    /**
     * A map of shared pointers to all loaded sprites along with the category they belong to.
     */
    std::map<std::string, std::vector<std::shared_ptr<sf::Texture>>> sprites{};

    /**
     * A map of shared pointers to all available sound-buffers along with their name.
     */
    std::map<std::string, std::vector<std::shared_ptr<sf::SoundBuffer>>> sound_buffers{};

    /**
     * A map with shared pointers to all playable sounds along with their category name.
     */
    std::map<std::string, std::vector<std::shared_ptr<sf::Sound>>> sounds{};

    /**
     * The font used in the game
     */
    sf::Font font{};

    /**
     * The background texture of the level.
     */
    sf::Texture background_texture{};

    /**
     * The sprite of the background.
     */
    sf::Sprite background_sprite{};

    /**
     * The texture of the mouse cursor.
     */
    sf::Texture mouse_cursor_texture{};

    /**
     * Function to call all other load functions in the class.
     */
    void load();


    /**
     * Loads the font used in the game.
     */
    void load_font();

    /**
     * Loads the background texture used in the game.
     */
    void load_background();

    /**
     * Loads the mouse cursor texture used in the game.
     */
    void load_cursor();

    /**
     * Load all textures that are to be used in the game into the sprites map.
     */
    void load_textures();

    /**
     * Loads all audioclips that should be played during the game.
     */
    void load_audio();

    /**
     * Adds a texture to the sprites map.
     *
     * @param category The sprite category.
     * @param filename The filename of the texture.
     */
    void add_texture(std::string const& category,  std::string const& filename);

    /**
     * Adds a sound to the sound buffer map.
     * @param name The name of the sound.
     * @param filename The filename of the sound.
     */
    void add_sound(std::string const& name,  std::string const& filename);
};


#endif