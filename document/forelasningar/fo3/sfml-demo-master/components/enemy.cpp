#include "enemy.h"
#include "visual.h"
#include "behavior.h"
#include "random.h"

static shared_ptr<Entity> create_bullet(Entity &from) {
    shared_ptr<Entity> e = std::make_shared<Entity>(from.center);

    e->type = Tag::enemy;

    e->add(std::make_shared<Particles>(10, 70.0f, sf::milliseconds(800), sf::Color::Yellow));
    e->add(std::make_shared<Textured>("bullet.png"));

    if (random_int(0, 2) == 1) {
        e->add(std::make_shared<Down_Movement>(250.0f));
    } else {
        e->add(std::make_shared<Down_Center_Movement>(250.0f));
    }

    // Remove them when they are outside of the screen.
    e->add(std::make_shared<Remove_Outside>(20.0f));

    // Add a shield, just to show that it is possible.
    // e->add(std::make_shared<Shield>(Tag::enemy));
    // e->add(std::make_shared<Shield>(Tag::player));

    return e;
}

shared_ptr<Entity> create_enemy() {
    shared_ptr<Entity> e = std::make_shared<Entity>(sf::Vector2f{});

    e->type = Tag::enemy;

    e->add(std::make_shared<Particles>(10, 80.0f, sf::milliseconds(1200), sf::Color::Green));
    e->add(std::make_shared<Textured>("green.png"));
    e->add(std::make_shared<Sine_Movement>(
            float(random_int(0, width)),
            sf::milliseconds(random_int(3000, 4000))));

    e->add(std::make_shared<Spawn>(sf::milliseconds(500), &create_bullet));

    return e;
}
