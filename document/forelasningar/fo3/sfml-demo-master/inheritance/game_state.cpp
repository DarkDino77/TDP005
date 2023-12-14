#include "game_state.h"
#include "menu_state.h"
#include "player.h"
#include "enemy.h"
#include "random.h"

Game_State::Game_State() {
    world.add(std::make_shared<Player>(sf::Vector2f{width / 2.0f, height * 4.0f / 5.0f}));
}

shared_ptr<State> Game_State::tick(sf::Time delta) {
    // Create new enemies from time to time.
	if (random_int(0, 100) < 7) {
		float x = float(random_int(0, width));
        world.add(std::make_shared<Spawner>(x, random_int(3000, 4000)));
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
