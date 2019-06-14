//
//  RGbot.cpp
//  Game
//
//  Created by Илья  on 11/06/2019.
//  Copyright © 2019 Илья . All rights reserved.
//

#include "Declarations.h"

extern std::vector<RGbullet> bullets;
extern std::vector<RGmeteors> meteors;
extern std::vector<RGbullet> enemies_bullets;

RGbot:: RGbot()
{
    texture_.loadFromFile("/Users/ilya1/Desktop/code/Game/res/bot.png");
    texture_.setSmooth(true);
    bot_.setTexture(texture_);
    
    scale_ = 1;
    x_ = 2300;
    y_ = -400;
    bounding_box_ = bot_.getLocalBounds();
    bot_.setOrigin(bounding_box_.width / 2, bounding_box_.height / 2);
    bot_.setScale(scale_, scale_);
}

void RGbot:: draw (sf::RenderTexture& rendering)
{
    bot_.setPosition(x_, y_);
    sf::RenderTexture offscreen;
    offscreen.create(2560, 1600);
    
    offscreen.clear(sf::Color::Transparent);
    offscreen.draw(bot_);
    offscreen.display();
    
    sf::Sprite out(offscreen.getTexture());
    rendering.draw(out);
}

bool RGbot:: check()
{
    return status_;
}

void RGbot:: activate()
{
    status_ = true;
}

void RGbot:: deactivate()
{
    status_ = false;
}

void RGbot:: move_x(char symb)
{
    if (symb == '-')
    {
        x_ -= speed_;
    }
    else if (symb == '+')
    {
        x_ += speed_;
    }
}

void RGbot:: move_y(char symb)
{
    if (symb == '-')
    {
        y_ -= speed_;
    }
    else if (symb == '+')
    {
        y_ += speed_;
    }
}

void RGbot:: fire(RGbullet& bullet)
{
    bullet.activate();
    bullet.set_start(x_ - 200, y_);
    bullet.setPosition(x_ - 200, y_);
    enemies_bullets.push_back(bullet);
}

void RGbot:: bot_upgrade (RGmain_hero& hero, sf::RenderTexture& rendering, sf::Clock& timer, RGbullet& bullet)
{
    if (status_ == true)
    {
        if (y_ < hero.gety() - 10)
        {
            move_y('+');
        }
        
        if (y_ > hero.gety() + 10)
        {
            move_y('-');
        }
        
        if (y_ > hero.gety() - 20 && y_ < hero.gety() + 20 && timer.getElapsedTime().asSeconds() > 3)
        {
            fire(bullet);
            timer.restart();
        }
        
        this->draw(rendering);
    }
}
