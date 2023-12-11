#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Resource_Manager.h"

class Game_Object;
class Player;
class Hud;
class Resource_Manager;

class World
{
public:
    // ==============================[ Getters ]==============================
    World();
    std::shared_ptr<Player>& get_player();
    sf::Vector2f& get_mouse_pos();
    float get_elapsed_time() const;
    std::shared_ptr<Hud>& get_hud();
    std::vector<std::string>& get_available_pick_ups();
    Resource_Manager& get_resource_manager();

    // ==============================[ Setters ]==============================
    void kill(std::shared_ptr<Game_Object> const& obj_to_kill);

    // ==============================[ Creation ]==============================
    void add_explosion(sf::Vector2f const& position, float const explosive_radius, int const explosive_damage);
    void add_pick_up(sf::Vector2f const& position, int const drop_chance);
    void add_bullet(int const damage, sf::Vector2f const& direction, double const bullet_speed, std::string const& bullet_type,
                    sf::Vector2f const& bullet_spawn, bool const is_friendly);
    void add_wall(sf::Vector2f const& position);
    void add_explosive_barrel(sf::Vector2f const& position);
    void add_crate(sf::Vector2f const& position);
    void add_player(sf::Vector2f const& position);

    // ==============================[ Misc ]==============================
    bool can_see_player(std::shared_ptr<Game_Object> const& source, sf::Vector2f const& direction);

    // ==============================[ Game Loop ]==============================
    bool simulate(sf::Time const& delta_time, float const elapsed_time, sf::RenderWindow & window);
    void render(sf::RenderWindow & window);

private:

    // ===[ Containers ]===
    std::vector<std::shared_ptr<Game_Object>> game_objects{}; //TODO: Determine if public and if unique_ptr
    std::vector<std::string> available_pick_ups{"health_drop"};
    std::vector<std::shared_ptr<Game_Object>> add_queue{};
    std::vector<std::shared_ptr<Game_Object>> kill_queue{};

    // ===[ Player ]===
    std::shared_ptr<Player> player{nullptr};

    // ===[ Waves ]===
    int current_wave{1};
    float time_since_spawn{0};

    // ===[ Graphics ]===
    sf::RectangleShape mouse_cursor{};
    sf::Vector2f mouse_pos{};

    // ===[ Hud ]===
    std::shared_ptr<Hud> hud{};

    // ===[ Debug ]===
    float elapsed_time{0};

    // ===[ Resources ]===
    Resource_Manager resource_manager;

    // ==============================[ Creation ]==============================
    void add_melee_enemy(std::string const& name, sf::Vector2f const& position);
    void add_ranged_enemy(std::string const& name, sf::Vector2f const& position);
    void spawn_monsters();
    void add_game_objects();
    bool delete_game_objects();

    // ==============================[ Game Loop ]==============================
    void check_collision(std::shared_ptr<Game_Object> const& current_obj);
    void update_game_objects(sf::Time const& delta_time);
    void draw_game_objects(sf::RenderWindow & window);
};
#endif