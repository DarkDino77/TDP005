#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <iostream>
#include "World.h"
#include "Player.h"
#include "Melee.h"
#include "Ranged.h"
#include "Crate.h"
#include "Explosion.h"
#include "Explosive_Barrel.h"
#include "Wall.h"
#include "Updatable.h"
#include "Ammo.h"
#include "Hud.h"
#include "point.h"
#include "Health_Drop.h"
#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include <fstream>
#include <iterator>

// ==============================[ Getters ]==============================
std::shared_ptr<Player>& World::get_player()
{
    return player;
}

sf::Texture& World::get_sprite(std::string const& category)
{
    if(sprites[category].empty())
    {
        std::cerr << "Error: A sprite in the category '" << category << "' was never added to world." << std::endl;
        return *sprites["error"].at(0);
    }

    std::random_device rd;
    std::uniform_int_distribution<int> rd_uniform(1,int(sprites[category].size()));
    int sprite_index{(rd_uniform(rd)-1)};

    return *sprites[category].at(sprite_index);
}

sf::Font& World::get_font()
{
    return font;
}

int World::get_level() const
{
    return player_level;
}

float World::get_level_percent() const
{
    return level_percent;
}

float World::get_health_percent() const
{
    return health_percent;
}

std::shared_ptr<Weapon>& World::get_weapon_stats()
{
    return weapon_stats;
}

// TODO bestäm om det är bättre att functionen är const eller om det är att functionen ska returnera ref
sf::Vector2f& World::get_mouse_pos()
{
    return mouse_pos;
}

float World::get_elapsed_time() const
{
    return elapsed_time;
}

// ==============================[ Setters ]==============================
void World::kill(std::shared_ptr<Game_Object> const& obj_to_kill)
{
    kill_queue.push_back(obj_to_kill);
}

void World::set_health_percent(int const health, int const max_health)
{
    health_percent = (float(health) / float(max_health));
}
void World::set_weapon_stats(std::shared_ptr<Weapon> const& weapon)
{
    weapon_stats = weapon;
}

void World::add_player_xp(int const xp)
{
    player_level_progression+=xp;
    while(player_level_progression >= xp_to_level)
    {
        level_up_player();
    }
    level_percent = float(player_level_progression)/float(xp_to_level);
}

// ==============================[ Creation ]==============================
void World::load()
{
    load_font();

    fps_text.setFont(font);
    fps_text.setCharacterSize(24);
    fps_text.setOutlineColor(sf::Color (0x373737ff));
    fps_text.setOutlineThickness(4);
    fps_text.setPosition(10+33*4,10 + 4*4);
    fps_text.setString("FPS:0");

    // ==============================[ Background ]==============================
    load_background();

    // ==============================[ Cursor ]==============================
    load_cursor();

    // ==============================[ Create World ]==============================
    load_textures();

    // ==============================[ Add audio ]==============================
    load_audio();

    load_pick_ups();


    sf::Music music;
    if (!music.openFromFile("audio/music.ogg"))
    {
        std::cerr << "Error: Could not find music with filename 'audio/music.ogg'." << std::endl;
        return;
    }
    music.play();

    // ==============================[ HUD ]==============================
    auto hud_obj = std::make_shared<Hud>(sf::Vector2f {0,0}, get_sprite("hud"), *this);
    hud = hud_obj;

    load_level_file("level1.txt");
    spawn_monsters();
}

void World::add_explosion(sf::Vector2f const& position, float const explosive_radius, int const explosive_damage)
{
    auto explosion = std::make_shared<Explosion>(position,
                                                 get_sprite("explosion"), explosive_radius, explosive_damage);
    add_queue.push_back(explosion);
}

void World::add_pick_up(sf::Vector2f const& position, int const drop_chance)
{
    std::random_device rd;
    std::uniform_int_distribution<int> uniform_rd(1,100);
    int rand_int{uniform_rd(rd)};


    if(rand_int <= drop_chance)
    {
        std::uniform_int_distribution<int> rand_pick_up_rd(1,int(available_pick_ups.size()));

        int random_int{rand_pick_up_rd(rd)-1};

        if(random_int == 0)
        {
            auto health_drop = std::make_shared<Health_Drop>(position, get_sprite("health_drop"));
            add_queue.push_back(health_drop);
        }
        else
        {
            auto ammo = std::make_shared<Ammo>(position, get_sprite(available_pick_ups.at(random_int)),
                                               available_pick_ups.at(random_int));
            add_queue.push_back(ammo);
        }
    }
}

