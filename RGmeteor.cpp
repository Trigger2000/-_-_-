//
//  RGmeteor.cpp
//  Game
//
//  Created by Илья  on 09/06/2019.
//  Copyright © 2019 Илья . All rights reserved.
//

#include "Declarations.h"

extern std::vector<RGmeteors> meteors;

RGmeteors:: RGmeteors(int parameter)
{
    texture_.setSmooth(true);
    switch (parameter)
    {
        case 1:
        {
            texture_.loadFromFile("/Users/ilya1/Desktop/code/Game/res/meteors/small.png");
            meteor_.setTexture(texture_);
            type_ = 1;
            speed_ = 10;
            rotation_ = 2;
            break;
        }
        case 2:
        {
            texture_.loadFromFile("/Users/ilya1/Desktop/code/Game/res/meteors/medium.png");
            meteor_.setTexture(texture_);
            type_ = 2;
            speed_ = 7;
            rotation_ = -3;
            break;
        }
        case 3:
        {
            texture_.loadFromFile("/Users/ilya1/Desktop/code/Game/res/meteors/huge.png");
            meteor_.setTexture(texture_);
            type_ = 3;
            speed_ = 4;
            rotation_ = 1;
            break;
        }
    }
    scale_ = 1;
    meteor_.setTexture(texture_);
    x_ = 1280;
    y_ = 800;
    bounding_box_ = meteor_.getLocalBounds();
    meteor_.setOrigin(bounding_box_.width / 2, bounding_box_.height / 2);
    meteor_.setScale(scale_, scale_);
}

void RGmeteors:: draw(sf::RenderTexture& rendering)
{
    meteor_.setPosition(x_, y_);
    meteor_.rotate(rotation_);
    sf::RenderTexture offscreen;
    offscreen.create(2560, 1600);
    
    offscreen.clear(sf::Color::Transparent);
    offscreen.draw(meteor_);
    offscreen.display();
    
    sf::Sprite out(offscreen.getTexture());
    rendering.draw(out);
}

bool RGmeteors:: check ()
{
    return status_;
}

int RGmeteors:: get_direction ()
{
    return movement_direction_;
}

int&  RGmeteors:: get_x()
{
    return x_;
}

int& RGmeteors:: get_y()
{
    return y_;
}

int RGmeteors:: get_start_x()
{
    return start_x_;
}

int RGmeteors:: get_start_y()
{
    return start_y_;
}

int RGmeteors:: get_type()
{
    return type_;
}

int RGmeteors:: get_speed()
{
    return speed_;
}

void RGmeteors:: deactivate()
{
    status_ = false;
}

int RGmeteors:: get_width ()
{
    return bounding_box_.width;
}

int RGmeteors:: get_height ()
{
    return bounding_box_.height;
}

void RGmeteors:: appear1()
{
    status_ = true;
    movement_direction_ = 1;
    x_ = 2900;
    y_ = getRandomNumber(200, 1400);
    start_x_ = x_;
    start_y_ = y_;
    meteors.push_back(*this);
}

void RGmeteors:: appear2()
{
    status_ = true;
    movement_direction_ = 2;
    x_ = getRandomNumber(800, 2300);
    y_ = -200;
    start_x_ = x_;
    start_y_ = y_;
    meteors.push_back(*this);
}

void RGmeteors:: appear3()
{
    status_ = true;
    movement_direction_ = 3;
    x_ = getRandomNumber(800, 2300);
    y_ = 1900;
    start_x_ = x_;
    start_y_ = y_;
    meteors.push_back(*this);
}

void upgrade_meteors(sf::RenderTexture& rendering, sf::Clock& timer)
{
    for (int counter = 0; counter < meteors.size(); counter++)
    {
        if (meteors[counter].get_x() < -300 || meteors[counter].get_y() < -300 || meteors[counter].get_y() > 1900)
        {
            meteors.erase(meteors.begin() + counter);
        }
    }
    
    for (int counter = 0; counter < meteors.size(); counter++)
    {
        if (meteors[counter].check() == true)
        {
            if (meteors[counter].get_direction() == 1)
            {
                if (meteors[counter].get_type() == 1)
                {
                    meteors[counter].get_x() -= meteors[counter].get_speed();
                }
                else if (meteors[counter].get_type() == 2)
                {
                    meteors[counter].get_x() -= meteors[counter].get_speed();
                    if (meteors[counter].get_start_y() < 800)
                    {
                        meteors[counter].get_y() += meteors[counter].get_speed() / 2;
                    }
                    else
                    {
                        meteors[counter].get_y() -= meteors[counter].get_speed() / 2;
                    }
                }
                else
                {
                    meteors[counter].get_x() -= meteors[counter].get_speed();
                }
            }
            else if (meteors[counter].get_direction() == 2)
            {
                if (meteors[counter].get_type() == 1)
                {
                    meteors[counter].get_x() -= meteors[counter].get_speed();
                    meteors[counter].get_y() += meteors[counter].get_speed();
                }
                else if (meteors[counter].get_type() == 2)
                {
                    meteors[counter].get_y() += meteors[counter].get_speed();
                    meteors[counter].get_x() -= meteors[counter].get_speed() / 2;                }
                else
                {
                    meteors[counter].get_x() -= meteors[counter].get_speed();
                    meteors[counter].get_y() += meteors[counter].get_speed();
                }
            }
            else
            {
                if (meteors[counter].get_type() == 1)
                {
                    meteors[counter].get_x() -= meteors[counter].get_speed();
                    meteors[counter].get_y() -= meteors[counter].get_speed();
                }
                else if (meteors[counter].get_type() == 2)
                {
                    meteors[counter].get_y() -= meteors[counter].get_speed();
                    meteors[counter].get_x() -= meteors[counter].get_speed() / 2;
                }
                else
                {
                    meteors[counter].get_x() -= meteors[counter].get_speed();
                    meteors[counter].get_y() -= meteors[counter].get_speed();
                }
            }
            meteors[counter].draw(rendering);
        }
    }
}
