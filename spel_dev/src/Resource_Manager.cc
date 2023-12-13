#include <iostream>
#include <random>
#include <fstream>
#include "Resource_Manager.h"
#include "World.h"

Resource_Manager::Resource_Manager()
{
    load();
}

sf::Texture& Resource_Manager::get_sprite(std::string const& category)
{
    if(sprites[category].empty())
    {
        std::cerr << "Error: A sprite in the category '" << category << "' was never added to world." << std::endl;
        return *sprites["error"].at(0);
    }

    std::random_device rd;
    std::uniform_int_distribution<int> rd_uniform(1,int(sprites[category].size()));
    int sprite_index{(rd_uniform(rd)-1)};

    return *sprites[category].at(sprite_index);
}

sf::Font& Resource_Manager::get_font()
{
    return font;
}

sf::Sprite& Resource_Manager::get_background_sprite()
{
    return background_sprite;
}

sf::Texture& Resource_Manager::get_mouse_cursor_texture()
{
    return mouse_cursor_texture;
}

void Resource_Manager::play_sound(std::string const& name)
{
    if(sounds[name].empty())
    {
        std::cerr << "Error: Sound with name '" << name << "' was never added to world." << std::endl;
        return;
    }

    std::random_device rd;
    std::uniform_int_distribution<int> rd_uniform(1,int(sound_buffers[name].size()));
    int track_index{(rd_uniform(rd)-1)};

    sounds[name].at(track_index)->play();
}

// ==============================[ Load ]==============================
void Resource_Manager::load()
{
    load_font();
    // ==============================[ Background ]==============================
    load_background();

    // ==============================[ Cursor ]==============================
    load_cursor();

    // ==============================[ Create World ]==============================
    load_textures();

    // ==============================[ Add audio ]==============================
    load_audio();

    sf::Music music;
    if (!music.openFromFile("audio/music.ogg"))
    {
        std::cerr << "Error: Could not find music with filename 'audio/music.ogg'." << std::endl;
        return;
    }
    music.play();
}

void Resource_Manager::load_font()
{
    if(!font.loadFromFile("res/font3.ttf"))
    {
        std::cerr << "Could not load font" << std::endl;
    }
}

void Resource_Manager::load_background()
{
    background_texture.loadFromFile("textures/background.png");
    background_sprite.setTexture(background_texture);
}

void Resource_Manager::load_cursor()
{
    mouse_cursor_texture.loadFromFile("textures/crosshair.png");


}

void Resource_Manager::load_textures()
{
    // Map objects
    add_texture("error", "textures/error.png");
    add_texture("wall", "textures/wall_1.png");
    add_texture("wall", "textures/wall_2.png");
    add_texture("crate", "textures/crate.png");
    add_texture("explosive_barrel", "textures/explosive_barrel.png");

    // Characters
    add_texture("player", "textures/player.png");
    add_texture("melee", "textures/zombie1.png");
    add_texture("melee", "textures/zombie2.png");
    add_texture("melee", "textures/zombie3.png");
    add_texture("melee4", "textures/zombie4.png");
    add_texture("melee5", "textures/zombie5.png");
    add_texture("melee6", "textures/zombie6.png");
    add_texture("melee7", "textures/zombie7.png");
    add_texture("spitter", "textures/spitter1.png");
    add_texture("spitter", "textures/spitter2.png");
    add_texture("biter", "textures/biter1.png");
    add_texture("biter", "textures/biter2.png");
    add_texture("boss", "textures/zombie_boss1.png");
    add_texture("boss", "textures/zombie_boss2.png");

    // Weapons
    add_texture("spitter_bullet", "textures/spitter_bullet.png");
    add_texture("explosion", "textures/explosion.png");
    add_texture("glock_bullet", "textures/glock_bullet.png");
    add_texture("baretta_bullet", "textures/baretta_bullet.png");
    add_texture("uzi_bullet", "textures/uzi_bullet.png");
    add_texture("shotgun_bullet", "textures/shotgun_bullet.png");
    add_texture("assault_rifle_bullet", "textures/assault_rifle_bullet.png");
    add_texture("sniper_rifle_bullet", "textures/sniper_rifle_bullet.png");
    add_texture("baretta_ammo", "textures/baretta_ammo.png");
    add_texture("uzi_ammo", "textures/uzi_ammo.png");
    add_texture("shotgun_ammo", "textures/shotgun_ammo.png");
    add_texture("assault_rifle_ammo", "textures/assault_rifle_ammo.png");
    add_texture("sniper_rifle_ammo", "textures/sniper_rifle_ammo.png");

    add_texture("health_drop", "textures/health_pick_up.png");

    // HUD
    add_texture("hud", "textures/hud.png");
    add_texture("hud_level", "textures/hud_level.png");
    add_texture("hud_health", "textures/hud_health.png");
    add_texture("hud_health_fill", "textures/hud_health_fill.png");
    add_texture("hud_level_fill", "textures/hud_level_fill.png");
    add_texture("hud_weapon_background", "textures/hud_weapon_background.png");
    add_texture("glock_hud", "textures/glock_hud.png");
    add_texture("baretta_hud", "textures/baretta_hud.png");
    add_texture("uzi_hud", "textures/uzi_hud.png");
    add_texture("shotgun_hud", "textures/shotgun_hud.png");
    add_texture("assault_rifle_hud", "textures/assault_rifle_hud.png");
    add_texture("sniper_rifle_hud", "textures/sniper_rifle_hud.png");
}

