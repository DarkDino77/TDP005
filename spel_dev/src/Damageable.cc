#include "Damageable.h"

Damageable::Damageable(int health)
: health{health}
{}

void Damageable::take_damage(int damage)
{
    health -= damage;
}
