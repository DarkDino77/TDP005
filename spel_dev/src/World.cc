#include <SFML/Graphics.hpp>
#include "point.h"
#include "standard.h"
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

void World::add_game_object(std::string const& name,  sf::Vector2f position)
{
    float pos_x{8.0f*sprite_scale + position.x*16.0f*sprite_scale};
    float pos_y{8.0f*sprite_scale + position.y*16.0f*sprite_scale};
    std::shared_ptr<Game_Object> game_obj = std::shared_ptr<Game_Object>(new Game_Object({pos_x,pos_y}, *sprites[name], false));


    game_objects.push_back(game_obj);
}

void World::add_player(sf::Vector2f position)
{
    float pos_x{8.0f*sprite_scale + position.x*16.0f*sprite_scale};
    float pos_y{8.0f*sprite_scale + position.y*16.0f*sprite_scale};
    std::shared_ptr<Game_Object> player_obj = std::shared_ptr<Game_Object>(new Player({pos_x,pos_y}, *sprites["player"], false));

    game_objects.push_back(player_obj);

    player = std::dynamic_pointer_cast<Player>(player_obj);
}

std::shared_ptr<Player> World::get_player()
{
    return player;
};
bool contains(const sf::CircleShape &c, const sf::Vector2f &p){
    sf::Vector2f center = c.getPosition();
    float a = (p.x - center.x);
    float b = (p.y - center.y);
    a *= a;
    b *= b;
    float r = c.getRadius() * c.getRadius();

    return (( a + b ) < r);
}
bool tri_rect_intersects(const sf::CircleShape &c, const sf::RectangleShape &r){
    sf::FloatRect fr = r.getGlobalBounds();
    sf::Vector2f topLeft(fr.left, fr.top);
    sf::Vector2f topRight(fr.left + fr.width, fr.top);
    sf::Vector2f botLeft(fr.left, fr.top + fr.height);
    sf::Vector2f botRight(fr.left + fr.width, fr.top + fr.height);

    return contains(c, topLeft) ||
           contains(c, topRight) ||
           contains(c, botLeft) ||
           contains(c, botRight);
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
    /*sf::Texture texture;
    texture.loadFromFile("textures/player.png");

    sf::Vector2f textureSize{texture.getSize()};
    sf::RectangleShape player{textureSize};
    player.setTexture(&texture);
    player.setOrigin(textureSize / 2.0f);
    player.setScale(sprite_scale,sprite_scale);*/


    // ==============================[ TEST ]==============================
    World world{};

    world.add_texture("wall", "textures/wall.png");
    world.add_texture("crate", "textures/crate.png");
    world.add_texture("barrel", "textures/barrel.png");
    world.add_texture("player", "textures/player.png");

    world.add_game_object("wall",{1,1});
    world.add_game_object("wall",{4,1});
    world.add_game_object("wall",{7,1});
    world.add_game_object("wall",{10,1});
    world.add_game_object("wall",{2,4});
    world.add_game_object("wall",{5,4});
    world.add_game_object("wall",{8,4});
    world.add_game_object("wall",{11,4});
    world.add_game_object("wall",{28,14});
    world.add_game_object("wall",{25,14});
    world.add_game_object("wall",{22,14});
    world.add_game_object("wall",{19,14});
    world.add_game_object("crate", {10,3});
    world.add_game_object("crate",{9,14});
    world.add_game_object("crate",{28,12});
    world.add_game_object("barrel", {14, 7});
    world.add_game_object("wall",{15,7});

    world.add_game_object("wall",{27,1});
    world.add_game_object("wall",{28,1});
    world.add_game_object("wall",{28,2});

    world.add_game_object("wall",{1,13});
    world.add_game_object("wall",{1,14});
    world.add_game_object("wall",{2,14});

    world.add_player({20,20});
    sf::Vector2f location{world.get_player()->shape.getPosition()};

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

        world.get_player()->shape.setRotation((rotate_degrees*180/3.1415f) - 90.f);


        if (quit)
            break;

        sf::Vector2f direction = find_direction();
        world.get_player()->direction = direction;

        auto delta = clock.restart();
        {
            float distance = 250.0f * delta.asSeconds() * player_speed;
            location += direction * distance;
        }

        mouse_cursor.setPosition(mouse_pos);

        window.clear();
        window.draw(background_sprite);
        world.get_player()->shape.setPosition(location);
        world.get_player()->collision_shape.setPosition(location);

        // Collision handling
        for(std::shared_ptr<Game_Object> obj : world.game_objects)
        {
            std::shared_ptr<Movable> current_obj{std::dynamic_pointer_cast<Movable>(obj)};
            if(current_obj != nullptr)
            {
                for(std::shared_ptr<Game_Object> collide_obj : world.game_objects) {
                    const bool collides = (obj != collide_obj && (current_obj->collision_shape).getGlobalBounds().intersects((collide_obj->shape).getGlobalBounds()) );
                    //const bool collides = (obj != collide_obj && tri_rect_intersects(current_obj->collision_shape, collide_obj->shape));

                    if(collides)
                    {
                       std::cout << "Player direction: x" << world.get_player()->direction.x << ", y" << world.get_player()->direction.x << std::endl;
                       sf::Vector2f push_direction{};
                       bool collision_x{
                           (world.get_player()->direction.y == 0)
                           &&
                           (std::abs(collide_obj->shape.getPosition().y - world.get_player()->collision_shape.getPosition().y) <= (collide_obj->shape.getSize().y/2.0f))
                       };
                       std::cout << "X-difference: " << std::abs(collide_obj->shape.getPosition().x - world.get_player()->collision_shape.getPosition().x) << std::endl;
                       std::cout << "X-size / 2: " << collide_obj->shape.getSize().x/2.0f << std::endl;

                       bool collision_y{
                           (world.get_player()->direction.x == 0)
                           &&
                           (std::abs(collide_obj->shape.getPosition().x - world.get_player()->collision_shape.getPosition().x) < (collide_obj->shape.getSize().x/2.0f))

                       };
                        std::cout << collision_y << std::endl;
                       if(collision_x || collision_y)
                       {
                           std::cout << "Collision passed" << std::endl;
                           push_direction = (-direction);
                       }
                       else
                       {
                           // 1. beräkna riktningsvektor från vägg till spelare.
                           push_direction = normalize(obj->get_collision_shape().getPosition() - collide_obj->get_collision_shape().getPosition());
                       }

                        float temp_increment{0.005f};
                        // 2. Tryck spelaren, i inkrement i samma riktning tills collision är falskt.
                        while ((obj->get_collision_shape()).getGlobalBounds().intersects((collide_obj->get_collision_shape()).getGlobalBounds()) ) {
                            obj->get_collision_shape().setPosition(obj->get_collision_shape().getPosition() + push_direction * temp_increment);
                            location += push_direction * temp_increment;
                        }
                    }
                }
            }
        }

        for(std::shared_ptr<Game_Object> obj : world.game_objects)
        {
            obj -> render(window);
        }
        window.draw(mouse_cursor);
        window.display();
    }

    return 0;
}