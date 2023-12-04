#include <SFML/Graphics.hpp>
#include "standard.h"
#include "World.h"
#include "Player.h"
#include "Melee.h"
#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include <fstream>
#include <iterator>

const size_t window_width = 1920;
const size_t window_height = 1024;
const int font_size{40};

sf::Vector2f grid_to_coord(sf::Vector2f const& grid_coordinate)
{
    float sprite_scale{2.0f};
    float pos_x = 8.0f * sprite_scale + grid_coordinate.x * 16.0f * sprite_scale;
    float pos_y = 8.0f * sprite_scale + grid_coordinate.y * 16.0f * sprite_scale;
    return {pos_x, pos_y};
}

void World::add_texture(std::string const& name, std::string const& filename)
{
    auto texture = std::make_shared<sf::Texture>();
    if(!texture->loadFromFile(filename))
    {
        std::cerr << "Could not find image with name '" << filename << "'." << std::endl;
    }
    else
    {
        sprites[name] = texture;
    }
}

void World::add_game_object(std::string const& name, sf::Vector2f const& position)
{
    auto game_obj = std::make_shared<Game_Object>(grid_to_coord(position),
                                                  *sprites[name]);
    game_objects.push_back(game_obj);
}

void World::add_player(sf::Vector2f const& position, sf::Window const& window)
{
    auto player_obj = std::make_shared<Player>(grid_to_coord(position),
                                               *sprites["player"], 1.0f, 100, window);
    game_objects.push_back(player_obj);
    player = std::dynamic_pointer_cast<Player>(player_obj);
}

void World::add_melee_enemy(std::string const& name, sf::Vector2f const& position)
{
    auto enemy = std::make_shared<Melee>(grid_to_coord(position),
                                         *sprites[name], 0.3f, 20, 10);
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
    std::vector<std::string> enemy_sprites{"melee1","melee2", "melee3", "melee4", "melee5", "melee6", "melee7"};

    std::random_device rd;
    std::uniform_int_distribution<int> for_x_uniform(1,2);
    std::uniform_int_distribution<int> for_y_uniform(1,31);
    std::uniform_int_distribution<int> sprite_randomizer(1,int(enemy_sprites.size()));
    while(spawn_positions.size() < 5)
    {
        int pos_x{(for_x_uniform(rd)-1)*59};
        int pos_y{(for_y_uniform(rd)-1)};

        sf::Vector2f pos{float(pos_x), float(pos_y)};
        auto it = std::find(spawn_positions.begin(), spawn_positions.end(), pos);
        if(it == spawn_positions.end())
        {
            spawn_positions.push_back(pos);
        }
    }

    for(sf::Vector2f pos : spawn_positions)
    {
        add_melee_enemy(enemy_sprites.at(sprite_randomizer(rd)-1), pos);
    }
}

void World::load_level_file(std::string const& filename, sf::Window const& window)
{
    std::ifstream filestream{"res/"+filename, std::ifstream::in};

    if(!filestream.is_open())
    {
        std::cerr << "Error: Could not open level with filename '" << filename << "'." << std::endl;
    }

    std::string row;
    for(int y{0}; std::getline(filestream, row); y++)
    {
        for (int x = 0; x < int(row.size()); x++)
        {
            char symbol = row[x];
            switch (symbol) {
                case '#':
                    add_game_object("wall",{float(x-1),float(y-1)});
                    break;

                case '@':
                    add_player({float(x-1),float(y-1)}, window);
                    break;

                case 'b':
                    add_game_object("barrel",{float(x-1),float(y-1)});
                    break;

                case 'c':
                    add_game_object("crate",{float(x-1),float(y-1)});
                    break;

                default:
                    break;
            }
        }
    }

}

int main() {
    sf::RenderWindow window{sf::VideoMode{window_width, window_height}, "The Grand Arena"};
    window.setMouseCursorVisible(false);
    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(true);

    float sprite_scale{2.0f};

    // ==============================[ Font ]==============================
    sf::Font font;
    if(!font.loadFromFile("res/font.ttf"))
    {
        std::cerr << "Could not load font" << std::endl;
    }
    sf::Text fps_text;
    fps_text.setFont(font);
    fps_text.setCharacterSize(font_size);
    fps_text.setString("FPS:0");

    // ==============================[ Background ]==============================
    sf::Texture background_texture;
    background_texture.loadFromFile("textures/background.png");

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


    // ==============================[ Create World ]==============================
    World world{};

    world.add_texture("wall", "textures/wall.png");
    world.add_texture("crate", "textures/crate.png");
    world.add_texture("barrel", "textures/barrel.png");
    world.add_texture("player", "textures/player.png");
    world.add_texture("melee1", "textures/zombie1.png");
    world.add_texture("melee2", "textures/zombie2.png");
    world.add_texture("melee3", "textures/zombie3.png");
    world.add_texture("melee4", "textures/zombie4.png");
    world.add_texture("melee5", "textures/zombie5.png");
    world.add_texture("melee6", "textures/zombie6.png");
    world.add_texture("melee7", "textures/zombie7.png");
    world.add_texture("bullet", "textures/bullet.png");

    world.load_level_file("level1.txt", window);
    world.spawn_monsters();

    sf::Clock clock;
    float time_since_spawn{0};
    float elapsed_time{0};

    // ==============================[ Game Loop ]==============================
    bool quit = false;
    while (true) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    quit = true;
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::F5)
                    {
                        if(world.debug_mode)
                        {
                            world.debug_mode = false;
                        }
                        else
                        {
                            world.debug_mode = true;
                        }
                    }
                default:
                    break;
            }
        }

        if (quit)
        {
            break;
        }

        auto delta_time = clock.restart();
        elapsed_time += delta_time.asSeconds();
        if(elapsed_time > time_since_spawn + 30)
        {
            time_since_spawn = elapsed_time;
            world.spawn_monsters();
        }

        sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        mouse_cursor.setPosition(mouse_pos);

        // 1. Update all game objects.
        for(const std::shared_ptr<Game_Object>& obj : world.game_objects)
        {
            obj->update(delta_time, world, obj);
        }

        // 2. Draw each game object.
        window.clear();
        window.draw(background_sprite);
        for(const std::shared_ptr<Game_Object>& obj : world.game_objects)
        {
            if(world.debug_mode)
            {
                std::shared_ptr<Movable> target_obj{std::dynamic_pointer_cast<Movable>(obj)};
                if(target_obj != nullptr)
                {
                    window.draw(target_obj->collision_shape);
                }
                window.draw(fps_text);
            }
            obj -> render(window);
        }

        // 3. Delete any game objects in the kill queue.
        while (!world.kill_queue.empty())
        {
            /* // Turns off the game when player is dead.
            if (world.kill_queue.at(0) == world.get_player())
            {
                quit = true;
                break;
            }*/
            auto delete_it{std::remove(world.game_objects.begin(), world.game_objects.end(),
                                       world.kill_queue.at(0))};
            world.game_objects.erase(delete_it);

            world.kill_queue.erase(world.kill_queue.begin());
        }
        window.draw(mouse_cursor);
        window.display();
    }

    return 0;
}