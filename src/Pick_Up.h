#ifndef PICK_UP_H
#define PICK_UP_H

#include "Collidable.h"
#include "Player.h"

/**
 * @class Pick_Up
 * @brief This class represents an item that the player should be able to acquire on the ground.
 */
class Pick_Up : public Collidable
{
public:
    /**
     * @brief This is the constructor for a Pick_Up object.
     * @param position The position of the Pick_Up object.
     * @param sprite The texture that is used to render the Pick_Up object.
     */
    Pick_Up(sf::Vector2f const& position, sf::Texture const& sprite);

    /**
      * @brief this is the default destructor for a Pick_Up.
      */
    virtual ~Pick_Up() = default;

    /**
      * @brief Updates the state of the Pick_Up object.
      */
    void update(sf::Time const&, World &, std::shared_ptr<Game_Object> const&) override;

    /**
     * @brief Handles collision of the Pick_Up object.
     */
    void handle_collision(World &, std::shared_ptr<Game_Object> const&, std::shared_ptr<Game_Object> const&) override;

protected:
    /**
     * A internal bool parameter that specifies whether or not a PicK_Up object ha been picked up or not.
     */
    bool picked_up{false};

    /**
     * @brief A pure virtual function that specifies what should happen when a
     * Sub_class to Pick_Up is to be picked_up by the player
     * @param other_obj
     */
    virtual void pick_up(std::shared_ptr<Game_Object> const& other_obj) const = 0;
};


#endif
