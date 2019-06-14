//
//  RGmain_hero.cpp
//  Game
//
//  Created by Илья  on 07/06/2019.
//  Copyright © 2019 Илья . All rights reserved.
//

#include "Declarations.h"

extern std::vector<RGbullet> bullets;
extern std::vector<RGmeteors> meteors;

RGmain_hero:: RGmain_hero()
{
    texture_.loadFromFile("/Users/ilya1/Desktop/code/Game/res/main_hero.png");
    texture_.setSmooth(true);
    main_hero_.setTexture(texture_);
    main_hero_.rotate(90);
    
    scale_ = 1;
    x_ = 1280;
    y_ = 800;
    bounding_box_ = main_hero_.getLocalBounds();
    main_hero_.setOrigin(bounding_box_.width / 2, bounding_box_.height / 2);
    main_hero_.setScale(scale_, scale_);
}

void RGmain_hero:: draw(sf::RenderTexture& rendering)
{
    main_hero_.setPosition(x_, y_);
    sf::RenderTexture offscreen;
    offscreen.create(2560, 1600);
    
    offscreen.clear(sf::Color::Transparent);
    offscreen.draw(main_hero_);
    offscreen.display();
    
    sf::Sprite out(offscreen.getTexture());
    rendering.draw(out);
}

void RGmain_hero:: animation_appear(sf::RenderWindow& window, sf::RenderTexture& rendering, sf::Sprite& background)
{
    for (int counter = 1; counter < 900; counter += 10)
    {
        x_ = counter;
        this->draw(rendering);
        
        sf::Sprite out(rendering.getTexture());
        window.clear();
        window.draw(out);
        window.display();
        rendering.clear();
        rendering.draw(background);
    }
}

void RGmain_hero:: upgrade(sf::RenderTexture& rendering, sf::Clock& timer)
{
    bool checker = false;
    if (this->forward_ == true)
    {
        x_ += speed_;
        checker = true;
    }
    
    if (this->back_ == true)
    {
        x_ -= speed_;
        checker = true;
    }
    
    if (this->left_ == true)
    {
        y_ -= speed_;
        checker = true;
    }
    
    if (this->right_ == true)
    {
        y_ += speed_;
        checker = true;
    }
    
    if (checker == true)
    {
        speed_ += acceleration_;
    }
    
    this->draw(rendering);
}

void RGmain_hero:: fire(RGbullet& bullet)
{
    bullet.activate();
    bullet.set_start(x_ + 75, y_ - 79);
    bullet.setPosition(x_ + 75, y_ - 79);
    bullets.push_back(bullet);
    
    bullet.set_start(x_ + 75, y_ + 79);
    bullet.setPosition(x_ + 75, y_ + 79);
    bullets.push_back(bullet);
    //bullet_counter++;
}

void RGmain_hero:: power_fire(RGbullet& bullet)
{
    bullet.activate();
    bullet.set_start(x_ + 200, y_);
    bullet.setPosition(x_ + 200, y_);
    bullets.push_back(bullet);
}

void RGmain_hero:: set_speed (float speed)
{
    speed_ = speed;
}

int RGmain_hero:: getx()
{
    return x_;
}

int RGmain_hero:: gety()
{
    return y_;
}

void RGmain_hero:: check_collision()
{
    for (int counter = 0; counter < meteors.size(); counter++)
    {
        int m_pos_x = meteors[counter].get_x(), m_pos_y = meteors[counter].get_y();
        if (pow(x_ - m_pos_x, 2) + pow(y_ - m_pos_y, 2) > 40000)
        {
            continue;
        }
        else
        {
            int width = bounding_box_.width / 2, height = bounding_box_.height / 2;
            if (m_pos_x < x_ + width && m_pos_x > x_ - width && m_pos_y > y_ - height && m_pos_y < y_ + height)
            {
                health_--;
                meteors.erase(meteors.begin() + counter);
            }
        }
    }
}

int RGmain_hero:: get_health ()
{
    return health_;
}
