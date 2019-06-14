//
//  RGbullet.cpp
//  Game
//
//  Created by Илья  on 08/06/2019.
//  Copyright © 2019 Илья . All rights reserved.
//

#include "Declarations.h"

extern std::vector<RGbullet> bullets;
extern std::vector<RGbullet> enemies_bullets;

RGbullet:: RGbullet(int parameter)
{
    texture_.setSmooth(true);
    switch (parameter)
    {
        case 1:
        {
            texture_.loadFromFile("/Users/ilya1/Desktop/code/Game/res/shots/1.1.png");
            bullet1_.setTexture(texture_);
            texture_.loadFromFile("/Users/ilya1/Desktop/code/Game/res/shots/1.2.png");
            bullet2_.setTexture(texture_);
            texture_.loadFromFile("/Users/ilya1/Desktop/code/Game/res/shots/1.3.png");
            bullet3_.setTexture(texture_);
            texture_.loadFromFile("/Users/ilya1/Desktop/code/Game/res/shots/1.4.png");
            bullet4_.setTexture(texture_);
            
            direction_ = 1;
            break;
        }
            
        case 2:
        {
            texture_.loadFromFile("/Users/ilya1/Desktop/code/Game/res/shots/2.1.png");
            bullet1_.setTexture(texture_);
            texture_.loadFromFile("/Users/ilya1/Desktop/code/Game/res/shots/2.2.png");
            bullet2_.setTexture(texture_);
            texture_.loadFromFile("/Users/ilya1/Desktop/code/Game/res/shots/2.3.png");
            bullet3_.setTexture(texture_);
            texture_.loadFromFile("/Users/ilya1/Desktop/code/Game/res/shots/2.4.png");
            bullet4_.setTexture(texture_);
            
            direction_ = 1;
            break;
        }
            
        case 3:
        {
            texture_.loadFromFile("/Users/ilya1/Desktop/code/Game/res/shots/3.1.png");
            bullet1_.setTexture(texture_);
            texture_.loadFromFile("/Users/ilya1/Desktop/code/Game/res/shots/3.2.png");
            bullet2_.setTexture(texture_);
            texture_.loadFromFile("/Users/ilya1/Desktop/code/Game/res/shots/3.3.png");
            bullet3_.setTexture(texture_);
            texture_.loadFromFile("/Users/ilya1/Desktop/code/Game/res/shots/3.4.png");
            bullet4_.setTexture(texture_);
            
            direction_ = 2;
            break;
        }
    }
    
    if (direction_ == 1)
    {
        bullet1_.rotate(180);
        bullet2_.rotate(180);
        bullet3_.rotate(180);
        bullet4_.rotate(180);
    }
    
    scale_ = 1;
    x_ = 1280;
    y_ = 800;
    bounding_box_ = bullet4_.getLocalBounds();
    bullet4_.setOrigin(bounding_box_.width / 2, bounding_box_.height / 2);
    bullet4_.setScale(scale_, scale_);
    
    sf::FloatRect bounding_box_temp;
    bounding_box_temp = bullet1_.getLocalBounds();
    bullet1_.setOrigin(bounding_box_temp.width / 2, bounding_box_temp.height / 2);
    bullet1_.setScale(scale_, scale_);
    
    bounding_box_temp = bullet2_.getLocalBounds();
    bullet2_.setOrigin(bounding_box_temp.width / 2, bounding_box_temp.height / 2);
    bullet2_.setScale(scale_, scale_);
    
    bounding_box_temp = bullet3_.getLocalBounds();
    bullet3_.setOrigin(bounding_box_temp.width / 2, bounding_box_temp.height / 2);
    bullet3_.setScale(scale_, scale_);
}

void RGbullet:: draw(sf::RenderTexture& rendering, int sprite_num)
{
    sf::Sprite sprite;
    switch (sprite_num)
    {
        case 1:
            sprite = this->bullet1_;
            break;
            
        case 2:
            sprite = this->bullet2_;
            break;
            
        case 3:
            sprite = this->bullet3_;
            break;
            
        case 4:
            sprite = this->bullet4_;
            break;
    }
    
    sprite.setPosition(x_, y_);
    sf::RenderTexture offscreen;
    offscreen.create(2560, 1600);
    
    offscreen.clear(sf::Color::Transparent);
    offscreen.draw(sprite);
    offscreen.display();
    
    sf::Sprite out(offscreen.getTexture());
    rendering.draw(out);
}

