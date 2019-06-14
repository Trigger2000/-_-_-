//
//  Header.h
//  Game
//
//  Created by Илья  on 06/06/2019.
//  Copyright © 2019 Илья . All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

//--------------------------
class RGobjects
{
public:
    //virtual void draw();
    
protected:
    bool collision_detector = false;
    int x_, y_;
    float scale_;
    sf::Texture texture_;
    sf::FloatRect bounding_box_;
};
//--------------------------
class RGtext: RGobjects
{
public:
    RGtext(std::string content, float size, sf::Color colour, int pos_x, int pos_y);
    
    void upgrade(sf::RenderTexture& rendering, sf::Clock& timer);
    void draw(sf::RenderWindow& window);
    void change(sf::RenderWindow& window, std::string content, float size, sf::Color colour, int pos_x, int pos_y);
    
    void animation_big (float upper_limit, sf::RenderWindow& window, sf::Sprite background, sf::Keyboard::Key interrupter);
    void animation_small (float lower_limit, sf::RenderWindow& window, sf::Sprite background, sf::Keyboard::Key interrupter);
    void animation_big (float upper_limit, sf::RenderWindow& window, sf::Sprite background);
    void animation_small (float lower_limit, sf::RenderWindow& window, sf::Sprite background);
    void animation_fade (sf::RenderWindow& window, sf::Sprite background);
    
private:
    sf::Text text_;
    sf::Font Helvetica_;
    sf::Color colour_;
    std::string content_;
    
};
//--------------------------
class RGbullet: RGobjects
{
public:
    RGbullet(int parameter);
    
    void draw(sf::RenderTexture& renderinf, int sprite_num);
    void setPosition(int x, int y);
    void activate();
    void deactivate();
    bool check();
    void set_start (int position_x, int position_y);
    int& get_x();
    int& get_y();
    int get_start_x();
    int get_start_y();
    int get_direction();
    
private:
    int start_position_x_, start_position_y_;
    bool status_ = false;
    int direction_;
    sf::Sprite bullet1_;
    sf::Sprite bullet2_;
    sf::Sprite bullet3_;
    sf::Sprite bullet4_;
};
//--------------------------
class RGmain_hero: RGobjects
{
public:
    RGmain_hero();
    bool forward_ = false, back_ = false, right_ = false, left_ = false;
    
    void upgrade(sf::RenderTexture& rendering, sf::Clock& timer);
    void draw(sf::RenderTexture& rendering);
    void animation_appear(sf::RenderWindow& window, sf::RenderTexture& rendering, sf::Sprite& background);
    void fire(RGbullet& bullet);
    void power_fire(RGbullet& bullet);
    int getx();
    int gety();
    void check_collision();
    int get_health ();
    void set_speed (float speed);
    
private:
    float speed_ = 8, acceleration_ = 0.5;
    int shots_, health_ = 3;
    sf::Sprite main_hero_;
};
//--------------------------
class RGmeteors: RGobjects
{
public:
    RGmeteors(int parameter);
    void draw (sf::RenderTexture& rendering);
    bool check ();
    int get_direction ();
    int& get_x();
    int& get_y();
    int get_type();
    int get_speed();
    int get_start_x();
    int get_start_y();
    void appear1();
    void appear2();
    void appear3();
    void deactivate();
    int get_width ();
    int get_height ();

private:
    sf::Sprite meteor_;
    int speed_, rotation_, type_, movement_direction_, start_x_, start_y_;
    //int random_parameter_ = static_cast<unsigned int>(time(0));
    bool status_ = false;
};
//--------------------------
class RGbot: RGobjects
{
public:
    RGbot();
    void draw (sf::RenderTexture& rendering);
    bool check();
    void activate();
    void deactivate();
    void move_x(char symb);
    void move_y(char symb);
    void fire(RGbullet& bullet);
    void bot_upgrade(RGmain_hero& hero, sf::RenderTexture& rendering, sf::Clock& timer, RGbullet& bullet);
    
private:
    sf::Sprite bot_;
    int speed_ = 10;
    int health = 3;
    bool status_ = false;
};
//--------------------------
void animation_welcome (sf::RenderWindow& window, RGtext& welcome, sf::Sprite background);
void RGgame_run (sf::RenderWindow& window);
void manager(sf::RenderWindow& window, sf::RenderTexture& rendering, RGmain_hero& hero, sf::Sprite& background);
void move (RGmain_hero& hero, sf::Event& event);
void upgrade_bullets(sf::RenderTexture& rendering, sf::Clock& timer);
int getRandomNumber(int min, int max);
void upgrade_meteors(sf::RenderTexture& rendering, sf::Clock& timer);
void meteors_appear(RGmeteors& meteor1, RGmeteors& meteor2, RGmeteors& meteor3);
void check_collisions_bullets_meteors ();

#endif
