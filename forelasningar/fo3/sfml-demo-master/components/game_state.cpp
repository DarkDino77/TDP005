#include "game_state.h"
#include "menu_state.h"
#include "random.h"
#include "player.h"
#include "enemy.h"

Game_State::Game_State() {
    world.add(create_player());
}

shared_ptr<State> Game_State::tick(sf::Time delta) {
    // Create new enemies from time to time.
	if (random_int(0, 100) < 7) {
        world.add(create_enemy());
	}

    world.tick(delta);

    // Pause?
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        return std::make_shared<Menu_State>(shared_from_this());

    return nullptr;
}

void Game_State::render(sf::RenderWindow &to) {
    world.render(to);
}