void RGbullet:: setPosition(int x, int y)
{
    x_ = x;
    y_ = y;
}

void RGbullet:: activate()
{
    status_ = true;
}

void RGbullet:: deactivate()
{
    status_ = false;
}

bool RGbullet:: check()
{
    return status_;
}

void RGbullet:: set_start (int position_x, int position_y)
{
    start_position_x_ = position_x;
    start_position_y_ = position_y;
}

int& RGbullet:: get_x()
{
    return x_;
}

int RGbullet:: get_start_x()
{
    return start_position_x_;
}

int& RGbullet:: get_y()
{
    return y_;
}

int RGbullet:: get_start_y()
{
    return start_position_y_;
}

int RGbullet:: get_direction()
{
    return direction_;
}

void upgrade_bullets(sf::RenderTexture& rendering, sf::Clock& timer)
{
    for (int counter = 0; counter < bullets.size(); counter++)
    {
        if (bullets[counter].check() == true)
        {
            if (bullets[counter].get_x() < bullets[counter].get_start_x() + 60)
            {
                bullets[counter].setPosition(bullets[counter].get_x(), bullets[counter].get_start_y());
                bullets[counter].draw(rendering, 1);
                bullets[counter].get_x() += 35;
            }
            else if (bullets[counter].get_x() < bullets[counter].get_start_x() + 120)
            {
                bullets[counter].setPosition(bullets[counter].get_x(), bullets[counter].get_start_y());
                bullets[counter].draw(rendering, 2);
                bullets[counter].get_x() += 35;
            }
            else if (bullets[counter].get_x() < bullets[counter].get_start_x() + 180)
            {
                bullets[counter].setPosition(bullets[counter].get_x(), bullets[counter].get_start_y());
                bullets[counter].draw(rendering, 3);
                bullets[counter].get_x() += 35;
            }
            else if (bullets[counter].get_x() < 2700)
            {
                bullets[counter].setPosition(bullets[counter].get_x(), bullets[counter].get_start_y());
                bullets[counter].draw(rendering, 4);
                bullets[counter].get_x() += 35;
            }
            else
            {
                bullets[counter].deactivate();
                bullets.erase(bullets.begin() + counter);
            }
        }
    }
    
    for (int counter = 0; counter < enemies_bullets.size(); counter++)
    {
        if (enemies_bullets[counter].check() == true)
        {
            if (enemies_bullets[counter].get_x() > enemies_bullets[counter].get_start_x() - 60)
            {
                enemies_bullets[counter].setPosition(enemies_bullets[counter].get_x(), enemies_bullets[counter].get_start_y());
                enemies_bullets[counter].draw(rendering, 1);
                enemies_bullets[counter].get_x() -= 25;
            }
            else if (enemies_bullets[counter].get_x() > enemies_bullets[counter].get_start_x() - 120)
            {
                enemies_bullets[counter].setPosition(enemies_bullets[counter].get_x(), enemies_bullets[counter].get_start_y());
                enemies_bullets[counter].draw(rendering, 2);
                enemies_bullets[counter].get_x() -= 25;
            }
            else if (enemies_bullets[counter].get_x() > enemies_bullets[counter].get_start_x() - 180)
            {
                enemies_bullets[counter].setPosition(enemies_bullets[counter].get_x(), enemies_bullets[counter].get_start_y());
                enemies_bullets[counter].draw(rendering, 3);
                enemies_bullets[counter].get_x() -= 25;
            }
            else if (enemies_bullets[counter].get_x() > -300)
            {
                enemies_bullets[counter].setPosition(enemies_bullets[counter].get_x(), enemies_bullets[counter].get_start_y());
                enemies_bullets[counter].draw(rendering, 4);
                enemies_bullets[counter].get_x() -= 25;
            }
            else
            {
                enemies_bullets[counter].deactivate();
                enemies_bullets.erase(enemies_bullets.begin() + counter);
            }
        }
    }
}
