#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
#include "World.h"
#include "Weapon.h"
#include "Hud.h"
/**
 * @class Player
 * @brief This class represents a Player object and inherits from the Character class.
 *
 * The player class represents the character that the user controls.
 * Stats such as player health, xp and level are tracked inside this class.
 */
class Player : public Character
{
public:
    /**
     * @brief The constructor for the player object.
     *
     * @param position The initial position of the Player object.
     * @param sprite The texture for the Players game object sprite.
     * @param speed The speed of that an Player can move with.
     * @param health The initial health of the Player object
     */
    Player(sf::Vector2f const& position, sf::Texture const& sprite, float const speed, int const health);

    /**
     * @brief Used to get the current level of the player.
     *
     * @return the current level.
     */
    int get_level() const;

    /**
     * @brief Used to get the current progress to the next level.
     *
     * @return The current levels percentage.
     */
    float get_level_percent() const;

    /**
     * @brief Gets the players health percentage (current_health/max_health)
     *
     * @return The health percentage
     */
    float get_health_percent() const;

    /**
     * @brief Used by the HUD to get information about the players current weapon.
     *
     * @return A shared pointer to the weapon that the player is currently wielding.
     */
    std::shared_ptr<Weapon>& get_weapon_stats();

    /**
     * @brief Updates the players position, keeps track of health and manages keypresses by the user.
     *
     * @param delta_time The time since the update function was last called.
     * @param world A reference to the world instance which the player exists in.
     * @param current_obj A shared pointer to the player object as stored in the current world instance.
     */
    void update(sf::Time const& delta_time, World & world, std::shared_ptr<Game_Object> const& current_obj) override;

    /**
     * @brief Handles collision events involving the Player by pushing the player back in the opposite vector direction
     * when compared to it's movement.
     *
     * @param world Reference to the game world.
     * @param current_obj Shared pointer to the current game object.
     * @param other_obj Shared pointer to the other game object involved in the collision.
     */
    void handle_collision(World & world, std::shared_ptr<Game_Object> const& current_obj, std::shared_ptr<Game_Object> const& other_obj) override;

    /**
     * @brief increases the amount of ammunition that the relevant weapon has of the matching ammo with its weapon.
     *
     * @param ammo_type The Ammo type that is to be added.
     * @param amount The amount that it should increase
     */
    void add_ammo(std::string const& ammo_type, int const amount);

    /**
     * @brief Used to add health points to the player.
     *
     * @param amount The amount of health points to be added to the player.
     */
    void add_health(int const amount);

    /**
     * @brief Used to add xp to the players xp-amount.
     *
     * @param xp The amount of xp to be added.
     * @param world A reference to the world instance of which the player exists in.
     */
    void add_player_xp(int const xp, World & world);

private:
    /**
     * @brief This parameter represents the percentage of player health remaining for the player.
     */
    int max_health{100};

    /**
     * This parameter represents the current player level.
     */
    int player_level{0};

    /**
     * This parameter represents the xp that the player currently has.
     */
    int player_level_progression{0};

    /**
     * The amount of xp needed to progress to the next player level.
     */
    int xp_to_level{20};

    /**
     * The health percentage of the player.
     */
    float health_percent{100};

    /**
     * This parameter represents the percentage progress the player has to his next level.
     */
    float level_percent{0};

    /**
     * Levels up the player to the next level
     *
     * @param world A reference to the world instance of which the player exists in.
     */
    void level_up_player(World & world);

    /**
     * @brief Adds a weapon to the player based on it's level
     * @param world A reference to the world instance of which the player exists in.
     */
    void add_player_weapon(World & world);
};

#endif
