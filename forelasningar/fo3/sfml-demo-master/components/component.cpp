#include "component.h"

void Component::added(Entity &) {}

bool Component::tick(sf::Time, Entity &, World &) { return true; }

void Component::render(sf::RenderWindow &, Entity &) {}
