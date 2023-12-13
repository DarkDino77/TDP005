#include "Damageable.h"

void Damageable::take_damage(int damage)
{
    hit = true;
    health -= damage;
}

Damageable::Damageable(int const health)
        : health{health}
{}