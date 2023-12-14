#include "player.h"
#include "visual.h"
#include "behavior.h"

shared_ptr<Entity> create_player() {
    shared_ptr<Entity> e = std::make_shared<Entity>(sf::Vector2f(width / 2, height * 4 / 5));

    e->type = Tag::player;

    // e->add(std::make_shared<Particles>(10, 70.0f, sf::milliseconds(800), sf::Color::Red));

    e->add(std::make_shared<Textured>("player.png"));
    e->add(std::make_shared<Player_Control>(300.0f));
    e->add(std::make_shared<Shield>(Tag::enemy));

    // e->add(std::make_shared<Remove_Outside>(5.0f));

    return e;
}
