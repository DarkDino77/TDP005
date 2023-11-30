#include <SFML/Graphics.hpp>
#include "point.h"
#include "standard.h"
#include "Player.h"
#include "World.h"
#include <cmath>

// TEMP v
#include <vector>
#include <memory>

const size_t width = 1920;
const size_t height = 1024;

sf::Vector2f find_direction() {
    sf::Vector2f direction;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        direction.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        direction.y += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        direction.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        direction.x += 1;

    return normalize(direction);
}

void World::add_texture(std::string name, std::string filename)
{
    std::shared_ptr<sf::Texture> texture = std::shared_ptr<sf::Texture>(new sf::Texture());

    texture -> loadFromFile(filename);
    sprites[name] = texture;
}

void World::add_wall(sf::Vector2f position)
{
    float pos_x{8.0f*sprite_scale + position.x*16.0f*sprite_scale};
    float pos_y{8.0f*sprite_scale + position.y*16.0f*sprite_scale};
    std::shared_ptr<Game_Object> wall = std::shared_ptr<Game_Object>(new Game_Object({pos_x,pos_y}, *sprites["wall"], false));

    game_objects.push_back(wall);
}

void World::add_crate(sf::Vector2f position)
{
    float pos_x{8.0f*sprite_scale + position.x*16.0f*sprite_scale};
    float pos_y{8.0f*sprite_scale + position.y*16.0f*sprite_scale};
    std::shared_ptr<Game_Object> crate = std::shared_ptr<Game_Object>(new Game_Object({pos_x,pos_y}, *sprites["crate"], false));

    game_objects.push_back(crate);
}

void World::add_barrel(sf::Vector2f position)
{
    float pos_x{8.0f*sprite_scale + position.x*16.0f*sprite_scale};
    float pos_y{8.0f*sprite_scale + position.y*16.0f*sprite_scale};
    std::shared_ptr<Game_Object> barrel = std::shared_ptr<Game_Object>(new Game_Object({pos_x,pos_y}, *sprites["barrel"], false));

    game_objects.push_back(barrel);
}

void World::add_player(sf::Vector2f position)
{
    float pos_x{8.0f*sprite_scale + position.x*16.0f*sprite_scale};
    float pos_y{8.0f*sprite_scale + position.y*16.0f*sprite_scale};
    std::shared_ptr<Game_Object> player = std::shared_ptr<Game_Object>(new Player({pos_x,pos_y}, *sprites["barrel"], false));

    game_objects.push_back(player);
}

int main() {
    sf::RenderWindow window{sf::VideoMode{width, height}, "The Grand Arena"};
    window.setMouseCursorVisible(false);
    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(true);

    float sprite_scale{2.0f};

    // ==============================[ Background ]==============================
    sf::Texture background_texture;
    background_texture.loadFromFile("textures/background.png");

    sf::Vector2f background_texture_size{background_texture.getSize()};
    sf::Sprite background_sprite;
    background_sprite.setTexture(background_texture);

    // ==============================[ Cursor ]==============================
    sf::Texture mouse_cursor_texture;
    mouse_cursor_texture.loadFromFile("textures/crosshair.png");

    sf::Vector2f mouse_texture_size{mouse_cursor_texture.getSize()};
    sf::RectangleShape mouse_cursor{mouse_texture_size};
    mouse_cursor.setTexture(&mouse_cursor_texture);
    mouse_cursor.setOrigin(mouse_texture_size / 2.f);
    mouse_cursor.setScale(sprite_scale,sprite_scale);

    // ==============================[ Player ]==============================
    sf::Texture texture;
    texture.loadFromFile("textures/player.png");

    sf::Vector2f textureSize{texture.getSize()};
    sf::RectangleShape player{textureSize};
    player.setTexture(&texture);
    player.setOrigin(textureSize / 2.0f);
    player.setScale(sprite_scale,sprite_scale);
    sf::Vector2f location{300, 300};

    // ==============================[ TEST ]==============================
    World world{};

    world.add_texture("wall", "textures/wall.png");
    world.add_texture("crate", "textures/crate.png");
    world.add_texture("barrel", "textures/barrel.png");

    world.add_wall({1,1});
    world.add_wall({4,1});
    world.add_wall({7,1});
    world.add_wall({10,1});
    world.add_wall({2,4});
    world.add_wall({5,4});
    world.add_wall({8,4});
    world.add_wall({11,4});
    world.add_wall({28,14});
    world.add_wall({25,14});
    world.add_wall({22,14});
    world.add_wall({19,14});
    world.add_crate({10,3});
    world.add_crate({9,14});
    world.add_crate({28,12});
    world.add_barrel({14, 7});
    world.add_wall({15,7});

    world.add_wall({27,1});
    world.add_wall({28,1});
    world.add_wall({28,2});

    world.add_wall({1,13});
    world.add_wall({1,14});
    world.add_wall({2,14});
    world.add_player({40,20});

    // ==============================[ END TEST ]==============================
    double player_speed{1.0f};

    sf::Clock clock;

    // ==============================[ Game Loop ]==============================
    bool quit = false;
    while (!quit) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    quit = true;
                    break;
                default:
                    break;
            }
        }

        sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        sf::Vector2f rotate_direction = normalize(location - mouse_pos);

        float rotate_degrees = std::atan2(rotate_direction.y, rotate_direction.x);

        player.setRotation((rotate_degrees*180/3.1415f) - 90.f);


        if (quit)
            break;

        sf::Vector2f direction = find_direction();

        auto delta = clock.restart();
        {
            float distance = 250.0f * delta.asSeconds() * player_speed;
            location += direction * distance;
        }

        mouse_cursor.setPosition(mouse_pos);

        window.clear();
        window.draw(background_sprite);
        player.setPosition(location);
        window.draw(player);
        for(std::shared_ptr<Game_Object> obj : world.game_objects)
        {
            obj -> render(window);
        }
        for(std::shared_ptr<Game_Object> obj : world.game_objects)
        {

            if(std::dynamic_pointer_cast<Player>(obj) != nullptr)
            {
                for(std::shared_ptr<Game_Object> collide_obj : world.game_objects)
                {
                    if(collide_obj != obj && obj->shape.getGlobalBounds().intersects(collide_obj->shape.getGlobalBounds()))
                    {
                        std::cout << "COLLISION" << std::endl;
                    }
                }
                // Detect collision.
            }
        }
        window.draw(mouse_cursor);
        window.display();
    }

    return 0;
}