#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL.h>
#include <SDL_ttf.h>
#ifdef macintosh
#define DIR_SEP	":"
#define DIR_CUR ":"
#else
#define DIR_SEP	"/"
#define DIR_CUR	""
#endif
#define ROOT_DIRECTORY "/home/ljr/Desktop/Exp12/data"
#define DATAFILE(X)	ROOT_DIRECTORY DIR_SEP X
#define	FRAME_RATES	10                 	//ÿ���ӵ�֡��
#define CANNON_SPEED	5                  	//�����˶��ٶ�
#define MAX_SHOTS	1                       	//�����Է�����ٷ��ڵ�
#define SHOT_SPEED	10                      	//�ڵ����ٶ�
#define MAX_AIRS	2                       	//�����ֶ��ټܷɻ�
#define AIR_SPEED	5                       	//�ɻ����ٶ�
#define AIR_ODDS	(1*FRAME_RATES)		//ʣ�µķɻ���
#define EXPLODE_TIME	4					//��ըʱ��
#define MAX_UPDATES	3*(1+MAX_SHOTS+MAX_AIRS)	//�����´���
#define SCORE_PER_AIR 5

int score = 0;

typedef struct object{							//����ṹ��
	int alive;								//�Ƿ����־
	int facing;								//�˶�����
	int x, y;								//����
	SDL_Surface* image;						//ͼ��ָ��
} object;

struct blit {									//��������ػ����ṹ��
	SDL_Surface* src;
	SDL_Rect* srcrect;
	SDL_Rect* dstrect;
} blits[MAX_UPDATES];

SDL_Surface* screen, * background;						//����ָ��
object cannon;									//���ڶ���
object shots[MAX_SHOTS];						//�ڵ�����
object airs[MAX_AIRS];							//�ɻ�����
object explosions[MAX_AIRS + 1];					//��ը����
SDL_Rect srcUpdate[MAX_UPDATES];				//ԴĿ�����
SDL_Rect dstUpdate[MAX_UPDATES];				//Ŀ�����
int reloading;									//���¼��ر�־
int numUpdates;		//���´����ı���


SDL_Surface* loadImage(char* datafile) {
	SDL_Surface* image, * surface;
	image = SDL_LoadBMP(datafile);
	if (image == NULL) {
		fprintf(stderr, "Couldn't load image %s: %s\n", datafile, SDL_GetError());
		return(NULL);
	}

	surface = SDL_DisplayFormat(image);	SDL_FreeSurface(image);
	return(surface);
}

void printScore() {
	SDL_Color green = { 0,255,0,0 };
	int fontSize = 30;
	TTF_Font* Nfont;
	SDL_Surface* text;
	SDL_Rect fontRect;

	if (TTF_Init() != 0) {
		fprintf(stderr, "Can not initialize TTF font.\n");
	}

	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

	Nfont = TTF_OpenFont("/usr/share/fonts/simsunb.ttf", fontSize);
	TTF_SetFontStyle(Nfont, TTF_STYLE_NORMAL);
	char end[50];

	sprintf(end, "You got %d scores.", score);
	text = TTF_RenderUTF8_Blended(Nfont, end, green);
	TTF_CloseFont(Nfont);
	TTF_Quit();

	fontRect.x = 200;
	fontRect.y = 50;
	fontRect.w = text->w;
	fontRect.h = text->h;

	SDL_BlitSurface(text, NULL, screen, &fontRect);
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	SDL_FreeSurface(text);
	SDL_Delay(5000);

}

