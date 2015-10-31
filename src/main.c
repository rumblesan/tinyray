#include <stdio.h>
#include <SDL/SDL.h>

#define BPP    4
#define DEPTH  32

int main(int argc, char *argv[]) {

    SDL_Surface *screen;
    SDL_Event event;

    int running = 1;

    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        return 1;
    }

    if (!(screen = SDL_SetVideoMode(0, 0, DEPTH, SDL_FULLSCREEN|SDL_HWSURFACE))) {
        SDL_Quit();
        return 1;
    }

    const SDL_VideoInfo* vidInfo = SDL_GetVideoInfo();

    while(running) {
        while(SDL_PollEvent(&event)) {

            switch (event.type) {

            case SDL_QUIT:
                running = 0;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    // Escape key
                    running = 0;
                    break;
                default:
                    break;
                }
                break;
            }
        }
    }

    SDL_Quit();

    return 0;
}

