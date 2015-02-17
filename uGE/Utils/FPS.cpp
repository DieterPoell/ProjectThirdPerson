#include <iostream>

#include "FPS.hpp"
#include "Time.hpp"

namespace uGE {

    sf::Clock FPS::clock;
    float FPS::startTime = 0.0f;
    float FPS::time = 0.0f;
    unsigned int FPS::count = 0;
    unsigned int FPS::fps = 0;

    void FPS::update()
    {
        FPS::time = FPS::clock.getElapsedTime().asSeconds();
        FPS::count++;
        if ( FPS::time - FPS::startTime >= 1.0f ) {
            std::cout << "FPS " << FPS::count << std::endl;
            FPS::count = 0;
            FPS::startTime = FPS::time;
        }
    }

    unsigned int FPS::getFPS()
    {
        return fps;
    }
}
