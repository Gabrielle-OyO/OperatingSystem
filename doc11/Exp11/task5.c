#include<SDL.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>

void showBmp(char* path, SDL_Surface* screen, int x, int y) {
	SDL_Rect dest;

	SDL_Surface* image = SDL_LoadBMP(path);
	if (image == NULL) {
		fprintf(stderr, "Can not open %s:%s", path, SDL_GetError());
		exit(1);
	}

	dest.x = x;
	dest.y = y;
	dest.w = image->w;
	dest.h = image->h;

	SDL_BlitSurface(image, NULL, screen, &dest);
	SDL_UpdateRects(screen, 1, &dest);
	SDL_Delay(500);
}

int main() {
	SDL_Surface* screen;
	int x, y;
	Uint32 white;
	char basename[4][100] = { "black block","red block","green block","blue block" };
	char extension[] = ".bmp";
	char path[4][100];

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Can not initialize SDL:%s\n", SDL_GetError());
		exit(1);
	}

	screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE);
	if (screen == NULL) {
		fprintf(stderr, "Can not initialize the video mode:%s\n", SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);

	white = SDL_MapRGB(screen->format, 255, 255, 255);
	SDL_FillRect(screen, NULL, white);
	SDL_UpdateRect(screen, 0, 0, 0, 0);

	for (int i = 0; i < 4; i++) {
		strcpy(path[i], strcat(basename[i], extension));
	}

	for (x = 0; x < 640 / 32; x++) {
		showBmp(path[x % 4], screen, x * 32, x * 24);
	}
	sleep(3);
	return 0;
}
