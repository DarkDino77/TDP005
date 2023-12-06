#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "standard.h"
#include "World.h"
#include "Player.h"
#include "Melee.h"
#include "Ranged.h"
#include "Crate.h"
#include "Explosion.h"
#include "Explosive_Barrel.h"
#include "Wall.h"
#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include <fstream>
#include <iterator>

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
        std::cerr << "Error: Could not find image with name '" << filename << "'." << std::endl;
    }
    else
    {
        sprites[name] = texture;
    }
}

void World::add_sound(std::string const& category,  std::string const& filename)
{
    auto sound_buffer = std::make_shared<sf::SoundBuffer>();
    if (!sound_buffer->loadFromFile(filename))
    {
        std::cerr << "Error: Could not find file with name '" << filename << "'." << std::endl;
    }
    else
    {
        sound_buffers[category].push_back(sound_buffer);
    }
}

void World::play_sound(std::string const& name)
{
    if(sound_buffers[name].empty())
    {
        std::cerr << "Error: Sound with name '" << name << "' was never added to world." << std::endl;
        return;
    }

    std::random_device rd;
    std::uniform_int_distribution<int> rd_uniform(1,int(sound_buffers[name].size()));
    int track_index{(rd_uniform(rd)-1)};

    std::shared_ptr<sf::Sound> sound{std::make_shared<sf::Sound>()};
    sound->setBuffer(*sound_buffers[name].at(track_index));
    sound->play();
    sound_queue.push_back(sound);
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
    if(name == "zombie")
    {
        auto enemy = std::make_shared<Melee>(grid_to_coord(position),
                                             *sprites["melee1"], 0.3f, 20, 5);
        game_objects.push_back(enemy);
    }
}

void World::add_ranged_enemy(std::string const& name, sf::Vector2f const& position)
{
    if(name == "spitter")
    {
        auto enemy = std::make_shared<Ranged>(grid_to_coord(position),
                                             *sprites["spitter1"], 0.15f, 20, 2);
        game_objects.push_back(enemy);
    }
}

void World::add_wall(sf::Vector2f const& position)
{
    auto wall = std::make_shared<Wall>(grid_to_coord(position),
                                                  *sprites["wall"]);
    game_objects.push_back(wall);
}

void World::add_explosive_barrel(sf::Vector2f const& position)
{
    auto explosive_barrel = std::make_shared<Explosive_Barrel>(grid_to_coord(position),
                                                  *sprites["explosive_barrel"], 10);
    game_objects.push_back(explosive_barrel);
}

void World::add_crate(sf::Vector2f const& position)
{
    auto crate = std::make_shared<Crate>(grid_to_coord(position),
                                                  *sprites["crate"], 50);
    game_objects.push_back(crate);
}

void World::add_explosion(std::string const& name, sf::Vector2f const& position)
{
    auto explosion = std::make_shared<Explosion>(position,
                                          *sprites[name], 100, 10);
    add_queue.push_back(explosion);
}

std::shared_ptr<Player> World::get_player()
{
    return player;
}

void World::kill(std::shared_ptr<Game_Object> const& obj_to_kill)
{
    kill_queue.push_back(obj_to_kill);
}
/*void World::set_health_percent(int health)
{
    health_percent = health;
    hud_elements.at(0)->setScale(4.0f*health_percent/100, 4.0f);
}
void World::set_level_percent(int level_progress)
{
    level_percent = level_progress;
    hud_elements.at(2)->setScale(4.0f*level_percent/100, 4.0f);
}*/

void World::add_bullet(int damage, sf::Vector2f const& direction, double bullet_speed, std::string const& ammo_type, sf::Vector2f & bullet_spawn, std::shared_ptr<Game_Object> const& source)
{
    auto bullet = std::make_shared<Bullet>(damage, direction, bullet_speed, *sprites[ammo_type], bullet_spawn, source);
    add_queue.push_back(bullet);
}

