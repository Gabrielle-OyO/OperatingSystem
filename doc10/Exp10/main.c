#include <stdlib.h>
#include <SDL.h>
#include <unistd.h>

int main()
{
    SDL_Surface *screen;
    Uint32 color;
    int x;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Can not initialize SDL:%s\n", SDL_GetError());
        exit(1);
    }

    screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE);
    if (screen == NULL) {
        fprintf(stderr, "Can not set 640*480,16bit color video mode:%s\n", SDL_GetError());
        exit(1);
    }
    atexit(SDL_Quit);

    color = SDL_MapRGB(screen->format, 255, 0, 0);
    SDL_FillRect(screen, NULL, color);
    SDL_UpdateRect(screen, 0, 0, 0, 0);

    for (x = 1; x <= 255; x++) {
        color = SDL_MapRGB(screen->format, 255, x, x);
        SDL_FillRect(screen, NULL, color);
        SDL_UpdateRect(screen, 0, 0, 0, 0);
        SDL_Delay(5);
    }
    sleep(5);

    for (x = 255; x >= 0; x--) {
        color = SDL_MapRGB(screen->format, x, 255, x);
        SDL_FillRect(screen, NULL, color);
        SDL_UpdateRect(screen, 0, 0, 0, 0);
        SDL_Delay(5);
    }

    sleep(3);

    srand(5);
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;

    color = SDL_MapRGB(screen->format, r, g, b);
    SDL_FillRect(screen, NULL, color);
    SDL_UpdateRect(screen, 0, 0, 0, 0);
    sleep(5);

    return 0;
}