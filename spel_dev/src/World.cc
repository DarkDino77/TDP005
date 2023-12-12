#include <SFML/Graphics.hpp>
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
#include "Resource_Manager.h"
#include "point.h"
#include "Health_Drop.h"
#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include <iterator>

World::World()
: resource_manager{*this}
{
    // ==============================[ HUD ]==============================
    auto hud_obj = std::make_shared<Hud>(resource_manager.get_sprite("hud"), *this);
    hud = hud_obj;
    spawn_monsters();

    sf::Vector2f mouse_texture_size{resource_manager.get_mouse_cursor_texture().getSize()};
    mouse_cursor.setSize(mouse_texture_size);
    mouse_cursor.setTexture(&resource_manager.get_mouse_cursor_texture());
    mouse_cursor.setOrigin(mouse_texture_size / 2.f);
    mouse_cursor.setScale(2.0f,2.0f);
}

// ==============================[ Getters ]==============================
std::shared_ptr<Player>& World::get_player()
{
    return player;
}

std::vector<std::string>& World::get_available_pick_ups()
{
    return available_pick_ups;
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

std::shared_ptr<Hud>& World::get_hud()
{
    return hud;
}

Resource_Manager& World::get_resource_manager()
{
    return resource_manager;
}

// ==============================[ Setters ]==============================
void World::kill(std::shared_ptr<Game_Object> const& obj_to_kill)
{
    kill_queue.push_back(obj_to_kill);
}

// ==============================[ Creation ]==============================
void World::add_explosion(sf::Vector2f const& position, float const explosive_radius, int const explosive_damage)
{
    auto explosion = std::make_shared<Explosion>(position,
                                                 resource_manager.get_sprite("explosion"), explosive_radius, explosive_damage);
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
            auto health_drop = std::make_shared<Health_Drop>(position, resource_manager.get_sprite("health_drop"));
            add_queue.push_back(health_drop);
        }
        else
        {
            auto ammo = std::make_shared<Ammo>(position, resource_manager.get_sprite(available_pick_ups.at(random_int)),
                                               available_pick_ups.at(random_int));
            add_queue.push_back(ammo);
        }
    }
}

void World::add_bullet(int const damage, sf::Vector2f const& direction, double const bullet_speed, std::string const& bullet_type, sf::Vector2f const& bullet_spawn, bool const is_friendly)
{
    auto bullet = std::make_shared<Bullet>(damage, direction, bullet_speed, resource_manager.get_sprite(bullet_type), bullet_spawn, is_friendly);
    add_queue.push_back(bullet);
}

void World::add_wall(sf::Vector2f const& position)
{
    auto wall = std::make_shared<Wall>(grid_to_coord(position),
                                       resource_manager.get_sprite("wall"));
    game_objects.push_back(wall);
}

void World::add_explosive_barrel(sf::Vector2f const& position)
{
    auto explosive_barrel = std::make_shared<Explosive_Barrel>(grid_to_coord(position),
                                                               resource_manager.get_sprite("explosive_barrel"), 10);
    game_objects.push_back(explosive_barrel);
}

void World::add_crate(sf::Vector2f const& position)
{
    auto crate = std::make_shared<Crate>(grid_to_coord(position),
                                         resource_manager.get_sprite("crate"), 50);
    game_objects.push_back(crate);
}

void World::add_player(sf::Vector2f const& position)
{
    if(player != nullptr)
    {
        return;
    }
    auto player_obj = std::make_shared<Player>(grid_to_coord(position),
                                               resource_manager.get_sprite("player"), 1.0f, 100);
    game_objects.push_back(player_obj);
    player = std::dynamic_pointer_cast<Player>(player_obj);
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

    mouse_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    mouse_cursor.setPosition(mouse_pos);

    // 1. Update all game objects and handle collisions.
    update_game_objects(delta_time);
    hud->update(delta_time, *this, hud);

    // 2. Add all game_objects in add queue
    add_game_objects();

    // 3. Delete any game objects in the kill queue.
    if(not delete_game_objects())
    {
        quit = true;
        return quit;
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

// ==============================[ Creation ]==============================
void World::add_melee_enemy(std::string const& name, sf::Vector2f const& position)
{
    if(name == "zombie")
    {
        auto enemy = std::make_shared<Melee>(grid_to_coord(position),
                                             resource_manager.get_sprite("melee"), 0.3f, 20, 5, 10);
        game_objects.push_back(enemy);
    }
    if(name == "hulk")
    {
        auto enemy = std::make_shared<Melee>(grid_to_coord(position),
                                             resource_manager.get_sprite("boss"), 0.15f, 100, 20, 30);
        game_objects.push_back(enemy);
    }
    if(name == "biter")
    {
        auto enemy = std::make_shared<Melee>(grid_to_coord(position),
                                             resource_manager.get_sprite("biter"), 0.5f, 10, 10, 10);
        game_objects.push_back(enemy);
    }
}

void World::add_ranged_enemy(std::string const& name, sf::Vector2f const& position)
{
    if(name == "spitter")
    {
        auto enemy = std::make_shared<Ranged>(grid_to_coord(position),
                                              resource_manager.get_sprite("spitter"), 0.15f, 20, 2, 12);
        game_objects.push_back(enemy);
    }
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
    window.draw(resource_manager.get_background_sprite());
    for(const std::shared_ptr<Game_Object>& obj : game_objects)
    {
        obj -> render(window);
    }
}