void World::spawn_monsters()
{
    int num_enemies{5 + ((current_wave - 1) * 2)};
    int num_ranged{int(std::floor(float(current_wave) * 0.5f))};

    std::vector<sf::Vector2f> spawn_positions{};
    //std::vector<std::string> enemy_sprites{"melee1","melee2", "melee3", "melee4", "melee5", "melee6", "melee7"};

    std::random_device rd;
    std::uniform_int_distribution<int> for_x_uniform(1,2);
    std::uniform_int_distribution<int> for_y_uniform(1,31);
    //std::uniform_int_distribution<int> sprite_randomizer(1,int(enemy_sprites.size()));

    int num_melee_spawned{0};
    while ( num_melee_spawned < (num_enemies-num_ranged))
    {
        int pos_x{(for_x_uniform(rd)-1)*59};
        int pos_y{(for_y_uniform(rd)-1)};
        sf::Vector2f pos{float(pos_x), float(pos_y)};
        auto it = std::find(spawn_positions.begin(), spawn_positions.end(), pos);
        if(it == spawn_positions.end())
        {
            add_melee_enemy("zombie", pos);
            num_melee_spawned++;
            spawn_positions.push_back(pos);
        }
    }

    int num_ranged_spawned{0};
    while(num_ranged_spawned < num_ranged)
    {
        int pos_x{(for_x_uniform(rd)-1)*59};
        int pos_y{(for_y_uniform(rd)-1)};
        sf::Vector2f pos{float(pos_x), float(pos_y)};
        auto it = std::find(spawn_positions.begin(), spawn_positions.end(), pos);
        if(it == spawn_positions.end())
        {
            add_ranged_enemy("spitter", pos);
            num_ranged_spawned++;
            spawn_positions.push_back(pos);
        }
    }
    current_wave++;
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
                    add_wall({float(x-1),float(y-1)});
                    break;

                case '@':
                    add_player({float(x-1),float(y-1)}, window);
                    break;

                case 'b':
                    add_explosive_barrel({float(x-1),float(y-1)});
                    break;

                case 'c':
                    add_crate({float(x-1),float(y-1)});
                    break;

                default:
                    break;
            }
        }
    }
}