void Resource_Manager::load_audio()
{
    // Weapons
    add_sound("glock_shoot", "audio/glock_shoot_1.wav");
    add_sound("glock_shoot", "audio/glock_shoot_2.wav");
    add_sound("baretta_shoot", "audio/baretta_shoot_1.wav");
    add_sound("baretta_shoot", "audio/baretta_shoot_2.wav");
    add_sound("uzi_shoot", "audio/uzi_shoot_1.wav");
    add_sound("uzi_shoot", "audio/uzi_shoot_2.wav");
    add_sound("uzi_shoot", "audio/uzi_shoot_3.wav");
    add_sound("shotgun_shoot", "audio/shotgun_shoot_1.wav");
    add_sound("shotgun_shoot", "audio/shotgun_shoot_2.wav");
    add_sound("shotgun_shoot", "audio/shotgun_shoot_3.wav");
    add_sound("assault_rifle_shoot", "audio/assault_rifle_shoot_1.wav");
    add_sound("assault_rifle_shoot", "audio/assault_rifle_shoot_2.wav");
    add_sound("assault_rifle_shoot", "audio/assault_rifle_shoot_3.wav");
    add_sound("sniper_rifle_shoot", "audio/sniper_rifle_shoot_1.wav");
    add_sound("sniper_rifle_shoot", "audio/sniper_rifle_shoot_2.wav");
    add_sound("sniper_rifle_shoot", "audio/sniper_rifle_shoot_3.wav");
    add_sound("spitter_shoot", "audio/spitter_shoot.wav");
    add_sound("ammo_pick_up", "audio/ammo_pick_up.wav");

    // Player
    add_sound("player_hurt", "audio/player_hurt_1.wav");
    add_sound("player_hurt", "audio/player_hurt_2.wav");
    add_sound("player_hurt", "audio/player_hurt_3.wav");
    add_sound("player_hurt", "audio/player_hurt_4.wav");

    // Enemy
    add_sound("enemy_hurt", "audio/enemy_hurt_1.wav");
    add_sound("enemy_hurt", "audio/enemy_hurt_2.wav");
    add_sound("enemy_hurt", "audio/enemy_hurt_3.wav");
    add_sound("enemy_hurt", "audio/enemy_hurt_4.wav");

    // Other
    add_sound("explosion", "audio/explosion.wav");
    add_sound("crate_destroy", "audio/crate_destroy.wav");
    add_sound("bullet_impact", "audio/bullet_impact_1.wav");
    add_sound("bullet_impact", "audio/bullet_impact_2.wav");
    add_sound("bullet_impact", "audio/bullet_impact_3.wav");
}

void Resource_Manager::add_texture(std::string const& category, std::string const& filename)
{
    auto texture = std::make_shared<sf::Texture>();
    if(!texture->loadFromFile(filename))
    {
        std::cerr << "Error: Could not find image with name '" << filename << "'." << std::endl;
    }
    else
    {
        sprites[category].push_back(texture);
    }
}

void Resource_Manager::add_sound(std::string const& category,  std::string const& filename)
{
    auto sound_buffer = std::make_shared<sf::SoundBuffer>();
    if (!sound_buffer->loadFromFile(filename))
    {
        std::cerr << "Error: Could not find file with name '" << filename << "'." << std::endl;
    }
    else
    {
        sound_buffers[category].push_back(sound_buffer);
        std::shared_ptr<sf::Sound> sound{std::make_shared<sf::Sound>()};
        sound->setBuffer(*sound_buffers[category].back());
        sounds[category].push_back(sound);
    }
}