#include<SDL.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

int main() {
	SDL_Surface* screen, * image;
	SDL_Event event;
	int bAppRun = 1;
	int bTopBottom = 1;
	int bLeftRight = 1;
	Uint32 Tstart, Tstop;
	SDL_Rect drect;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
		fprintf(stderr, "Can not initialize SDL:%s\n", SDL_GetError());
		exit(1);
	}

	screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE);
	if (screen == NULL) {
		fprintf(stderr, "Can not initialize the video mode:%s\n", SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);

	image = SDL_LoadBMP("Circle.bmp");
	if (image == NULL) {
		fprintf(stderr, "Can not open such file:%s", SDL_GetError());
		exit(1);
	}

	drect.x = 0;
	drect.y = 0;
	drect.w = image->w;
	drect.h = image->h;

	if (SDL_BlitSurface(image, NULL, screen, &drect) < 0) {
		fprintf(stderr, "Can not blit surface£º%s", SDL_GetError());
		SDL_FreeSurface(image);
		exit(1);
	}

	SDL_UpdateRect(screen, 0, 0, image->w, image->h);
	Tstart = SDL_GetTicks();

	while (bAppRun == 1) {
		if (SDL_PollEvent(&event) && event.type == SDL_KEYDOWN && event.key.keysym.scancode == 9) {
			//printf("%d", event.key.keysym.scancode);
			bAppRun = 0;
			break;
		}
		Tstop = SDL_GetTicks();

		if ((Tstop - Tstart) > 15) {
			Tstop = Tstart;
			SDL_FillRect(screen, &drect, 0);

			//ÉÏÏÂÅö×²¼ì²â
			if (bTopBottom == 1) {
				if ((drect.y + drect.h + 3) <= screen->h)
					drect.y += 3;
				else {
					bTopBottom = 0;
					drect.y = screen->h - drect.h;
				}
			}
			else {
				if (drect.y - 3 >= 0)
					drect.y -= 3;
				else {
					bTopBottom = 1;
					drect.y = 0;
				}
			}

			//×óÓÒÅö×²¼ì²â
			if (bLeftRight == 1) {
				if ((drect.x + drect.w + 3) <= screen->w)
					drect.x += 3;
				else {
					bLeftRight = 0;
					drect.x = screen->w - drect.w;
				}
			}
			else {
				if (drect.x - 3 >= 0)
					drect.x -= 3;
				else {
					bLeftRight = 1;
					drect.x = 0;
				}
			}

			if (SDL_BlitSurface(image, NULL, screen, &drect) < 0) {
				fprintf(stderr, "Can not blit surface£º%s", SDL_GetError());
				SDL_FreeSurface(image);
				exit(1);
			}
			SDL_Flip(screen);
		}
	}

	SDL_FreeSurface(image);
	return 0;
}