bool World::can_see_player(std::shared_ptr<Game_Object> source, sf::Vector2f direction)
{
    sf::CircleShape collision_checker;
    collision_checker.setRadius(5);
    collision_checker.setOrigin({collision_checker.getRadius(),collision_checker.getRadius()});
    collision_checker.setPosition(source->get_position());
    //collision_checker.setFillColor(sf::Color::Red);

    while(true)
    {
        for(std::shared_ptr<Game_Object> const& collide_obj : game_objects) {
            sf::FloatRect collision_bounds = collision_checker.getGlobalBounds();
            sf::FloatRect other_bounds = (collide_obj->get_shape()).getGlobalBounds();

            if(collide_obj == source || not collision_bounds.intersects(other_bounds)  )
            {
                continue;
            }

            std::shared_ptr<Player> player_target{std::dynamic_pointer_cast<Player>(collide_obj)};
            if( player_target == nullptr)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        collision_checker.setPosition(collision_checker.getPosition() - direction * 16.0f * 2.f * 0.9f);
    }
}

void World::make_window()
{
    window.setMouseCursorVisible(false);
    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(false);
}

void World::load_font()
{
    if(!font.loadFromFile("res/font.ttf"))
    {
        std::cerr << "Could not load font" << std::endl;
    }
}

void World::load_background()
{
    background_texture.loadFromFile("textures/background.png");
    background_sprite.setTexture(background_texture);
}

void World::load_cursor()
{
    mouse_cursor_texture.loadFromFile("textures/crosshair.png");
    sf::Vector2f mouse_texture_size{mouse_cursor_texture.getSize()};
    mouse_cursor.setSize(mouse_texture_size);
    mouse_cursor.setTexture(&mouse_cursor_texture);
    mouse_cursor.setOrigin(mouse_texture_size / 2.f);
    mouse_cursor.setScale(2.0f,2.0f);
}

void World::load_textures()
{
    add_texture("wall", "textures/wall.png");
    add_texture("crate", "textures/crate.png");
    add_texture("explosive_barrel", "textures/explosive_barrel.png");
    add_texture("player", "textures/player.png");
    add_texture("melee1", "textures/zombie1.png");
    add_texture("melee2", "textures/zombie2.png");
    add_texture("melee3", "textures/zombie3.png");
    add_texture("melee4", "textures/zombie4.png");
    add_texture("melee5", "textures/zombie5.png");
    add_texture("melee6", "textures/zombie6.png");
    add_texture("melee7", "textures/zombie7.png");
    add_texture("glock_ammo", "textures/glock_ammo.png");
    add_texture("spitter_ammo", "textures/spitter_ammo.png");
    add_texture("spitter1", "textures/spitter1.png");
    add_texture("explosion", "textures/explosion.png");

    // HUD
    add_texture("hud_level", "textures/hud_level.png");
    add_texture("hud_health", "textures/hud_health.png");
    add_texture("hud_health_fill", "textures/hud_health_fill.png");
    add_texture("hud_level_fill", "textures/hud_level_fill.png");
    add_texture("hud_weapon_background", "textures/hud_weapon_background.png");
}

void World::load_audio()
{
    add_sound("glock_shoot", "audio/glock_shoot_1.wav");
    add_sound("glock_shoot", "audio/glock_shoot_2.wav");
    add_sound("spitter_shoot", "audio/spitter_shoot.wav");
    add_sound("player_hurt", "audio/player_hurt.wav");
    add_sound("explosion", "audio/explosion.wav");
}

/*void World::load_hud()
{
    std::shared_ptr<sf::RectangleShape> hud_current_health = std::make_shared<sf::RectangleShape>();
    hud_current_health->setTexture(&*sprites["hud_health_fill"]);
    hud_current_health->setSize(sf::Vector2f(hud_current_health->getTexture()->getSize()));
    hud_current_health->setOrigin({hud_current_health->getSize().x,hud_current_health->getSize().y/2.0f});
    hud_current_health->setPosition(1906-18*4,26);
    hud_current_health->setScale(4.0f * health_percent/100, 4.0f);
    hud_elements.push_back(hud_current_health);

    std::shared_ptr<sf::RectangleShape> hud_health = std::make_shared<sf::RectangleShape>();
    hud_health->setTexture(&*sprites["hud_health"]);
    hud_health->setSize(sf::Vector2f(hud_health->getTexture()->getSize()));
    hud_health->setOrigin({hud_health->getSize().x,0});
    hud_health->setPosition(1910-18*4,10);
    hud_health->setScale(4.0f, 4.0f);
    hud_elements.push_back(hud_health);

    std::shared_ptr<sf::RectangleShape> hud_current_level = std::make_shared<sf::RectangleShape>();
    hud_current_level->setTexture(&*sprites["hud_level_fill"]);
    hud_current_level->setSize(sf::Vector2f(hud_current_level->getTexture()->getSize()));
    hud_current_level->setOrigin({0,hud_current_level->getSize().y/2.0f});
    hud_current_level->setPosition(14,26);
    hud_current_level->setScale(4.0f * level_percent/100, 4.0f);
    hud_elements.push_back(hud_current_level);

    std::shared_ptr<sf::RectangleShape> hud_level = std::make_shared<sf::RectangleShape>();
    hud_level->setTexture(&*sprites["hud_level"]);
    hud_level->setSize(sf::Vector2f(hud_level->getTexture()->getSize()));
    hud_level->setOrigin({0,0});
    hud_level->setPosition(10,10);
    hud_level->setScale(4.0f, 4.0f);
    hud_elements.push_back(hud_level);

    std::shared_ptr<sf::RectangleShape> hud_weapon_background = std::make_shared<sf::RectangleShape>();
    hud_weapon_background->setTexture(&*sprites["hud_weapon_background"]);
    hud_weapon_background->setSize(sf::Vector2f(hud_weapon_background->getTexture()->getSize()));
    hud_weapon_background->setOrigin({hud_weapon_background->getSize().x, 0});
    hud_weapon_background->setPosition(1910, 10);
    hud_weapon_background->setScale(4.0f, 4.0f);
    hud_elements.push_back(hud_weapon_background);
}*/

void World::update_game_objects(sf::Time const& delta_time)
{
    for(const std::shared_ptr<Game_Object>& current_obj : game_objects)
    {
        std::shared_ptr<Wall> wall_target{std::dynamic_pointer_cast<Wall>(current_obj)};
        if(wall_target != nullptr)
        {
            continue;
        }
        current_obj->update(delta_time, *this, current_obj);
        std::shared_ptr<Destructible> destructible_target{std::dynamic_pointer_cast<Destructible>(current_obj)};
        if(destructible_target != nullptr)
        {
            continue;
        }

        sf::FloatRect current_bounds = current_obj->get_shape().getGlobalBounds();
        std::shared_ptr<Movable> movable_target{std::dynamic_pointer_cast<Movable>(current_obj)};
        std::shared_ptr<Explosion> explosive_target{std::dynamic_pointer_cast<Explosion>(current_obj)};
        if(movable_target != nullptr  )
        {
            current_bounds = movable_target->get_collision_shape().getGlobalBounds();
        }
        else if(explosive_target != nullptr)
        {
            current_bounds = explosive_target->get_collision_shape().getGlobalBounds();
        }

        for(std::shared_ptr<Game_Object> const& other_obj : game_objects)
        {
            sf::FloatRect other_bounds = (other_obj->get_shape()).getGlobalBounds();
            if(not current_bounds.intersects(other_bounds))
            {
                continue;
            }

            std::shared_ptr<Movable> other_movable_target{std::dynamic_pointer_cast<Movable>(other_obj)};
            std::shared_ptr<Explosion> other_explosive_target{std::dynamic_pointer_cast<Explosion>(other_obj)};
            if(other_movable_target != nullptr)
            {
                other_bounds = other_movable_target->get_collision_shape().getGlobalBounds();
            }
            else if(other_explosive_target != nullptr)
            {
                other_bounds = other_explosive_target->get_collision_shape().getGlobalBounds();
            }

            if(current_obj != other_obj && current_bounds.intersects(other_bounds))
            {
                current_obj->handle_collision(*this, current_obj, other_obj);
            }
        }
    }
}

void World::draw_game_objects()
{
    window.clear();
    window.draw(background_sprite);
    for(const std::shared_ptr<Game_Object>& obj : game_objects)
    {
        if(debug_mode)
        {
            std::shared_ptr<Movable> movable_target{std::dynamic_pointer_cast<Movable>(obj)};
            std::shared_ptr<Explosion> explosive_target{std::dynamic_pointer_cast<Explosion>(obj)};
            if(movable_target != nullptr)
            {
                window.draw(movable_target->get_collision_shape());
            }
            else if(explosive_target != nullptr)
            {
                window.draw(explosive_target->get_collision_shape());
            }
        }
        obj -> render(window);
    }
}

void World::add_game_objects()
{
    while (!add_queue.empty())
    {
        game_objects.push_back(add_queue.at(0));
        add_queue.erase(add_queue.begin());
    }
}

bool World::delete_game_objects()
{
    while (!kill_queue.empty())
    {
        // Turns off the game when player is dead.
        if (kill_queue.at(0) == get_player())
        {
            return false;
        }
        auto delete_it{std::remove(game_objects.begin(), game_objects.end(),
                                   kill_queue.at(0))};
        game_objects.erase(delete_it);

        kill_queue.erase(kill_queue.begin());
    }
    return true;
}

/*void World::draw_hud()
{
    for(std::shared_ptr<sf::RectangleShape> const& hud_element : hud_elements)
    {
        window.draw(*hud_element);
    }
}*/

void World::simulate()
{
    make_window();
    load_font();

    sf::Text fps_text;
    fps_text.setFont(font);
    fps_text.setCharacterSize(font_size);
    fps_text.setOutlineColor(sf::Color (0x373737ff));
    fps_text.setOutlineThickness(4);
    fps_text.setString("FPS:0");

    /*
    sf::Texture number_texture;
    if(!number_texture.loadFromFile("textures/numbers.png"))
    {
        return;
    }

    sf::Sprite number_sprites[11];
    int char_width{5};

    for (int i = 0; i < 11; i++)
    {
        number_sprites[i].setTexture(number_texture);
        number_sprites[i].setTextureRect(sf::IntRect(i * char_width, 0, char_width, 8));
        number_sprites[i].setPosition(i * char_width, 0);
    }*/

    // ==============================[ Background ]==============================
    load_background();

    // ==============================[ Cursor ]==============================
    load_cursor();

    // ==============================[ Create World ]==============================
    load_textures();

    // ==============================[ Add audio ]==============================
    load_audio();
    sf::Music music;
    if (!music.openFromFile("audio/music.ogg"))
    {
        std::cerr << "Error: Could not find music with filename 'audio/music.ogg'." << std::endl;
        return;
    }
    music.play();

    // ==============================[ HUD ]==============================
    //load_hud();

    load_level_file("level1.txt", window);
    spawn_monsters();

    sf::Clock clock;
    float time_since_spawn{0};
    float elapsed_time{0};
    float last_time{0};
    float fps;

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
                        if(debug_mode)
                        {
                            debug_mode = false;
                        }
                        else
                        {
                            debug_mode = true;
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
            spawn_monsters();
        }

        fps = 1.0f / (elapsed_time - last_time);
        last_time = elapsed_time;

        sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        mouse_cursor.setPosition(mouse_pos);

        // 1. Update all game objects and handle collisions.
        update_game_objects(delta_time);

        // 2. Draw each game object.
        draw_game_objects();

        // 3. Add all game_objects in add queue
        add_game_objects();

        // 4. Delete any game objects in the kill queue.
        if(not delete_game_objects())
        {
            quit = true;
            break;
        }

        if (debug_mode)
        {
            fps_text.setString("FPS:" + std::to_string(int(fps)));
            window.draw(fps_text);
        }
        window.draw(mouse_cursor);

        //draw_hud();
        window.display();

    }

}