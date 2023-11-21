#include "entity.h"
#include "component.h"

bool Entity::tick(sf::Time time, World &world) {
    bool live = true;
    for (auto &x : components) {
        live &= x->tick(time, *this, world);
    }
    return live;
}

void Entity::render(sf::RenderWindow &window) {
    for (auto &x : components) {
        x->render(window, *this);
    }
}

void Entity::add(shared_ptr<Component> component) {
    component->added(*this);
    components.push_back(std::move(component));
}