int loadData(void)
{
	int i;

	//���ش���ͼƬ
	cannon.image = loadImage(DATAFILE("cannon.bmp"));
	if (cannon.image == NULL)
		return 0;

	//�����ڵ�ͼƬ
	shots[0].image = loadImage(DATAFILE("shot.bmp"));
	if (shots[0].image == NULL)
		return 0;

	for (i = 1; i < MAX_SHOTS; ++i) {
		shots[i].image = shots[0].image;
	}

	//���طɻ�ͼƬ
	airs[0].image = loadImage(DATAFILE("air.bmp"));
	if (airs[0].image == NULL)
		return 0;

	for (i = 1; i < MAX_AIRS; ++i) {
		airs[i].image = airs[0].image;
	}

	//���ر�ըͼƬ
	explosions[0].image = loadImage(DATAFILE("explosion.bmp"));
	if (explosions[0].image == NULL)
		return 0;

	for (i = 1; i < MAX_AIRS + 1; ++i) {
		explosions[i].image = explosions[0].image;
	}

	//���ر���ͼƬ
	background = loadImage(DATAFILE("background.bmp"));
	if (background == NULL)
		return 0;

	//���ø���Ŀ����ε�ָ��
	for (i = 0; i < MAX_UPDATES; ++i) {
		blits[i].srcrect = &srcUpdate[i];
		blits[i].dstrect = &dstUpdate[i];
	}

	return 1;
}

void freeObject(void) {
	int i;

	SDL_FreeSurface(cannon.image);
	SDL_FreeSurface(shots[0].image);
	SDL_FreeSurface(airs[0].image);
	SDL_FreeSurface(explosions[0].image);
	
}

void createAir(void)
{
	int i;
	for (i = 0; i < MAX_AIRS; ++i) {	//���ɻ���û�дﵽ���ֵ�����Ҵ��ֵΪ1ʱ������һ���µķɻ�
		if (!airs[i].alive)
			break;
	}
	if (i == MAX_AIRS) {
		return;
	}

	//����������������������ֱ���������˶�����
	do {
		airs[i].facing = (rand() % 3) - 1;
	} while (airs[i].facing == 0);

	//ȷ���ɻ���ʼʱ��y�����ϵ�λ�ã�0����ʾ��Ļ���ϲ�
	airs[i].y = 0;
	if (airs[i].facing < 0) {//����ɻ�����С��0���������򣬷ɻ�������ƶ�
		airs[i].x = screen->w - airs[i].image->w - 1;
	}
	else {
		airs[i].x = 0;
	}
	airs[i].alive = 1;
}

void drawObject(object* sprite)			//������
{
	struct blit* update;

	update = &blits[numUpdates++];
	update->src = sprite->image;
	update->srcrect->x = 0;				//����ԴĿ��Ĵ�С��λ����������
	update->srcrect->y = 0;
	update->srcrect->w = sprite->image->w;
	update->srcrect->h = sprite->image->h;
	update->dstrect->x = sprite->x;
	update->dstrect->y = sprite->y;
	update->dstrect->w = sprite->image->w;
	update->dstrect->h = sprite->image->h;
}

void eraseObject(object* sprite)		//����Ŀ��
{
	struct blit* update;
	int wrap;
	//����ˮƽ�ص��ﵽ�������Ч��
	update = &blits[numUpdates++];
	update->src = background;
	update->srcrect->x = sprite->x % background->w;
	update->srcrect->y = sprite->y;
	update->srcrect->w = sprite->image->w;
	update->srcrect->h = sprite->image->h;
	wrap = (update->srcrect->x + update->srcrect->w) - (background->w);

	if (wrap > 0) {
		update->srcrect->w -= wrap;
	}
	update->dstrect->x = sprite->x;
	update->dstrect->y = sprite->y;
	update->dstrect->w = update->srcrect->w;
	update->dstrect->h = update->srcrect->h;

	//һ������һ�������İ���Ļ�ػ�
	if (wrap > 0) {
		update = &blits[numUpdates++];
		update->src = background;
		update->srcrect->x = 0;
		update->srcrect->y = sprite->y;
		update->srcrect->w = wrap;
		update->srcrect->h = sprite->image->h;
		update->dstrect->x = ((sprite->x / background->w) + 1) * background->w;
		update->dstrect->y = sprite->y;
		update->dstrect->w = update->srcrect->w;
		update->dstrect->h = update->srcrect->h;
	}
}

