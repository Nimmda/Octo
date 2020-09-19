#include "Application.h"

namespace Octo
{
    Application::Application(/* args */)
    {
    }

    Application::~Application()
    {
        SDL_Quit();
    }

    int Application::Run()
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
            return 1;
        }
        
        return createWindow();
    }

    int Application::createWindow()
    {
        // Create an application window with the following settings:
        window_ = SDL_CreateWindow(
            "An SDL2 window",        // window title
            SDL_WINDOWPOS_UNDEFINED, // initial x position
            SDL_WINDOWPOS_UNDEFINED, // initial y position
            640,                     // width, in pixels
            480,                     // height, in pixels
            SDL_WINDOW_OPENGL        // flags - see below
        );

        // Check that the window was successfully created
        if (window_ == NULL)
        {
            // In the case that the window could not be made...
            printf("Could not create window: %s\n", SDL_GetError());
            return 1;
        }

        // The window is open: could enter program loop here (see SDL_PollEvent())

        SDL_Delay(3000); // Pause execution for 3000 milliseconds, for example

        // Close and destroy the window
        SDL_DestroyWindow(window_);

        return 0;
    }
    

} // namespace Octo