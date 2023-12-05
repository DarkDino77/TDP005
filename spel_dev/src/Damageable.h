#ifndef DAMAGEABLE_H
#define DAMAGEABLE_H

class Damageable {
public:
    Damageable(int health);
    virtual ~Damageable() = default;
    void take_damage(int damage);
protected:
    int health{};
};


#endif
