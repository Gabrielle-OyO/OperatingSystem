#include<SDL.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<SDL_ttf.h>

int main() {
	SDL_Rect drect;
	TTF_Font* Nfont;

	SDL_Surface* text, * screen;
	SDL_Color white = { 255,255,255,0 };
	char notation[] = "You have worked for TWO hours!";
	char font_path[] = "/usr/share/fonts/simsunb.ttf";
	int font_style[4] = { TTF_STYLE_NORMAL ,TTF_STYLE_BOLD,TTF_STYLE_ITALIC,TTF_STYLE_UNDERLINE };

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

	if (TTF_Init() != 0) {
		fprintf(stderr, "Can not inityialize font:%s", SDL_GetError());
		exit(1);
	}

	drect.x = 40;
	drect.y = 200;

	Nfont = TTF_OpenFont(font_path, 40);
	Uint32 black = SDL_MapRGB(screen->format, 0, 0, 0);
	for (int i = 0; i < 4; i++) {

		TTF_SetFontStyle(Nfont, font_style[i]);
		text = TTF_RenderUTF8_Blended(Nfont, notation, white);
		drect.w = text->w;
		drect.h = text->h;
		SDL_BlitSurface(text, NULL, screen, &drect);
		SDL_UpdateRect(screen, 0, 0, 0, 0);
		sleep(2);
		SDL_FreeSurface(text);
		SDL_FillRect(screen, NULL, black);
		SDL_UpdateRect(screen, 0, 0, 0, 0);
	}

	TTF_CloseFont(Nfont);
	TTF_Quit();
	return 0;
}