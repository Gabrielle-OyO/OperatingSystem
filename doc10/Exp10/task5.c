#include <stdlib.h>
#include <SDL.h>
#include <SDL_draw.h>
#include <unistd.h>

int main() {
    SDL_Surface* screen;
    Uint32 color, black;
    int r, g, b;
    int ox, oy;

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

    black = SDL_MapRGB(screen->format, 0, 0, 0);

    ox = 320;
    oy = 240;

    srand(5);

    for (int i = 0; i < 240; i+=2) {
        r = rand() % 256;
        g = rand() % 256;
        b = rand() % 256;

        color = SDL_MapRGB(screen->format, r, g, b);
        Draw_Circle(screen, ox, oy, i, color);
        SDL_UpdateRect(screen, 0, 0, 0, 0);
        SDL_Delay(10);
        Draw_Circle(screen, ox, oy, i, black);
        SDL_UpdateRect(screen, 0, 0, 0, 0);
    }
    sleep(3);
    
    return 0;
}