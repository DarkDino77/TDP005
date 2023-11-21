#include "visual.h"
#include "entity.h"
#include "world.h"
#include "texture_manager.h"
#include "random.h"

Textured::Textured(const string &texture) {
    sf::Texture *t = Texture_Manager::get(texture);
    auto size = t->getSize();
    shape.setSize(sf::Vector2f(size.x, size.y));
    shape.setTexture(t);
    shape.setOrigin(size.x / 2, size.y / 2);
}

void Textured::added(Entity &to) {
    auto size = shape.getTexture()->getSize();
    to.radius = max(size.x, size.y) / 2.0f;
}

void Textured::render(sf::RenderWindow &window, Entity &to) {
    shape.setPosition(to.center);
    window.draw(shape);
}


Shield::Shield(Tag for_type) : for_type{for_type} {
    shield.setFillColor(sf::Color(255, 0, 0, 128));
}

bool Shield::tick(sf::Time time, Entity &entity, World &world) {
    shield_visible -= time;
    if (shield_visible <= sf::Time{}) {
        shield_visible = sf::Time{};

        // Don't check for collisions if the shield is up.
        for (auto &collision : world.collides_with(entity)) {
            if (collision->type == for_type)
                shield_visible = sf::milliseconds(1000);
        }
    }

    return true;
}

void Shield::render(sf::RenderWindow &window, Entity &to) {
    if (shield_visible > sf::Time{}) {
        shield.setRadius(to.radius * 2);
        shield.setOrigin(to.radius * 2, to.radius * 2);
        shield.setPosition(to.center);
        window.draw(shield);
    }
}


Particles::Particles(size_t spawn, float distance, sf::Time live, sf::Color color)
    : spawn{spawn}, distance{distance}, live{live}, color{color} {}

bool Particles::tick(sf::Time time, Entity &entity, World &) {
    float advance = time.asMicroseconds() / float(live.asMicroseconds());

    // Update all particles.
    size_t to = 0;
    for (auto &p : particles) {
        p.life += advance;
        if (p.life <= 1.0f)
            particles[to++] = p;
    }

    // Shrink.
    particles.resize(to);

    // Spawn new.
    for (size_t i = 0; i < spawn; i++) {
        float angle = 2 * M_PI * random_int(0, 36000) / 36000.0f;
        float dist = distance + distance/3 * random_int(0, 1000) / 1000.0f;
        Particle p = {
            entity.radius / dist,
            entity.center,
            sf::Vector2f(sin(angle), cos(angle)) * dist
        };
        particles.push_back(p);
    }

    return true;
}

void Particles::render(sf::RenderWindow &window, Entity &) {
    vector<sf::Vertex> r(particles.size());

    for (size_t i = 0; i < r.size(); i++) {
        Particle &p = particles[i];

        sf::Vector2f pos = p.pos + p.delta*p.life;
        sf::Color c = color;
        c.a = (1.0f - p.life)*255.0f;
        r[i] = sf::Vertex(pos, c);
    }

    window.draw(&r[0], r.size(), sf::PrimitiveType::Points);
}
