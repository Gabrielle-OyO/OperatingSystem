#include<SDL.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<SDL_ttf.h>

void init_daemon() {
	pid_t pid;
	int i;

	if ((pid = fork()) < 0) {
		perror("Fork failed.\n");
		exit(1);
	}

	if (pid > 0)
		exit(0);
	setsid();
	chdir("/tmp");
	umask(0);
	for (i = 0; i < 1048576; i++)
		close(i);
}


int main() {
	SDL_Surface* text, * screen;
	SDL_Rect drect;
	SDL_Color white = { 255,255,255,0 };
	TTF_Font* Nfont;
	pid_t pid;
	int stat;

	init_daemon();

	while (1) {
		sleep(5);
		if ((pid = fork()) == 0) {
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

			Nfont = TTF_OpenFont("/usr/share/fonts/simsunb.ttf", 20);
			TTF_SetFontStyle(Nfont, TTF_STYLE_NORMAL);
			text = TTF_RenderUTF8_Blended(Nfont, "You have worked for TWO hours!", white);
			TTF_CloseFont(Nfont);
			TTF_Quit();
			drect.x = 15;
			drect.y = 200;
			drect.w = text->w;
			drect.h = text->h;
			SDL_BlitSurface(text, NULL, screen, &drect);
			SDL_UpdateRect(screen, 0, 0, 0, 0);
			SDL_FreeSurface(text);
			sleep(3);
			exit(0);
		}
		else {
			waitpid(pid, &stat, 0);
		}
	}
}