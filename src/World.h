#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>
#include <string>
#include "Player.h"
#include "Resource_Manager.h"

class Game_Object;
class Player;
class Hud;
class Resource_Manager;

/**
 * @class World
 * @brief Represents the game-world.
 *
 * The World class is responsible for storing all game_objects that are on the map.
 * It provides the functionality to add new game objects and remove existing.
 * The class also allows the game world to be simulated via ticks, using delta_time
 */
class World
{
public:
    /**
     * @brief Constructor for the World class.
     */
    World();

    /**
     * @brief Used to access the player
     *
     * @return A shared pointer to player instance in the world.
     */
    std::shared_ptr<Player>& get_player();

    /**
     * @brief Gets the mouse position
     *
     * @return The coordinate of the mouse position relative to the render window.
     */
    sf::Vector2f& get_mouse_pos();

    /**
     * @brief Gets the elapsed time in seconds.
     *
     * @return The elapsed time in seconds as a float.
     */
    float get_elapsed_time() const;

    /**
     * @brief Used to access the HUD.
     *
     * @return A shared pointer to the HUD instance in the world.
     */
    std::shared_ptr<Hud>& get_hud();

    /**
     * @brief Used to access the available pick-ups in the game world.
     *
     * @return A reference to the available pick-up lists in the world.
     */
    std::vector<std::string>& get_available_pick_ups();

    /**
     * @brief Used to access the resource manager.
     *
     * @return A reference to the resource manager handling all the resources in the world.
     */
    Resource_Manager& get_resource_manager();

    // ==============================[ Setters ]==============================
    /**
     * @brief Adds a game_object to the kill queue.
     *
     * @param obj_to_kill A shared pointer to the game object that is to be deleted.
     */
    void kill(std::shared_ptr<Game_Object> const& obj_to_kill);

    // ==============================[ Creation ]==============================
    /**
     * @brief Adds an explosion to the world.
     *
     * @param position The initial position of the explosion.
     * @param explosive_radius The explosive radius in pixels from the center of the explosion.
     * @param explosive_damage The amount of health point to be deducted from all Damageable targets in the radius.
     */
    void add_explosion(sf::Vector2f const& position, float const explosive_radius, int const explosive_damage);

    /**
     * @brief Adds a pickup to the world.
     *
     * @param position The initial position of the pick-up.
     * @param drop_chance The chance of a pick_up actually appearing once the add_pick_up function has been called (0-100).
     */
    void add_pick_up(sf::Vector2f const& position, int const drop_chance);

    /**
     * @brief Adds a bullet object to the world.
     *
     * @param damage The amount of damage that should be dealt upon collision if the target is a damageable target.
     * @param direction The direction of which the bullet is fired in.
     * @param bullet_speed The speed multiplier of the bullets travel speed.
     * @param bullet_type The type of bullet, used to get the correct texture (Should be "weapon name"_bullet)
     * @param bullet_spawn The initial position of the bullet.
     * @param is_friendly Specifies if the bullet was shot by the player (true) or an enemy (false).
     */
    void add_bullet(int const damage, sf::Vector2f const& direction, double const bullet_speed, std::string const& bullet_type,
                sf::Vector2f const& bullet_spawn, bool const is_friendly);

    // ==============================[ Misc ]==============================
    /**
     * @brief Used to determine if there is a straight path from a game object to
     * the player that is not obstructed by another game object.
     *
     * @param source A shared pointer to the source game object.
     * @param direction The direction that the source game object is facing.
     * @return If the source game_object can see the player.
     */
    bool can_see_player(std::shared_ptr<Game_Object> const& source, sf::Vector2f const& direction);

    // ==============================[ Game Loop ]==============================
    /**
     * @brief Used to simulate the movement and collision handling for all game objects each time the function is called.
     *
     * @param delta_time The time since the simulate function was last called.
     * @param elapsed_time The total amount of time that has passed since the world was initialized.
     * @param window A reference to the render window that the world is to be drawn upon.
     * @return If the game was exited during the simulation tick or not, where true means not exited.
     */
    bool simulate(sf::Time const& delta_time, float const elapsed_time, sf::RenderWindow & window);

