#include "enemy.h"
#include "world.h"
#include "random.h"

Spawner::Spawner(float x, size_t lifetime)
    : Enemy(sf::Vector2f{x, 0}, "green.png"), cumulated_time{},
      lifetime{sf::milliseconds(lifetime)}, until_spawn{sf::milliseconds(500)}, x{x} {}

bool Spawner::tick(sf::Time delta, World &world) {
	float t = float(cumulated_time.asMilliseconds()) / float(lifetime.asMilliseconds());
	center.y = height * t;

	float amplitude = 1.0f - t;
	center.x = x + sin((t + x / width) * 12) * amplitude * width / 4.0f;
	if (x > width / 2) {
		center.x += (width - x) * t;
	} else {
		center.x -= x * t;
	}

	if (t >= 1.0f)
		return false;

    until_spawn -= delta;
    if (until_spawn < sf::Time{}) {
        world.add(std::make_shared<Bullet>(center));
        until_spawn = sf::milliseconds(random_int(400, 900));
    }

	cumulated_time += delta;
	return true;
}


Bullet::Bullet(sf::Vector2f position)
    : Enemy(position, "bullet.png"), speed(250.0f) {

    direction.y = 1.0f;
    if (random_int(0, 2) == 1) {
        direction.x = (center.x - (width / 2)) / (center.y - height);

        direction = direction * float(1.0 / sqrt(pow(direction.x, 2) + pow(direction.y, 2)));
    }
}

bool Bullet::tick(sf::Time delta, World &) {
    center += direction * (speed * delta.asMicroseconds() / 1000000.0f);

    if (center.y > height)
        return false;
    return true;
}
