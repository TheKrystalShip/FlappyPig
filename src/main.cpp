#include "GameDirector.h"
#include "Constants.h"

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(FP::W_WIDTH, FP::W_HEIGHT), FP::NAME);

    window.setFramerateLimit(FP::FPS);

    FP::GameDirector director;

    sf::Clock clock;

    while (window.isOpen())
    {
        // 1. Check for events

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                switch (event.mouseButton.button)
                {
                case sf::Mouse::Left:
                    if (director.isGameAtDeathScreen() && !director.isTimeoutEnded())
                    {
                        continue;
                    }
                    else if (director.isGameAtStartScreen() || director.isGameAtDeathScreen())
                    {
                        director.start();
                    }
                    else if (!director.isPaused() && !director.isPlayerDead())
                    {
                        director.onSpaceKeyPressed();
                    }
                    break;
                default:
                    break;
                }
                break;
            case sf::Event::KeyPressed:
                switch (event.key.scancode)
                {
                case sf::Keyboard::Scan::Space:
                    if (director.isGameAtDeathScreen() && !director.isTimeoutEnded())
                    {
                        continue;
                    }
                    else if (director.isGameAtStartScreen() || director.isGameAtDeathScreen())
                    {
                        director.start();
                    }
                    else if (!director.isPaused() && !director.isPlayerDead())
                    {
                        director.onSpaceKeyPressed();
                    }
                    break;
                case sf::Keyboard::Scan::Escape:
                    director.onEscapeKeyPressed();
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        } // while (window.pollEvent(event))

        // 2. Show stuff on screen

        switch (director.getGameState())
        {
        case FP::GAME_STATE::START:

            // Show start screen
            window.clear(sf::Color::Cyan);

            window.draw(director.getHud());

            window.display();

            break;
        case FP::GAME_STATE::RUNNING:

            // Show game running screen
            window.clear(sf::Color::Cyan);

            director.update(clock);

            window.draw(director.getClouds());
            window.draw(director.getPipes());
            window.draw(director.getHud());
            window.draw(director.getPlayer());

            window.display();

            break;
        case FP::GAME_STATE::PAUSED:

            // Show pause screen, keep everything on display
            // but stop the director.update(); cycle
            window.clear(sf::Color::Cyan);

            clock.restart();

            window.draw(director.getClouds());
            window.draw(director.getPipes());
            window.draw(director.getPlayer());
            window.draw(director.getHud());

            window.display();

            break;
        case FP::GAME_STATE::DEATH:

            // Show death screen
            window.clear(sf::Color::Cyan);

            window.draw(director.getHud());

            window.display();

            break;
        default:
            break;
        }
    } // while (window.isOpen())

    director.stop();

    return EXIT_SUCCESS;
}