    /**
     * @brief Renders the background, all game objects and then the HUD in the given order.
     *
     * @param window A reference to the render window that the gam is to be drawn upon.
     */
    void render(sf::RenderWindow & window);

private:
    // ===[ Containers ]===
    /**
     * A list of all the Game_Objects in the world.
     */
    std::vector<std::shared_ptr<Game_Object>> game_objects{};

    /**
     * A list containing all the available possible pick-ups.
     */
    std::vector<std::string> available_pick_ups{"health_drop"};

    /**
     * A list of all game objects that are to be added at the end of the current simulation.
     */
    std::vector<std::shared_ptr<Game_Object>> add_queue{};

    /**
     * A list of all game objects that are to be removed at the end of the current simulation.
     */
    std::vector<std::shared_ptr<Game_Object>> kill_queue{};

    // ===[ Player ]===
    /**
     * A shared pointer to the instantiated player object in the world.
     */
    std::shared_ptr<Player> player{nullptr};

    // ===[ Waves ]===
    /**
     * The current enemy-wave number.
     */
    int current_wave{1};

    /**
     * The time since the last wave of enemies were spawned, in seconds.
     */
    float time_since_spawn{0};

    // ===[ Graphics ]===
    /**
     * The shape used to replace the mouse cursor.
     */
    sf::RectangleShape mouse_cursor{};

    /**
     * The position of the mouse cursor relative to the render window.
     */
    sf::Vector2f mouse_pos{};

    // ===[ Hud ]===
    /**
     * A shared pointer to the instance of the HUD object that is instantiated in the world.
     */
    std::shared_ptr<Hud> hud{};

    // ===[ Debug ]===
    /**
     * The total time that has passed since the world was instantiated.
     */
    float elapsed_time{0};

    // ===[ Resources ]===
    /**
     * A resource manager managing all images and sounds.
     */
    Resource_Manager resource_manager{};

    // ==============================[ Creation ]==============================
    /**
 * @brief Adds a wall object to the world.
 *
 * @param position The initial position of the wall.
 */
    void add_wall(sf::Vector2f const& position);

    /**
     * @brief Adds an explosive barrel object to the world.
     *
     * @param position The initial position of the explosive barrel.
     */
    void add_explosive_barrel(sf::Vector2f const& position);

    /**
     * @brief Adds a crate object to the world.
     *
     * @param position The initial position of the crate.
     */
    void add_crate(sf::Vector2f const& position);

    /**
     * @brief Adds the player object to the world.
     *
     * @param position The initial position of the player.
     */
    void add_player(sf::Vector2f const& position);

    /**
     * @brief Adds a melee enemy object to the world.
     *
     * @param name The name of the melee enemy sprite category.
     * @param position The initial position of the melee enemy.
     */
    void add_melee_enemy(std::string const& name, sf::Vector2f const& position);

    /**
     * @brief Adds a ranged enemy object to the world.
     *
     * @param name The name of the ranged enemy sprite category.
     * @param position The initial position of the ranged enemy.
     */
    void add_ranged_enemy(std::string const& name, sf::Vector2f const& position);

    /**
    * Opens a file and loads the level via the add-functions in the World class.
    * @param filename The name of the file to load the level from.
    */
    void load_level_file(std::string const& filename);

    /**
     * Spawns a wave of enemies based on the current_wave variable.
     */
    void spawn_monsters();

    /**
     * Adds all the game objects in the add-queue to the world.
     */
    void add_game_objects();

    /**
     * @brief Removes all the game objects in the kill-queue from the world.
     *
     * @return True if the player was not in the kill-queue, else false.
     */
    bool delete_game_objects();

    // ==============================[ Game Loop ]==============================
    /**
     * @brief Checks what objects the current object collides with.
     *
     * @param current_obj A shared pointer to the Game_object of which to check collisions from.
     */
    void check_collision(std::shared_ptr<Game_Object> const& current_obj);

    /**
     * @brief Calls the update function for all the updatable game objects.
     *
     * @param delta_time The time since the update was last called.
     */
    void update_game_objects(sf::Time const& delta_time);

    /**
     * @brief Draws all game objects.
     *
     * @param window A reference to the render window of which the game objects are to be drawn upon.
     */
    void draw_game_objects(sf::RenderWindow & window);
};
#endif