#include <SFML/Graphics.hpp>
#include "standard.h"
#include "World.h"
#include <cmath>
#include "Player.h"
#include "Melee.h"

// TEMP v
#include <vector>
#include <memory>
#include <random>
#include <algorithm>

const size_t width = 1920;
const size_t height = 1024;



void World::add_texture(std::string name, std::string filename)
{
    auto texture = std::make_shared<sf::Texture>();
    texture->loadFromFile(filename);
    sprites[name] = texture;
}

void World::add_game_object(std::string const& name, sf::Vector2f position)
{
    float pos_x = 8.0f * sprite_scale + position.x * 16.0f * sprite_scale;
    float pos_y = 8.0f * sprite_scale + position.y * 16.0f * sprite_scale;

    auto game_obj = std::make_shared<Game_Object>(sf::Vector2f(pos_x, pos_y), *sprites[name]);
    game_objects.push_back(game_obj);
}

void World::add_player(sf::Vector2f position)
{
    float pos_x = 8.0f * sprite_scale + position.x * 16.0f * sprite_scale;
    float pos_y = 8.0f * sprite_scale + position.y * 16.0f * sprite_scale;

    auto player_obj = std::make_shared<Player>(sf::Vector2f(pos_x, pos_y), *sprites["player"], 1.0f);
    game_objects.push_back(player_obj);

    player = std::dynamic_pointer_cast<Player>(player_obj);
}

void World::add_melee_enemy(std::string const& name, sf::Vector2f position)
{
    float pos_x = 8.0f * sprite_scale + position.x * 16.0f * sprite_scale;
    float pos_y = 8.0f * sprite_scale + position.y * 16.0f * sprite_scale;

    auto enemy = std::make_shared<Melee>(sf::Vector2f(pos_x, pos_y), *sprites[name], 1.5f);
    game_objects.push_back(enemy);
}


std::shared_ptr<Player> World::get_player()
{
    return player;
}

