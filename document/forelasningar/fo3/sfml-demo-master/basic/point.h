#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

inline float length(const sf::Vector2f &v) {
    return sqrt(v.x*v.x + v.y*v.y);
}

inline sf::Vector2f normalize(const sf::Vector2f &v) {
    float len = length(v);
    if (len <= 0.0f)
        return sf::Vector2f{0, 0};
    else
        return v * (1.0f/len);
}
