#include "game_object.h"
#include "texture_manager.h"

Textured_Object::Textured_Object(sf::Vector2f center, const string &texture)
    : Game_Object(center, 0.0f) {

    sf::Texture *t = Texture_Manager::get(texture);
    auto size = t->getSize();
    shape.setSize(sf::Vector2f(size.x, size.y));
    shape.setTexture(t);
    shape.setOrigin(size.x / 2, size.y / 2);
    radius = max(size.x, size.y) / 2.0f;
}

void Textured_Object::render(sf::RenderWindow &window) {
    shape.setPosition(center);
    window.draw(shape);
}
