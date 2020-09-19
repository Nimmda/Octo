#pragma once
#include "SDL2/SDL.h"

namespace Octo {
    

    class Application
    {
    private:
        SDL_Window *window_ = NULL;
        int screenH_, screenW_;
        void fillSurface();
        int createWindow();
    public:
        Application(/* args */);
        ~Application();
        int Run();
    };
    
}