void UpdateScreen(void) {
	int i;
	for (i = 0; i < numUpdates; ++i) {
		SDL_LowerBlit(blits[i].src, blits[i].srcrect,
			screen, blits[i].dstrect);
	}

	SDL_UpdateRects(screen, numUpdates, dstUpdate);
	numUpdates = 0;
}

//��ײ���
int collide(object* sprite1, object* sprite2)
{
	if ((sprite1->y >= (sprite2->y + sprite2->image->h)) ||
		(sprite1->x >= (sprite2->x + sprite2->image->w)) ||
		(sprite2->y >= (sprite1->y + sprite1->image->h)) ||
		(sprite2->x >= (sprite1->x + sprite1->image->w))) {
		return 0;
	}
	return 1;

}

void WaitFrame(void)
{
	static Uint32 next_tick = 0;
	Uint32 this_tick;
	this_tick = SDL_GetTicks();

	if (this_tick < next_tick) {
		SDL_Delay(next_tick - this_tick);//��ʱ
	}

	next_tick = this_tick + (1000.0 / FRAME_RATES);//��һ֡
}

void runGame(void)
{
	int i, j;
	SDL_Event event;
	Uint8* keys;
	numUpdates = 0;
	SDL_Rect dst;			//��ʼ�ѱ�������ȥ
	dst.x = 0;
	dst.y = 0;
	dst.w = background->w;
	dst.h = background->h;
	SDL_BlitSurface(background, NULL, screen, &dst);
	SDL_UpdateRect(screen, 0, 0, 0, 0);

	//��ʼ�����ڲ�������λ�ú��˶�����
	cannon.alive = 1;
	cannon.x = (screen->w - cannon.image->w) / 2;
	cannon.y = (screen->h - cannon.image->h) - 1;
	cannon.facing = 0;

	drawObject(&cannon);

	//��ʼ���ڵ��Ĵ�����
	for (i = 0; i < MAX_SHOTS; ++i) {
		shots[i].alive = 0;
	}

	//��ʼ���ɻ��Ĵ�����
	for (i = 0; i < MAX_AIRS; ++i) {
		airs[i].alive = 0;
	}

	createAir();				//�����ɻ�
	drawObject(&airs[0]);   	//���ɻ�
	UpdateScreen();

	while (cannon.alive == 1) {
		WaitFrame();
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				return;
		}
		keys = SDL_GetKeyState(NULL);
		for (i = 0; i < MAX_SHOTS; ++i) {			//����ڵ�
			if (shots[i].alive) {
				eraseObject(&shots[i]);
			}
		}
		for (i = 0; i < MAX_AIRS; ++i) {	//����ɻ�
			if (airs[i].alive) {
				eraseObject(&airs[i]);
			}
		}
		eraseObject(&cannon);
		for (i = 0; i < MAX_AIRS + 1; ++i) {	//�����ը
			if (explosions[i].alive) {
				eraseObject(&explosions[i]);
			}
		}
		for (i = 0; i < MAX_AIRS + 1; ++i) {	//��ը������¼��������
			if (explosions[i].alive) {
				--explosions[i].alive;
			}
		}

		//�����µķɻ�
		if ((rand() % AIR_ODDS) == 0) {	
			createAir();
		}

		//�����µ��ڵ�
		if (!reloading) {
			if (keys[SDLK_SPACE] == SDL_PRESSED) {
				for (i = 0; i < MAX_SHOTS; ++i) {
					if (!shots[i].alive) {
						break;
					}
				}

				//�ڵ��ƶ��켣
				if (i != MAX_SHOTS) {
					shots[i].x = cannon.x + (cannon.image->w - shots[i].image->w) / 2;
					shots[i].y = cannon.y - shots[i].image->h;
					shots[i].alive = 1;
				}
			}
		}
		reloading = (keys[SDLK_SPACE] == SDL_PRESSED);
		cannon.facing = 0;

		//�ƶ�����
		if (keys[SDLK_RIGHT]) {
			++cannon.facing;
		}
		if (keys[SDLK_LEFT]) {
			--cannon.facing;
		}
		cannon.x += cannon.facing * CANNON_SPEED;

		//������ײ��Ļ��Ե����
		if (cannon.x < 0) {
			cannon.x = 0;
		}
		else if (cannon.x >= (screen->w - cannon.image->w)) {
				cannon.x = (screen->w - cannon.image->w) - 1;
		}

		//�ƶ��ɻ�
		for (i = 0; i < MAX_AIRS; ++i) {
			if (airs[i].alive) {
				//����ɻ�λ��
				airs[i].x += airs[i].facing * AIR_SPEED;

				//�ɻ�������Ե��ײ����
				if (airs[i].x < 0) {
					airs[i].x = 0;
					airs[i].y += airs[i].image->h;
					airs[i].facing = 1;
				}
				else if (airs[i].x + airs[i].image->w >= screen->w) {
					airs[i].x = screen->w - airs[i].image->w - 1;
					airs[i].y += airs[i].image->h;
					airs[i].facing = -1;
				}
			}
		}

		//�ڵ����ƶ�
		for (i = 0; i < MAX_SHOTS; ++i) {
			if (shots[i].alive) {
				shots[i].y -= SHOT_SPEED;  	//�����ڵ�λ��
				if (shots[i].y < 0) {
					shots[i].alive = 0;
				}
			}
		}

		//�ڵ����зɻ������㱬ը����
		for (j = 0; j < MAX_SHOTS; ++j) {
			for (i = 0; i < MAX_AIRS; ++i) {
				if (shots[j].alive && airs[i].alive && collide(&shots[j], &airs[i])) {
					score += SCORE_PER_AIR;
					airs[i].alive = 0;
					explosions[i].x = airs[i].x;
					explosions[i].y = airs[i].y;
					explosions[i].alive = EXPLODE_TIME;
					shots[j].alive = 0;
					break;
				}
			}
			//�÷�����
			if (score >= 1000) return;
		}

		//�ɻ��ʹ�����ײ�Ĵ���
		for (i = 0; i < MAX_AIRS; ++i) {	
			if (airs[i].alive && collide(&cannon, &airs[i])) {
				airs[i].alive = 0;
				explosions[i].x = airs[i].x;
				explosions[i].y = airs[i].y;
				explosions[i].alive = EXPLODE_TIME;
				cannon.alive = 0;
				explosions[MAX_AIRS].x = cannon.x;
				explosions[MAX_AIRS].y = cannon.y;
				explosions[MAX_AIRS].alive = EXPLODE_TIME;
			}
		}

		//���ɻ�
		for (i = 0; i < MAX_AIRS; ++i) {
			if (airs[i].alive) {
				drawObject(&airs[i]);
			}
		}

		//���ڵ�
		for (i = 0; i < MAX_SHOTS; ++i) {
			if (shots[i].alive) {
				drawObject(&shots[i]);
			}
		}

		//������
		if (cannon.alive) {
			drawObject(&cannon);
		}

		//����ը
		for (i = 0; i < MAX_AIRS + 1; ++i) {
			if (explosions[i].alive) {
				drawObject(&explosions[i]);
			}
		}
		UpdateScreen();

		//����Esc�˳�
		if (keys[SDLK_ESCAPE] == SDL_PRESSED) {
			cannon.alive = 0;
		}
	}
}

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(2);
	}
	atexit(SDL_Quit);

	screen = SDL_SetVideoMode(600, 480, 0, SDL_SWSURFACE);
	if (screen == NULL) {
		fprintf(stderr, "Couldn't set 600x480 video mode: %s\n",
			SDL_GetError());
		exit(2);
	}

	srand(time(NULL));

	if (loadData() == 1) {
		runGame();
		freeObject();
		printScore();
		SDL_FreeSurface(background);
	}

	return 0;
}
