#ifndef HUD_H
#define HUD_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Updatable.h"
#include "Resource_Manager.h"

class Weapon;
class World;
/**
 * @class Hud
 * @brief This class represent the heads up display that provieds the player with relevent information. Inherents from
 * Updatable.
 */
class Hud : public Updatable
{
public:
    /**
     * @brief This is the constructor for the HUD
     * @param sprite A texture representing the sprite for the HUD
     * @param world A copy of world
     */
    Hud(sf::Texture const& sprite, World & world);

    /**
     *@brief This is the update function for the hud it updates the different information that the hud is displaying to
     * be keep up with the reality of the game as it currently is.
     */
    void update(sf::Time const&, World &, std::shared_ptr<Game_Object> const&) override;

    /**
     * @brief This loads the hud based on the starting world information as well as the font for the relevant text hud
     * features.
     * @param world A copy of world
     */
    void load_hud(World & world);

    /**
     * @brief This Function draws its relevant information to the window
     * @param window a reference copy of the window that the game run in
     */
    void render(sf::RenderWindow & window) override;

    /**
     * @brief This Function adds a message to be displayed on the screen on a temporary time frame.
     * @param message This is the relevant massage to be displayed on the screen.
     */
    void pop_up(std::string const& message);

private:
    /**
     * This parameter represents the current player level.
     */
    int player_level{0};

    /**
     * This parameter represents the percentage progress the player has to his next level.
     */
    float level_percent{0};

    /**
     * This parameter represents the percentage of player health remaining for the player.
     */
    float health_percent{100};

    /**
     * This variable represents the amount of time the pop_up has been around
     */
    float time_since_pop_up{0};

    /**
     * This represents whether or not there is a pop up visible on the screen
     */
    bool is_pop_up_visible{false};

    /**
     * This vector represents all the non_text elements tide to the hud
     */
    std::vector<std::shared_ptr<sf::RectangleShape>> hud_elements{};

    /**
     * This vector represents all the text items relevant to the HUD
     */
    std::vector<std::shared_ptr<sf::Text>> hud_texts{};

    /**
     * This vector represents all the texts that need to be displayed by pop_up to the player
     */
    std::vector<std::string> pop_up_queue{};
};

#endif