void World::spawn_monsters()
{
    // TODO: Add a wave mechanic for the enemies, with a "wave-pot"

    std::vector<sf::Vector2f> spawn_positions{};

    std::random_device for_x;
    std::uniform_int_distribution<int> for_x_uniform(1,2);
    std::random_device for_y;
    std::uniform_int_distribution<int> for_y_uniform(1,31);
    while(spawn_positions.size() < 5)
    {
        int pos_x{(for_x_uniform(for_x)-1)*59};
        int pos_y{(for_y_uniform(for_y)-1)};

        sf::Vector2f pos{float(pos_x), float(pos_y)};
        auto it = std::find(spawn_positions.begin(), spawn_positions.end(), pos);
        if(it == spawn_positions.end())
        {
            spawn_positions.push_back(pos);
        }
    }

    for(sf::Vector2f pos : spawn_positions)
    {
        add_melee_enemy("melee1", pos);
    }

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
    world.add_texture("melee1", "textures/zombie1.png");
    world.add_texture("melee2", "textures/zombie2.png");
    world.add_texture("melee3", "textures/zombie3.png");
    world.add_texture("melee4", "textures/zombie4.png");

    /*for(int y{-1}; y <= 32; y++)
    {
        for(int x{-1}; x <= 60; x++)
        {
            if(y == -1 || y == 32)
            {
                world.add_game_object("wall",{float(x),float(y)});
            }
            else if(x == -1 || x == 60)
            {
                world.add_game_object("wall",{float(x),float(y)});
            }
        }
    }*/

    world.add_player({20,20});

    /*
    world.add_game_object("wall", {1,1});
    world.add_game_object("wall", {2,1});
    world.add_game_object("wall", {1,2});
    world.add_game_object("wall", {6,1});
    world.add_game_object("wall", {22,1});
    world.add_game_object("wall", {23,1});
    world.add_game_object("wall", {24,1});
    world.add_game_object("wall", {25,1});
    world.add_game_object("wall", {26,1});
    world.add_game_object("wall", {29,1});
    world.add_game_object("wall", {29,2});
    world.add_game_object("wall", {29,3});
    world.add_game_object("wall", {30,1});
    world.add_game_object("wall", {30,2});
    world.add_game_object("wall", {30,3});
    world.add_game_object("wall", {33,1});
    world.add_game_object("wall", {34,1});
    world.add_game_object("wall", {35,1});
    world.add_game_object("wall", {36,1});
    world.add_game_object("wall", {37,1});
    world.add_game_object("wall", {49,1});
    world.add_game_object("wall", {53,1});
    world.add_game_object("wall", {57,1});
    world.add_game_object("wall", {58,1});
    world.add_game_object("wall", {58,2});

    world.add_game_object("wall", {1,6});
    world.add_game_object("wall", {1,10});
    world.add_game_object("wall", {1,21});
    world.add_game_object("wall", {1,25});
    world.add_game_object("wall", {58,6});
    world.add_game_object("wall", {58,10});
    world.add_game_object("wall", {58,21});
    world.add_game_object("wall", {58,25});

    world.add_game_object("wall", {6,6});
    world.add_game_object("wall", {7,6});
    world.add_game_object("wall", {16,6});
    world.add_game_object("wall", {17,6});
    world.add_game_object("wall", {59-6,6});
    world.add_game_object("wall", {59-7,6});
    world.add_game_object("wall", {59-16,6});
    world.add_game_object("wall", {59-17,6});
    world.add_game_object("wall", {6,25});
    world.add_game_object("wall", {7,25});
    world.add_game_object("wall", {16,25});
    world.add_game_object("wall", {17,25});
    world.add_game_object("wall", {59-6,25});
    world.add_game_object("wall", {59-7,25});
    world.add_game_object("wall", {59-16,25});
    world.add_game_object("wall", {59-17,25});

    world.add_game_object("wall", {6,13});
    world.add_game_object("wall", {6,14});
    world.add_game_object("wall", {6,15});
    world.add_game_object("wall", {7,13});
    world.add_game_object("wall", {8,13});
    world.add_game_object("wall", {11,13});
    world.add_game_object("wall", {12,13});
    world.add_game_object("wall", {15,13});
    world.add_game_object("wall", {16,13});
    world.add_game_object("wall", {17,13});
    world.add_game_object("wall", {17,12});
    world.add_game_object("wall", {17,11});
    world.add_game_object("wall", {18,11});
    world.add_game_object("wall", {19,11});
    world.add_game_object("wall", {22,11});
    world.add_game_object("wall", {23,11});
    world.add_game_object("wall", {23,10});
    world.add_game_object("wall", {23,7});
    world.add_game_object("wall", {23,6});
    world.add_game_object("wall", {24,6});
    world.add_game_object("wall", {25,6});
    world.add_game_object("wall", {26,6});
    world.add_game_object("wall", {27,6});
    world.add_game_object("wall", {28,6});

    world.add_game_object("wall", {59-6,13});
    world.add_game_object("wall", {59-6,14});
    world.add_game_object("wall", {59-6,15});
    world.add_game_object("wall", {59-7,13});
    world.add_game_object("wall", {59-8,13});
    world.add_game_object("wall", {59-11,13});
    world.add_game_object("wall", {59-12,13});
    world.add_game_object("wall", {59-15,13});
    world.add_game_object("wall", {59-16,13});
    world.add_game_object("wall", {59-17,13});
    world.add_game_object("wall", {59-17,12});
    world.add_game_object("wall", {59-17,11});
    world.add_game_object("wall", {59-18,11});
    world.add_game_object("wall", {59-19,11});
    world.add_game_object("wall", {59-22,11});
    world.add_game_object("wall", {59-23,11});
    world.add_game_object("wall", {59-23,10});
    world.add_game_object("wall", {59-23,7});
    world.add_game_object("wall", {59-23,6});
    world.add_game_object("wall", {59-24,6});
    world.add_game_object("wall", {59-25,6});
    world.add_game_object("wall", {59-26,6});
    world.add_game_object("wall", {59-27,6});
    world.add_game_object("wall", {59-28,6});

    world.add_game_object("wall", {6,31-13});
    world.add_game_object("wall", {6,31-14});
    world.add_game_object("wall", {6,31-15});
    world.add_game_object("wall", {7,31-13});
    world.add_game_object("wall", {8,31-13});
    world.add_game_object("wall", {11,31-13});
    world.add_game_object("wall", {12,31-13});
    world.add_game_object("wall", {15,31-13});
    world.add_game_object("wall", {16,31-13});
    world.add_game_object("wall", {17,31-13});
    world.add_game_object("wall", {17,31-12});
    world.add_game_object("wall", {17,31-11});
    world.add_game_object("wall", {18,31-11});
    world.add_game_object("wall", {19,31-11});
    world.add_game_object("wall", {22,31-11});
    world.add_game_object("wall", {23,31-11});
    world.add_game_object("wall", {23,31-10});
    world.add_game_object("wall", {23,31-7});
    world.add_game_object("wall", {23,31-6});
    world.add_game_object("wall", {24,31-6});
    world.add_game_object("wall", {25,31-6});
    world.add_game_object("wall", {26,31-6});
    world.add_game_object("wall", {27,31-6});
    world.add_game_object("wall", {28,31-6});

    world.add_game_object("wall", {59-6,31-13});
    world.add_game_object("wall", {59-6,31-14});
    world.add_game_object("wall", {59-6,31-15});
    world.add_game_object("wall", {59-7,31-13});
    world.add_game_object("wall", {59-8,31-13});
    world.add_game_object("wall", {59-11,31-13});
    world.add_game_object("wall", {59-12,31-13});
    world.add_game_object("wall", {59-15,31-13});
    world.add_game_object("wall", {59-16,31-13});
    world.add_game_object("wall", {59-17,31-13});
    world.add_game_object("wall", {59-17,31-12});
    world.add_game_object("wall", {59-17,31-11});
    world.add_game_object("wall", {59-18,31-11});
    world.add_game_object("wall", {59-19,31-11});
    world.add_game_object("wall", {59-22,31-11});
    world.add_game_object("wall", {59-23,31-11});
    world.add_game_object("wall", {59-23,31-10});
    world.add_game_object("wall", {59-23,31-7});
    world.add_game_object("wall", {59-23,31-6});
    world.add_game_object("wall", {59-24,31-6});
    world.add_game_object("wall", {59-25,31-6});
    world.add_game_object("wall", {59-26,31-6});
    world.add_game_object("wall", {59-27,31-6});
    world.add_game_object("wall", {59-28,31-6});


    world.add_game_object("wall", {1,31-1});
    world.add_game_object("wall", {2,31-1});
    world.add_game_object("wall", {1,31-2});
    world.add_game_object("wall", {6,31-1});
    world.add_game_object("wall", {22,31-1});
    world.add_game_object("wall", {23,31-1});
    world.add_game_object("wall", {24,31-1});
    world.add_game_object("wall", {25,31-1});
    world.add_game_object("wall", {26,31-1});
    world.add_game_object("wall", {29,31-1});
    world.add_game_object("wall", {29,31-2});
    world.add_game_object("wall", {29,31-3});
    world.add_game_object("wall", {30,31-1});
    world.add_game_object("wall", {30,31-2});
    world.add_game_object("wall", {30,31-3});
    world.add_game_object("wall", {33,31-1});
    world.add_game_object("wall", {34,31-1});
    world.add_game_object("wall", {35,31-1});
    world.add_game_object("wall", {36,31-1});
    world.add_game_object("wall", {37,31-1});
    world.add_game_object("wall", {49,31-1});
    world.add_game_object("wall", {53,31-1});
    world.add_game_object("wall", {57,31-1});
    world.add_game_object("wall", {58,31-1});
    world.add_game_object("wall", {58,31-2});

    world.add_game_object("barrel", {1,7});
    world.add_game_object("barrel", {24,3});
    world.add_game_object("barrel", {49,2});
    world.add_game_object("barrel", {28,15});
    world.add_game_object("barrel", {13,22});
    world.add_game_object("barrel", {43,19});
    world.add_game_object("barrel", {42,26});

    world.add_game_object("crate", {6,7});
    world.add_game_object("crate", {9,15});
    world.add_game_object("crate", {6,24});
    world.add_game_object("crate", {53,7});
    world.add_game_object("crate", {50,15});
    world.add_game_object("crate", {53,24});*/


    // ==============================[ END TEST ]==============================
    double player_speed{1.0f};

    sf::Clock clock;
    sf::Clock spawn_clock;
    //world.spawn_monsters();
    //world.add_melee_enemy("melee1", {0,0});

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
            for(std::shared_ptr<Game_Object> ptr : world.game_objects)
            {
                ptr = nullptr;
            }
            break;
        }
        if(spawn_clock.getElapsedTime().asSeconds() > 30)
        {
            spawn_clock.restart();
            world.spawn_monsters();
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
           /* std::shared_ptr<Movable> target_obj{std::dynamic_pointer_cast<Movable>(obj)};
            if(target_obj != nullptr)
            {
                window.draw(target_obj->collision_shape);
            }*/
            obj -> render(window);
        }
        window.draw(mouse_cursor);
        window.display();
    }

    return 0;
}