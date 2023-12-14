#include "world.h"

void World::tick(sf::Time delta) {
    // Note: We cannot use iterators here as some of the objects might want to
    // add new entities while we are iterating in this loop. Therefore, we use
    // indices instead.

    for (size_t i = 0; i < objects.size(); i++) {
        if (!objects[i]->tick(delta, *this)) {
            // Remove this element.
            objects.erase(objects.begin() + i);
            i--;
        }
    }
}

void World::render(sf::RenderWindow &to) {
    for (auto &x : objects)
        x->render(to);
}

void World::add(shared_ptr<Entity> object) {
    objects.push_back(object);
}

static bool collides(Entity &a, Entity &b) {
	auto distance = a.center - b.center;
	// Calculate the lenght of "distance", squared (calling sqrt is expensive, and we don't actually need that).
	auto lengthSq = pow(distance.x, 2) + pow(distance.y, 2);
	return lengthSq <= pow(a.radius + b.radius, 2);

	// Note: If we're working with bounding boxes instead of circles. We can consider the 'x' and
	// 'y' axes separately, and arrive at something like this:
	// return (a.left < b.right && a.right > b.left)  // x-axis
	//     && (a.top < b.bottom && a.bottom > b.top)  // y-axis
}

vector<shared_ptr<Entity>> World::collides_with(Entity &me) const {
    vector<shared_ptr<Entity>> result;

    for (auto &x : objects) {
        // Don't collide with yourself.
        if (x.get() == &me)
            continue;

        if (collides(*x, me))
            result.push_back(x);
    }

    return result;
}
