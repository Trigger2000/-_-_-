//
//  RGtext.cpp
//  Game
//
//  Created by Илья  on 06/06/2019.
//  Copyright © 2019 Илья . All rights reserved.
//
#include "Declarations.h"

#define PRINT() \
{ \
    this->change(window, content_, scale_, colour_, x_, y_); \
    window.clear(); \
    window.draw(background); \
    this->draw(window); \
    time.restart(); \
}

RGtext:: RGtext(std::string content, float size, sf::Color colour, int pos_x, int pos_y)
{
    Helvetica_.loadFromFile("/Users/ilya1/Desktop/code/Game/res/Helvetica.ttc");
    x_ = pos_x;
    y_ = pos_y;
    content_ = content;
    scale_ = size;
    colour_ = colour;
    
    text_.setFont(Helvetica_);
    text_.setString(content_);
    text_.setFillColor(colour_);
    
    bounding_box_ = text_.getLocalBounds();
    text_.setOrigin(bounding_box_.width / 2, bounding_box_.height / 2);
    text_.setScale(scale_, scale_);
}

void RGtext::draw (sf::RenderWindow& window)
{
    text_.setPosition(x_, y_);
    sf::RenderTexture offscreen;
    offscreen.create(2560, 1600);
    
    offscreen.clear(sf::Color::Transparent);
    offscreen.draw(text_);
    offscreen.display();
    
    sf::Sprite out(offscreen.getTexture());
    window.draw(out);
    window.display();
}

void RGtext::change(sf::RenderWindow& window, std::string content, float size, sf::Color colour, int pos_x, int pos_y)
{
    x_ = pos_x;
    y_ = pos_y;
    content_ = content;
    scale_ = size;
    colour_ = colour;
    
    text_.setString(content_);
    text_.setFillColor(colour_);
    
    bounding_box_ = text_.getLocalBounds();
    text_.setOrigin(bounding_box_.width / 2, bounding_box_.height / 2);
    text_.setPosition(pos_x, pos_y);
    text_.setScale(scale_, scale_);
}

void RGtext::animation_big(float upper_limit, sf::RenderWindow& window, sf::Sprite background, sf::Keyboard::Key interrupter)
{
    sf::Clock time;
    while (scale_ <= upper_limit)
    {
        if (time.getElapsedTime().asMilliseconds() > 20)
        {
            scale_ += 0.01;
            PRINT();
        }
        
        if (sf::Keyboard::isKeyPressed(interrupter))
        {
            break;
        }
    }
}

void RGtext::animation_small(float lower_limit, sf::RenderWindow& window, sf::Sprite background, sf::Keyboard::Key interrupter)
{
    sf::Clock time;
    while (scale_ >= lower_limit)
    {
        if (time.getElapsedTime().asMilliseconds() > 20)
        {
            scale_ -= 0.01;
            PRINT();
        }
        
        if (sf::Keyboard::isKeyPressed(interrupter))
        {
            break;
        }
    }
}

void RGtext::animation_big(float upper_limit, sf::RenderWindow& window, sf::Sprite background)
{
    sf::Clock time;
    while (scale_ <= upper_limit)
    {
        if (time.getElapsedTime().asMilliseconds() > 20)
        {
            scale_ += 0.01;
            PRINT();
        }
    }
}

void RGtext::animation_small(float lower_limit, sf::RenderWindow& window, sf::Sprite background)
{
    sf::Clock time;
    while (scale_ >= lower_limit)
    {
        if (time.getElapsedTime().asMilliseconds() > 20)
        {
            scale_ -= 0.01;
            PRINT();
        }
    }
}

void RGtext:: animation_fade(sf::RenderWindow& window, sf::Sprite background)
{
    sf::Clock time;
    int fader_level = 255;
    while (fader_level > 50)
    {
        if (time.getElapsedTime().asMilliseconds() > 10)
        {
            fader_level--;
            sf::Color colour_ (255, 0, 0, fader_level);
            PRINT();
        }
    }
    
    window.clear();
    window.draw(background);
}

void RGtext:: upgrade(sf::RenderTexture& rendering, sf::Clock& timer)
{
    std::cout << 1;
}
