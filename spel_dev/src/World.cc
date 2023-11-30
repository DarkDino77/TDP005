#include <SFML/Graphics.hpp>
#include "standard.h"
#include "World.h"
#include <cmath>
#include "Player.h"

// TEMP v
#include <vector>
#include <memory>

const size_t width = 1920;
const size_t height = 1024;

void World::add_texture(std::string name, std::string filename)
{
    std::shared_ptr<sf::Texture> texture = std::shared_ptr<sf::Texture>(new sf::Texture());

    texture -> loadFromFile(filename);
    sprites[name] = texture;
}

void World::add_game_object(std::string const& name,  sf::Vector2f position)
{
    float pos_x{8.0f*sprite_scale + position.x*16.0f*sprite_scale};
    float pos_y{8.0f*sprite_scale + position.y*16.0f*sprite_scale};
    // TODO: cheack what  std::make_shared is
    std::shared_ptr<Game_Object> game_obj = std::shared_ptr<Game_Object>(new Game_Object({pos_x,pos_y}, *sprites[name]));


    game_objects.push_back(game_obj);
}

void World::add_player(sf::Vector2f position)
{
    float pos_x{8.0f*sprite_scale + position.x*16.0f*sprite_scale};
    float pos_y{8.0f*sprite_scale + position.y*16.0f*sprite_scale};
    std::shared_ptr<Game_Object> player_obj = std::shared_ptr<Game_Object>(new Player({pos_x,pos_y}, *sprites["player"]));

    game_objects.push_back(player_obj);

}


int main() {
    sf::RenderWindow window{sf::VideoMode{width, height}, "The Grand Arena"};
    window.setMouseCursorVisible(false);
    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(true);

    float sprite_scale{2.0f};

    // ==============================[ Background ]==============================
    sf::Texture background_texture;
    background_texture.loadFromFile("textures/background.png");

    sf::Vector2f background_texture_size{background_texture.getSize()};
    sf::Sprite background_sprite;
    background_sprite.setTexture(background_texture);

    // ==============================[ Cursor ]==============================
    sf::Texture mouse_cursor_texture;
    mouse_cursor_texture.loadFromFile("textures/crosshair.png");

    sf::Vector2f mouse_texture_size{mouse_cursor_texture.getSize()};
    sf::RectangleShape mouse_cursor{mouse_texture_size};
    mouse_cursor.setTexture(&mouse_cursor_texture);
    mouse_cursor.setOrigin(mouse_texture_size / 2.f);
    mouse_cursor.setScale(sprite_scale,sprite_scale);


    // ==============================[ TEST ]==============================
    World world{};

    world.add_texture("wall", "textures/wall.png");
    world.add_texture("crate", "textures/crate.png");
    world.add_texture("barrel", "textures/barrel.png");
    world.add_texture("player", "textures/player.png");

    world.add_game_object("wall",{1,1});
    world.add_game_object("wall",{4,1});
    world.add_game_object("wall",{7,1});
    world.add_game_object("wall",{10,1});
    world.add_game_object("wall",{2,4});
    world.add_game_object("wall",{5,4});
    world.add_game_object("wall",{8,4});
    world.add_game_object("wall",{11,4});
    world.add_game_object("wall",{28,14});
    world.add_game_object("wall",{25,14});
    world.add_game_object("wall",{22,14});
    world.add_game_object("wall",{19,14});
    world.add_game_object("crate", {10,3});
    world.add_game_object("crate",{9,14});
    world.add_game_object("crate",{28,12});
    world.add_game_object("barrel", {14, 7});
    world.add_game_object("wall",{15,7});

    world.add_game_object("wall",{27,1});
    world.add_game_object("wall",{28,1});
    world.add_game_object("wall",{28,2});

    world.add_game_object("wall",{1,13});
    world.add_game_object("wall",{1,14});
    world.add_game_object("wall",{2,14});

    world.add_player({20,20});

    // ==============================[ END TEST ]==============================
    double player_speed{1.0f};

    sf::Clock clock;

    // ==============================[ Game Loop ]==============================
    bool quit = false;
    while (!quit) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    quit = true;
                    break;
                default:
                    break;
            }
        }

        if (quit)
        {
            break;
        }

        auto delta_time = clock.restart();

        sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        mouse_cursor.setPosition(mouse_pos);

        window.clear();
        window.draw(background_sprite);

        // 1. Update
        for(std::shared_ptr<Game_Object> obj : world.game_objects)
        {
            obj->update(delta_time, world, window, obj);
        }

        // 2. Draw
        for(std::shared_ptr<Game_Object> obj : world.game_objects)
        {
            obj -> render(window);
        }
        window.draw(mouse_cursor);
        window.display();
    }

    return 0;
}