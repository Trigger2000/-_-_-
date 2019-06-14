//
//  RGother.cpp
//  Game
//
//  Created by Илья  on 07/06/2019.
//  Copyright © 2019 Илья . All rights reserved.
//
#include "Declarations.h"

extern std::vector<RGbullet> bullets;
extern std::vector<RGmeteors> meteors;

void animation_welcome (sf::RenderWindow& window, RGtext& welcome, sf::Sprite background)
{
    while (window.isOpen())
    {
        sf:: Event event;
        
        welcome.animation_big(1.7, window, background, sf::Keyboard::Space);
        welcome.animation_small(1.3, window, background, sf::Keyboard::Space);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            welcome.animation_fade(window, background);
            break;
        }
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    }
}

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void move (RGmain_hero& hero, sf::Event& event)
{
    bool speed_reset = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        hero.forward_ = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        hero.back_ = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        hero.left_ = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        hero.right_ = true;
    }
    
    if (event.type == sf::Event::KeyReleased)
    {
        speed_reset = true;
        switch (event.key.code)
        {
            case sf::Keyboard::Right:
            {
                hero.forward_ = false;
            }
            case sf::Keyboard::Left:
            {
                hero.back_ = false;
            }
            case sf::Keyboard::Up:
            {
                hero.left_ = false;
            }
            case sf::Keyboard::Down:
            {
                hero.right_ = false;
            }
        }
    }
    
    if (hero.getx() > 2345)
    {
        hero.forward_ = false;
        speed_reset = true;
    }
    
    if (hero.getx() < 222)
    {
        hero.back_ = false;
        speed_reset = true;
    }
    
    if (hero.gety() < 163)
    {
        hero.left_ = false;
        speed_reset = true;
    }
    
    if (hero.gety() > 1190)
    {
        hero.right_ = false;
        speed_reset = true;
    }
    
    if (speed_reset == true)
    {
        hero.set_speed(5);
    }
}

void meteors_appear(RGmeteors& meteor1, RGmeteors& meteor2, RGmeteors& meteor3)
{
    int random1 = getRandomNumber(1, 3);
    int random2 = getRandomNumber(1, 3);
    int random3 = getRandomNumber(1, 3);
    
    if (random1 == 1)
    {
        if (random2 == 1)
        {
            if (random3 == 1)
            {
                meteor1.appear1();
            }
            else if (random3 == 2)
            {
                meteor1.appear2();
            }
            else
            {
                meteor1.appear3();
            }
        }
        else if (random2 == 2)
        {
            if (random3 == 1)
            {
                meteor2.appear1();
            }
            else if (random3 == 2)
            {
                meteor2.appear2();
            }
            else
            {
                meteor2.appear3();
            }
        }
        else
        {
            if (random3 == 2)
            {
                meteor3.appear2();
            }
            else if (random3 == 3)
            {
                meteor3.appear3();
            }
        }
    }
    else if (random1 == 2)
    {
        if (random2 == 1)
        {
            if (random3 == 1)
            {
                meteor1.appear1();
                meteor2.appear1();
            }
            else if (random3 == 2)
            {
                meteor2.appear3();
                meteor1.appear2();
            }
            else
            {
                meteor1.appear1();
                meteor2.appear1();
            }
        }
        else if (random2 == 2)
        {
            if (random3 == 1)
            {
                meteor1.appear1();
                meteor2.appear2();
            }
            else if (random3 == 2)
            {
                meteor1.appear1();
                meteor3.appear3();
            }
            else
            {
                meteor2.appear2();
                meteor2.appear3();
            }
        }
        else
        {
            if (random3 == 1)
            {
                meteor1.appear2();
                meteor3.appear2();
            }
            else if (random3 == 2)
            {
                meteor2.appear3();
                meteor1.appear1();
            }
            else
            {
                meteor2.appear1();
                meteor2.appear1();
            }
        }
    }
    else
    {
        if (random2 == 1)
        {
            meteor1.appear1();
            meteor2.appear2();
            meteor1.appear3();
        }
        else if (random2 == 2)
        {
            meteor2.appear3();
            meteor1.appear1();
            meteor2.appear2();
        }
        else
        {
            meteor2.appear3();
            meteor3.appear1();
            meteor1.appear2();
        }
    }
}

void check_collisions_bullets_meteors ()
{
    bool checker = false;
    int it = 0;
    for (int counter = 0; counter < meteors.size(); counter++)
    {
        for (it = 0; it < bullets.size(); it++)
        {
            /*if (pow(meteors[counter].get_x() - bullets[counter].get_x(), 2) + pow(meteors[counter].get_y() - bullets[counter].get_y(), 2) > 30000)
            {
                continue;
            }
            else */
            {
                int width = meteors[counter].get_width() / 2, height = meteors[counter].get_height() / 2;
                int b_pos_x = bullets[it].get_x(), b_pos_y = bullets[it].get_y();
                int m_pos_x = meteors[counter].get_x(), m_pos_y = meteors[counter].get_y();
                
                if (b_pos_x < m_pos_x + width && b_pos_x > m_pos_x - width && b_pos_y < m_pos_y + height && b_pos_y > m_pos_y - height)
                {
                    checker = true;
                    break;
                }
            }
        }
        
        if (checker == true)
        {
            bullets.erase(bullets.begin() + it);
            meteors.erase(meteors.begin() + counter);
        }
    }
}
