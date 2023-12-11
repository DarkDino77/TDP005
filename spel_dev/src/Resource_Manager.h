#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

class World;

class Resource_Manager {
public:
    Resource_Manager(World & world);
    sf::Texture& get_sprite(std::string const& category);
    sf::Font& get_font();
    sf::Sprite& get_background_sprite();
    sf::Texture& get_mouse_cursor_texture();
    void play_sound(std::string const& sound_name);

private:
    World& world;
    std::vector<std::shared_ptr<sf::Sound>> sound_queue{};
    std::map<std::string, std::vector<std::shared_ptr<sf::Texture>>> sprites{};
    std::map<std::string, std::vector<std::shared_ptr<sf::SoundBuffer>>> sound_buffers{};
    std::map<std::string, std::vector<std::shared_ptr<sf::Sound>>> sounds{};

    sf::Font font{};
    sf::Texture background_texture{};
    sf::Sprite background_sprite{};
    sf::Texture mouse_cursor_texture{};

    void load();
    void load_level_file(std::string const& filename);
    void load_font();
    void load_background();
    void load_cursor();
    void load_textures();
    void load_audio();
    void add_texture(std::string const& category,  std::string const& filename);
    void add_sound(std::string const& name,  std::string const& filename);
};


#endif