void World::add_bullet(int const damage, sf::Vector2f const& direction, double const bullet_speed, std::string const& bullet_type, sf::Vector2f const& bullet_spawn, std::shared_ptr<Game_Object> const& source)
{
    auto bullet = std::make_shared<Bullet>(damage, direction, bullet_speed, get_sprite(bullet_type), bullet_spawn, source);
    add_queue.push_back(bullet);
}

// ==============================[ Misc ]==============================
bool World::can_see_player(std::shared_ptr<Game_Object> const& source, sf::Vector2f const& direction)
{
    sf::CircleShape collision_checker;
    collision_checker.setRadius(5);
    collision_checker.setOrigin({collision_checker.getRadius(),collision_checker.getRadius()});
    collision_checker.setPosition(source->get_position());

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

void World::play_sound(std::string const& name)
{
    if(sounds[name].empty())
    {
        std::cerr << "Error: Sound with name '" << name << "' was never added to world." << std::endl;
        return;
    }

    std::random_device rd;
    std::uniform_int_distribution<int> rd_uniform(1,int(sound_buffers[name].size()));
    int track_index{(rd_uniform(rd)-1)};

    sounds[name].at(track_index)->play();
}

// ==============================[ Game Loop ]==============================
bool World::simulate(sf::Time const& delta_time, float const elapsed_time_in, sf::RenderWindow & window)
{
    bool quit = false;
    elapsed_time = elapsed_time_in;

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
                        std::cout << "Debug on" << std::endl;
                        debug_mode = true;
                    }
                }
            default:
                break;
        }
    }

    if (quit)
    {
        return quit;
    }

    if(elapsed_time > time_since_spawn + 30)
    {
        time_since_spawn = elapsed_time;
        spawn_monsters();
    }

    float fps = 1.0f / (elapsed_time - last_time);
    last_time = elapsed_time;

    mouse_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    mouse_cursor.setPosition(mouse_pos);

    // 1. Update all game objects and handle collisions.
    update_game_objects(delta_time);
    hud->update(delta_time, *this, hud);

    // 3. Add all game_objects in add queue
    add_game_objects();

    // 4. Delete any game objects in the kill queue.
    if(not delete_game_objects())
    {
        quit = true;
        return quit;
    }

    if (debug_mode)
    {
        fps_text.setString("FPS: " + std::to_string(int(fps)));
        window.draw(fps_text);
    }

    return quit;
}

void World::render(sf::RenderWindow & window)
{
    draw_game_objects(window);
    window.draw(mouse_cursor);
    hud->render(window);
}

// =====================================================================================================
// =============================================[ Private ]=============================================
// =====================================================================================================

// ==============================[ Load ]==============================
void World::load_level_file(std::string const& filename)
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
                    add_player({float(x-1),float(y-1)});
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

