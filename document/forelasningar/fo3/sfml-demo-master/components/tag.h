#pragma once

/**
 * Tags for entities so that we can determine what type of object they are.
 */
enum class Tag : size_t {
    // Unknown entity.
    unknown,

    // This is a player.
    player,

    // This is an enemy.
    enemy,
};
