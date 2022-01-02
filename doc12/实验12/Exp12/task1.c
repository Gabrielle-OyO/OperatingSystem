#include<SDL.h>
#include<stdio.h>
#include<stdlib.h>
#include<SDL_ttf.h>
int main(int argc, char** argv)
{
	SDL_Surface* screen, * text;
	SDL_Surface* marioImage, * monsterImage;

	SDL_Event event;
	TTF_Font* Nfont;

	int bAppRun = 1, right, left, up, down;
	int bTopBottom = 1;
	int bLeftRight = 1;
	Uint32 Tstart, Tstop;
	SDL_Rect monsterRect, marioRect, textRect;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1) {
		fprintf(stderr, "Can not initialize: %s\n", SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);

	screen = SDL_SetVideoMode(960, 720, 16, SDL_SWSURFACE);
	if (screen == NULL) {
		fprintf(stderr, "Can not initialize 960*720£¬16bits video mode:%s\n", SDL_GetError());
		exit(1);
	}

	monsterImage = SDL_LoadBMP("./monster.bmp");
	marioImage = SDL_LoadBMP("./Mario.bmp");
	if (monsterImage == NULL || marioImage == NULL) {
		fprintf(stderr, "Couldn't load BMP: %s\n", SDL_GetError());
		exit(1);
	}

	monsterRect.x = 0;
	monsterRect.y = 0;
	monsterRect.w = monsterImage->w;
	monsterRect.h = monsterImage->h;
	if (SDL_BlitSurface(monsterImage, NULL, screen, &monsterRect) < 0) {
		fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
		SDL_FreeSurface(monsterImage);
		exit(1);
	}

	marioRect.x = 0;
	marioRect.y = 480;
	marioRect.w = marioImage->w;
	marioRect.h = marioImage->h;
	if (SDL_BlitSurface(marioImage, NULL, screen, &marioRect) < 0) {
		fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
		SDL_FreeSurface(marioImage);
		exit(1);
	}
	SDL_UpdateRect(screen, 0, 0, 0, 0);

	Tstart = SDL_GetTicks();
	while (bAppRun == 1) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					bAppRun = 0;
					break;
				case SDLK_RIGHT:
					right = 1;
					left = up = down = 0;
					break;
				case SDLK_LEFT:
					left = 1;
					right = up = down = 0;
					break;
				case SDLK_UP:
					up = 1;
					right = left = down = 0;
					break;
				case SDLK_DOWN:
					down = 1;
					right = left = up = 0;
					break;
				}
			}
		}

		//¹ÖÎï±ßÔµÅö×²¼ì²â
		Tstop = SDL_GetTicks();
		if ((Tstop - Tstart) > 5) {
			SDL_FillRect(screen, &monsterRect, 0);
			if (bTopBottom == 1) {
				if ((monsterRect.y + monsterRect.h + 3) < screen->h) {
					monsterRect.y += 3;
				}
				else {
					bTopBottom = 0;
					monsterRect.y = screen->h - monsterRect.h;
				}
			}
			else {
				if ((monsterRect.y - 3) > 0) {
					monsterRect.y -= 3;
				}
				else {
					bTopBottom = 1;
					monsterRect.y = 0;
				}
			}
			if (bLeftRight == 1) {
				if ((monsterRect.x + monsterRect.w + 3) < screen->w) {
					monsterRect.x += 3;
				}
				else {
					bLeftRight = 0;
					monsterRect.x = screen->w - monsterRect.w;
				}
			}
			else {
				if ((monsterRect.x - 3) > 0) {
					monsterRect.x -= 3;
				}
				else {
					bLeftRight = 1;
					monsterRect.x = 0;
				}
			}

			if (SDL_BlitSurface(monsterImage, NULL, screen, &monsterRect) < 0) {
				fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
				SDL_FreeSurface(monsterImage);
			}
			SDL_Flip(screen);
		}

		//½ÇÉ«±ßÔµÅö×²¼ì²â
		if ((Tstop - Tstart) > 15) {
			Tstart = Tstop;
			SDL_FillRect(screen, &marioRect, 0);
			if (right == 1 && (marioRect.x + marioRect.w + 3 < screen->w)) {
				marioRect.x += 3;
			}

			if (left == 1 && (marioRect.x - 3 > 0)) {
				marioRect.x -= 3;
			}

			if (up == 1 && (marioRect.y - 3 > 0)) {
				marioRect.y -= 3;
			}

			if (down == 1 && (marioRect.y + marioRect.h + 3 < screen->h)) {
				marioRect.y += 3;
			}

			if (SDL_BlitSurface(marioImage, NULL, screen, &marioRect) < 0) {
				fprintf(stderr, "BlitSurface error:%s\n", SDL_GetError());
				SDL_FreeSurface(marioImage);
				exit(1);
			}

			SDL_Flip(screen);
		}

		if (
			(marioRect.x + marioImage->w >= monsterRect.x)	 && \
			(marioRect.x <= monsterRect.x + monsterImage->w) && \
			(marioRect.y + marioImage->h >= monsterRect.y)   && \
			(marioRect.y <= monsterRect.y + monsterImage->h)
			)
				break;
	}

	SDL_FreeSurface(monsterImage);
	SDL_FreeSurface(marioImage);

	//±³¾°ÑÕÉ«±ä»»
	int x;
	Uint32 color;
	for (x = 0; x <= 255; x++)
	{
		color = SDL_MapRGB(screen->format, 255, x, x);
		SDL_FillRect(screen, NULL, color);
		SDL_UpdateRect(screen, 0, 0, 0, 0);
		SDL_Delay(5);
	}

	SDL_Color red = { 255,0,0,0 };
	int fontsize = 50;
	if (TTF_Init() != 0) {
		fprintf(stderr, "Can't init ttf font!\n");
		exit(1);
	}

	Nfont = TTF_OpenFont("/usr/share/fonts/simsunb.ttf", fontsize);
	TTF_SetFontStyle(Nfont, TTF_STYLE_NORMAL);
	text = TTF_RenderUTF8_Blended(Nfont, "GAME OVER", red);
	TTF_CloseFont(Nfont);
	TTF_Quit();

	//´òÓ¡½áÊøÓï
	textRect.x = 200;
	textRect.y = 300;
	textRect.w = text->w;
	textRect.h = text->h;
	SDL_BlitSurface(text, NULL, screen, &textRect);
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	SDL_FreeSurface(text);
	SDL_Delay(3000);

	return 0;
}