void World::load_font()
{
    if(!font.loadFromFile("res/font3.ttf"))
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

void World::load_pick_ups()
{
    available_pick_ups.push_back("health_drop");
}

void World::load_textures()
{
    // Map objects
    add_texture("error", "textures/error.png");
    add_texture("wall", "textures/wall_1.png");
    add_texture("wall", "textures/wall_2.png");
    add_texture("crate", "textures/crate.png");
    add_texture("explosive_barrel", "textures/explosive_barrel.png");

    // Characters
    add_texture("player", "textures/player.png");
    add_texture("melee", "textures/zombie1.png");
    add_texture("melee", "textures/zombie2.png");
    add_texture("melee", "textures/zombie3.png");
    add_texture("melee4", "textures/zombie4.png");
    add_texture("melee5", "textures/zombie5.png");
    add_texture("melee6", "textures/zombie6.png");
    add_texture("melee7", "textures/zombie7.png");
    add_texture("spitter", "textures/spitter1.png");
    add_texture("spitter", "textures/spitter2.png");
    add_texture("biter", "textures/biter1.png");
    add_texture("biter", "textures/biter2.png");
    add_texture("boss", "textures/zombie_boss1.png");
    add_texture("boss", "textures/zombie_boss2.png");

    // Weapons
    add_texture("spitter_bullet", "textures/spitter_bullet.png");
    add_texture("explosion", "textures/explosion.png");
    add_texture("glock_bullet", "textures/glock_bullet.png");
    add_texture("baretta_bullet", "textures/baretta_bullet.png");
    add_texture("uzi_bullet", "textures/uzi_bullet.png");
    add_texture("shotgun_bullet", "textures/shotgun_bullet.png");
    add_texture("assault_rifle_bullet", "textures/assault_rifle_bullet.png");
    add_texture("sniper_rifle_bullet", "textures/sniper_rifle_bullet.png");
    add_texture("baretta_ammo", "textures/baretta_ammo.png");
    add_texture("uzi_ammo", "textures/uzi_ammo.png");
    add_texture("shotgun_ammo", "textures/shotgun_ammo.png");
    add_texture("assault_rifle_ammo", "textures/assault_rifle_ammo.png");
    add_texture("sniper_rifle_ammo", "textures/sniper_rifle_ammo.png");

    add_texture("health_drop", "textures/health_pick_up.png");

    // HUD
    add_texture("hud", "textures/hud.png");
    add_texture("hud_level", "textures/hud_level.png");
    add_texture("hud_health", "textures/hud_health.png");
    add_texture("hud_health_fill", "textures/hud_health_fill.png");
    add_texture("hud_level_fill", "textures/hud_level_fill.png");
    add_texture("hud_weapon_background", "textures/hud_weapon_background.png");
    add_texture("glock_hud", "textures/glock_hud.png");
    add_texture("baretta_hud", "textures/baretta_hud.png");
    add_texture("uzi_hud", "textures/uzi_hud.png");
    add_texture("shotgun_hud", "textures/shotgun_hud.png");
    add_texture("assault_rifle_hud", "textures/assault_rifle_hud.png");
    add_texture("sniper_rifle_hud", "textures/sniper_rifle_hud.png");
}

void World::load_audio()
{
    // Weapons
    add_sound("glock_shoot", "audio/glock_shoot_1.wav");
    add_sound("glock_shoot", "audio/glock_shoot_2.wav");
    add_sound("baretta_shoot", "audio/baretta_shoot_1.wav");
    add_sound("baretta_shoot", "audio/baretta_shoot_2.wav");
    add_sound("uzi_shoot", "audio/uzi_shoot_1.wav");
    add_sound("uzi_shoot", "audio/uzi_shoot_2.wav");
    add_sound("uzi_shoot", "audio/uzi_shoot_3.wav");
    add_sound("shotgun_shoot", "audio/shotgun_shoot_1.wav");
    add_sound("shotgun_shoot", "audio/shotgun_shoot_2.wav");
    add_sound("shotgun_shoot", "audio/shotgun_shoot_3.wav");
    add_sound("assault_rifle_shoot", "audio/assault_rifle_shoot_1.wav");
    add_sound("assault_rifle_shoot", "audio/assault_rifle_shoot_2.wav");
    add_sound("assault_rifle_shoot", "audio/assault_rifle_shoot_3.wav");
    add_sound("sniper_rifle_shoot", "audio/sniper_rifle_shoot_1.wav");
    add_sound("sniper_rifle_shoot", "audio/sniper_rifle_shoot_2.wav");
    add_sound("sniper_rifle_shoot", "audio/sniper_rifle_shoot_3.wav");
    add_sound("spitter_shoot", "audio/spitter_shoot.wav");
    add_sound("ammo_pick_up", "audio/ammo_pick_up.wav");

    // Player
    add_sound("player_hurt", "audio/player_hurt_1.wav");
    add_sound("player_hurt", "audio/player_hurt_2.wav");
    add_sound("player_hurt", "audio/player_hurt_3.wav");
    add_sound("player_hurt", "audio/player_hurt_4.wav");

    // Enemy
    add_sound("enemy_hurt", "audio/enemy_hurt_1.wav");
    add_sound("enemy_hurt", "audio/enemy_hurt_2.wav");
    add_sound("enemy_hurt", "audio/enemy_hurt_3.wav");
    add_sound("enemy_hurt", "audio/enemy_hurt_4.wav");

    // Other
    add_sound("explosion", "audio/explosion.wav");
    add_sound("crate_destroy", "audio/crate_destroy.wav");
    add_sound("bullet_impact", "audio/bullet_impact_1.wav");
    add_sound("bullet_impact", "audio/bullet_impact_2.wav");
    add_sound("bullet_impact", "audio/bullet_impact_3.wav");
}

// ==============================[ Creation ]==============================
void World::add_texture(std::string const& category, std::string const& filename)
{
    auto texture = std::make_shared<sf::Texture>();
    if(!texture->loadFromFile(filename))
    {
        std::cerr << "Error: Could not find image with name '" << filename << "'." << std::endl;
    }
    else
    {
        sprites[category].push_back(texture);
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
        std::shared_ptr<sf::Sound> sound{std::make_shared<sf::Sound>()};
        sound->setBuffer(*sound_buffers[category].back());
        sounds[category].push_back(sound);
    }
}

void World::add_player(sf::Vector2f const& position)
{
    auto player_obj = std::make_shared<Player>(grid_to_coord(position),
                                               get_sprite("player"), 1.0f, 100, *this);
    game_objects.push_back(player_obj);
    player = std::dynamic_pointer_cast<Player>(player_obj);
}

void World::add_melee_enemy(std::string const& name, sf::Vector2f const& position)
{
    if(name == "zombie")
    {
        auto enemy = std::make_shared<Melee>(grid_to_coord(position),
                                             get_sprite("melee"), 0.3f, 20, 5, 10);
        game_objects.push_back(enemy);
    }
    if(name == "hulk")
    {
        auto enemy = std::make_shared<Melee>(grid_to_coord(position),
                                             get_sprite("boss"), 0.15f, 100, 20, 30);
        game_objects.push_back(enemy);
    }
    if(name == "biter")
    {
        auto enemy = std::make_shared<Melee>(grid_to_coord(position),
                                             get_sprite("biter"), 0.5f, 10, 10, 10);
        game_objects.push_back(enemy);
    }
}

void World::add_ranged_enemy(std::string const& name, sf::Vector2f const& position)
{
    if(name == "spitter")
    {
        auto enemy = std::make_shared<Ranged>(grid_to_coord(position),
                                              get_sprite("spitter"), 0.15f, 20, 2, 12);
        game_objects.push_back(enemy);
    }
}

void World::add_wall(sf::Vector2f const& position)
{
    auto wall = std::make_shared<Wall>(grid_to_coord(position),
                                       get_sprite("wall"));
    game_objects.push_back(wall);
}

void World::add_explosive_barrel(sf::Vector2f const& position)
{
    auto explosive_barrel = std::make_shared<Explosive_Barrel>(grid_to_coord(position),
                                                               get_sprite("explosive_barrel"), 10);
    game_objects.push_back(explosive_barrel);
}

void World::add_crate(sf::Vector2f const& position)
{
    auto crate = std::make_shared<Crate>(grid_to_coord(position),
                                         get_sprite("crate"), 50);
    game_objects.push_back(crate);
}

void World::spawn_monsters()
{
    int num_enemies{5 + ((current_wave - 1) * 2)};
    int num_ranged{int(std::floor(float(current_wave) * 0.5f))};
    int num_biter{current_wave};

    std::vector<sf::Vector2f> spawn_positions{};

    std::random_device rd;
    std::uniform_int_distribution<int> for_x_uniform(1,2);
    std::uniform_int_distribution<int> for_y_uniform(1,31);

    int num_melee_spawned{0};
    while ( num_melee_spawned < (num_enemies-num_ranged-num_biter))
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

    int num_biter_spawned{0};
    while(num_biter_spawned < num_biter)
    {
        int pos_x{(for_x_uniform(rd)-1)*59};
        int pos_y{(for_y_uniform(rd)-1)};
        sf::Vector2f pos{float(pos_x), float(pos_y)};
        auto it = std::find(spawn_positions.begin(), spawn_positions.end(), pos);
        if(it == spawn_positions.end())
        {
            add_melee_enemy("biter", pos);
            num_biter_spawned++;
            spawn_positions.push_back(pos);
        }
    }

    if(current_wave % 5 == 0)
    {
        add_melee_enemy("hulk", {10,10});
    }
    current_wave++;
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

// ==============================[ Game Loop ]==============================
void World::add_player_weapon()
{
    switch (player_level)
    {
        case(2):
            player->add_weapon("baretta", 15, 200, 2.5, 2);
            player->add_ammo("baretta_ammo", 200);
            available_pick_ups.push_back("baretta_ammo");
            break;
        case(4):
            player->add_weapon("uzi", 10, 500, 2.5, 5);
            player->add_ammo("uzi_ammo", 500);
            available_pick_ups.push_back("uzi_ammo");
            break;
        case(6):
            player->add_weapon("shotgun", 30, 50, 2, 0.75);
            player->add_ammo("shotgun_ammo", 50);
            available_pick_ups.push_back("shotgun_ammo");
            break;
        case(8):
            player->add_weapon("assault_rifle", 35, 300, 2.5, 4);
            player->add_ammo("assault_rifle_ammo", 300);
            available_pick_ups.push_back("assault_rifle_ammo");
            break;
        case(10):
            player->add_weapon("sniper_rifle", 70, 300, 3, 2);
            player->add_ammo("sniper_rifle_ammo", 40);
            available_pick_ups.push_back("sniper_rifle_ammo");
            break;
    }
}

void World::level_up_player()
{
    hud->pop_up("LEVEL UP");
    player_level_progression -= xp_to_level;
    xp_to_level+=5;
    player_level+= 1;

    switch (player_level%10) {
        case 0:
            player->increase_max_health(10);
            hud->pop_up("MAX HEALTH +10");
            add_player_weapon();
            break;
        case 2:
            add_player_weapon();
            break;
        case 4:
            add_player_weapon();
            break;
        case 6:
            add_player_weapon();
            break;
        case 8:
            add_player_weapon();
            break;
        default:
            break;

    }
}

void World::check_collision(std::shared_ptr<Game_Object> const& current_obj)
{
// Handle collision
    std::shared_ptr<Collidable> collidable_target{std::dynamic_pointer_cast<Collidable>(current_obj)};
    if(collidable_target == nullptr)
    {
        return;
    }

    sf::FloatRect current_bounds = collidable_target->get_collision_shape().getGlobalBounds();

    for(std::shared_ptr<Game_Object> const& other_obj : game_objects)
    {
        sf::FloatRect other_bounds = (other_obj->get_shape()).getGlobalBounds();
        if(not current_bounds.intersects(other_bounds) || current_obj == other_obj)
        {
            continue;
        }

        collidable_target->handle_collision(*this, current_obj, other_obj);

    }
}

void World::update_game_objects(sf::Time const& delta_time)
{
    for(std::shared_ptr<Game_Object> const& current_obj : game_objects) {
        // Update
        std::shared_ptr<Updatable> updatable_target{std::dynamic_pointer_cast<Updatable>(current_obj)};
        if (updatable_target == nullptr) {
            continue;
        }
        updatable_target->update(delta_time, *this, current_obj);

        check_collision(current_obj);
    }
}

void World::draw_game_objects(sf::RenderWindow & window)
{
    window.clear();
    window.draw(background_sprite);
    for(const std::shared_ptr<Game_Object>& obj : game_objects)
    {
        if(debug_mode)
        {
            std::shared_ptr<Collidable> collidable_target{std::dynamic_pointer_cast<Collidable>(obj)};

            if(collidable_target != nullptr)
            {
                window.draw(collidable_target->get_collision_shape());
            }
        }
        obj -> render(window);
    }
}