#include<SDL.h>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<SDL_draw.h>

int main() {
	int x, y;
	int y1, y2;
	int c[3], rx[3], ry[3];
	int i;

	SDL_Surface* screen;

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

    srand(4);
    x = 120 + 400.0 * rand() / RAND_MAX;
    y = 240 + 180.0 * rand() / RAND_MAX;
    y1 = y2 = 0;

    while (y1 <= y) {
        Draw_Line(screen, x, y1, x, 0, SDL_MapRGB(screen->format, 255, 255, 255));
        Draw_Line(screen, x, y2, x, 0, SDL_MapRGB(screen->format, 0, 0, 0));
        SDL_Delay(10);
        SDL_UpdateRect(screen, 0, 0, 0, 0);
        y1 += 10;
        if (y1 >= 50)y2 = y1 - 50;
    }

    for (i = 0; i < 3; i++) {
        c[i] = 255;
        rx[i] = 6;
        ry[i] = 3;
    }

    while (c[2] != 0) {
        for (i = 0; i < 3; i++) {
            if (i != 0 && c[0] > 255 - i * 50)
                continue;
            
            if (c[i] != 0) {
                Draw_Ellipse(screen, x, y, rx[i], ry[i], SDL_MapRGB(screen->format, c[i], c[i], c[i]));
                SDL_Delay(20);
            }
        }

        SDL_UpdateRect(screen, 0, 0, 0, 0);

        for (i = 0; i < 3; i++) {
            if (i != 0 && c[0] > 255 - i * 50)
                continue;

            if (c[i] != 0) {
                Draw_Ellipse(screen, x, y, rx[i], ry[i], SDL_MapRGB(screen->format, 0, 0, 0));
                c[i] -= 5;
                rx[i] += 2;
                ry[i] += 1;
            }
        }

        y2 += 10;
        Draw_Line(screen, x, y2, x, 0, SDL_MapRGB(screen->format, 0, 0, 0));
    }

    SDL_Delay(2000);
	return 0;
}