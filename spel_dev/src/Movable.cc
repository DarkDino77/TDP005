#include "Movable.h"

Movable::Movable(sf::Vector2f position, sf::Texture const& sprite, float speed)
: Game_Object(position, sprite), speed{speed}
{
    collision_shape.setRadius(shape.getSize().x*0.9f);
    collision_shape.setOrigin({collision_shape.getRadius(),collision_shape.getRadius()});
    collision_shape.setPosition(shape.getPosition());
    collision_shape.setFillColor(sf::Color::Red);
}