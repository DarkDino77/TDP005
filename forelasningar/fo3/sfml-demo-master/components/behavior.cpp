#include "behavior.h"
#include "world.h"
#include "entity.h"

Player_Control::Player_Control(float speed) : speed{speed} {}

static sf::Vector2f find_direction() {
    sf::Vector2f direction;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        direction.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        direction.y += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        direction.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        direction.x += 1;

    float len = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
    if (len > 0.0f)
        return direction * (1.0f / len);
    else
        return direction;
}

bool Player_Control::tick(sf::Time time, Entity &entity, World &) {
    sf::Vector2f dir = find_direction();
    entity.center += dir * (speed * time.asMicroseconds() / 1000000.0f);
    return true;
}

bool Remove_Outside::tick(sf::Time, Entity &entity, World &) {
    if (entity.center.x < -margin)
        return false;
    if (entity.center.x > width + margin)
        return false;
    if (entity.center.y < -margin)
        return false;
    if (entity.center.y > height + margin)
        return false;
    return true;
}


Spawn::Spawn(sf::Time interval, std::function<shared_ptr<Entity>(Entity &)> create)
    : create{create}, spawn_interval{interval}, remaining{interval} {}

bool Spawn::tick(sf::Time delta, Entity &entity, World &world) {
    remaining -= delta;
    if (remaining <= sf::Time{}) {
        world.add(create(std::ref(entity)));
        remaining += spawn_interval;
    }
    return true;
}


Sine_Movement::Sine_Movement(float x, sf::Time duration)
    : cumulated_time{}, lifetime{duration}, x{x} {}

bool Sine_Movement::tick(sf::Time delta, Entity &entity, World &) {
    float t = float(cumulated_time.asMicroseconds()) / float(lifetime.asMicroseconds());
	entity.center.y = height * t;

	float amplitude = 1.0f - t;
	entity.center.x = x + sin((t + x / width) * 12) * amplitude * width / 4.0f;
	if (x > width / 2) {
		entity.center.x += (width - x) * t;
	} else {
		entity.center.x -= x * t;
	}

	if (t >= 1.0f)
		return false;

	cumulated_time += delta;
	return true;
}


bool Down_Movement::tick(sf::Time delta, Entity &entity, World &) {
    entity.center.y += speed * delta.asMicroseconds() / 1000000.0f;
    return true;
}


bool Down_Center_Movement::tick(sf::Time delta, Entity &entity, World &) {
    sf::Vector2f heading = sf::Vector2f(width / 2, height + 15) - entity.center;
    float length = sqrt(pow(heading.x, 2) + pow(heading.y, 2));
    if (length > 1.0f)
        heading = heading * (1.0f / length);
    else
        return false;

    entity.center += heading * (speed * delta.asMicroseconds() / 1000000.0f);

    return true;
}
