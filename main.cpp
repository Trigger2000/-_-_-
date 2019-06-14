//
//  Header.h
//  Game
//
//  Created by Илья  on 03/06/2019.
//  Copyright © 2019 Илья . All rights reserved.
//

#include "Declarations.h"
//#define TIME_LEVEL 60

std::vector<RGbullet> bullets;
std::vector<RGmeteors> meteors;
std::vector<RGbullet> enemies_bullets;

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    sf::RenderWindow window(sf::VideoMode(2560, 1600), "Rule the galaxy");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    
    RGgame_run(window);
    
    return 0;
}

void RGgame_run (sf::RenderWindow& window)
{
    sf::Texture map_texture;
    map_texture.loadFromFile("/Users/ilya1/Desktop/code/Game/res/space.jpg");
    map_texture.setSmooth(true);
    sf::Sprite background(map_texture);
    background.setScale(1.33, 1.33);
    window.clear(sf::Color::Transparent);
    window.draw(background);
    
    sf::RenderTexture rendering;
    rendering.create(2560, 1600);
    rendering.clear(sf::Color::Transparent);
    rendering.draw(background);
    rendering.display();
    
    RGtext welcome ("Press Space to start", 1.3, sf::Color::Red, 1250, 650);
    welcome.draw(window);
    animation_welcome(window, welcome, background);
    
    RGmain_hero hero;
    //hero.draw(rendering);
    hero.animation_appear(window, rendering, background);
    
    manager(window, rendering, hero, background);
}

void manager (sf::RenderWindow& window, sf::RenderTexture& rendering, RGmain_hero& hero, sf::Sprite& background)
{
    RGbullet bullet1 (1);
    RGbullet bullet2 (2);
    RGbullet bullet3 (3);
    RGmeteors meteor1 (1);
    RGmeteors meteor2 (2);
    RGmeteors meteor3 (3);
    RGbot bot;
    RGtext end("Game over", 10, sf::Color::Red, 1250, 650);
    sf::Clock timer, shot_timer1, shot_timer2, shot_timer3, global_time;
    bool check_bot = false;
    
    while (window.isOpen())
    {
        sf:: Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    window.close();
                    break;
                }
            }
        }
        
        move(hero, event);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shot_timer1.getElapsedTime().asMilliseconds() > 500)
        {
            hero.fire(bullet2);
            shot_timer1.restart();
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && shot_timer2.getElapsedTime().asMilliseconds() > 500)
        {
            hero.power_fire(bullet1);
            shot_timer2.restart();
        }
        
        if (global_time.getElapsedTime().asSeconds() > 4)
        {
            meteors_appear(meteor1, meteor2, meteor3);
            global_time.restart();
        }
        
        if (timer.getElapsedTime().asSeconds() > 3 && check_bot == false)
        {
            bot.activate();
            check_bot = true;
        }
        
        hero.check_collision();
        if (hero.get_health() <= 0)
        {
            break;
        }
        hero.upgrade(rendering, timer);
        bot.bot_upgrade(hero, rendering, shot_timer3, bullet3);
        
        check_collisions_bullets_meteors();
        upgrade_bullets(rendering, timer);
        upgrade_meteors(rendering, timer);
        
        sf::Sprite out(rendering.getTexture());
        window.clear();
        window.draw(out);
        window.display();
        rendering.clear();
        rendering.draw(background);
    }
    
    end.draw(window);
    while (window.isOpen())
    {
        sf:: Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    window.close();
                    break;
                }
            }
        }
    }
}
