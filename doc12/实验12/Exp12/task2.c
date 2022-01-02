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
#define	FRAME_RATES	10                 	//每秒钟的帧数
#define CANNON_SPEED	5                  	//大炮运动速度
#define MAX_SHOTS	1                       	//最多可以发射多少发炮弹
#define SHOT_SPEED	10                      	//炮弹的速度
#define MAX_AIRS	2                       	//最多出现多少架飞机
#define AIR_SPEED	5                       	//飞机的速度
#define AIR_ODDS	(1*FRAME_RATES)		//剩下的飞机数
#define EXPLODE_TIME	4					//爆炸时间
#define MAX_UPDATES	3*(1+MAX_SHOTS+MAX_AIRS)	//最大更新次数
#define SCORE_PER_AIR 5

int score = 0;

typedef struct object{							//对象结构体
	int alive;								//是否存活标志
	int facing;								//运动方向
	int x, y;								//坐标
	SDL_Surface* image;						//图像指针
} object;

struct blit {									//定义快速重绘对象结构体
	SDL_Surface* src;
	SDL_Rect* srcrect;
	SDL_Rect* dstrect;
} blits[MAX_UPDATES];

SDL_Surface* screen, * background;						//背景指针
object cannon;									//大炮对象
object shots[MAX_SHOTS];						//炮弹对象
object airs[MAX_AIRS];							//飞机对象
object explosions[MAX_AIRS + 1];					//爆炸对象
SDL_Rect srcUpdate[MAX_UPDATES];				//源目标更新
SDL_Rect dstUpdate[MAX_UPDATES];				//目标更新
int reloading;									//重新加载标志
int numUpdates;		//更新次数的变量


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

	//加载大炮图片
	cannon.image = loadImage(DATAFILE("cannon.bmp"));
	if (cannon.image == NULL)
		return 0;

	//加载炮弹图片
	shots[0].image = loadImage(DATAFILE("shot.bmp"));
	if (shots[0].image == NULL)
		return 0;

	for (i = 1; i < MAX_SHOTS; ++i) {
		shots[i].image = shots[0].image;
	}

	//加载飞机图片
	airs[0].image = loadImage(DATAFILE("air.bmp"));
	if (airs[0].image == NULL)
		return 0;

	for (i = 1; i < MAX_AIRS; ++i) {
		airs[i].image = airs[0].image;
	}

	//加载爆炸图片
	explosions[0].image = loadImage(DATAFILE("explosion.bmp"));
	if (explosions[0].image == NULL)
		return 0;

	for (i = 1; i < MAX_AIRS + 1; ++i) {
		explosions[i].image = explosions[0].image;
	}

	//加载背景图片
	background = loadImage(DATAFILE("background.bmp"));
	if (background == NULL)
		return 0;

	//设置更新目标矩形的指针
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
	for (i = 0; i < MAX_AIRS; ++i) {	//当飞机数没有达到最大值，并且存活值为1时，产生一架新的飞机
		if (!airs[i].alive)
			break;
	}
	if (i == MAX_AIRS) {
		return;
	}

	//用随机函数产生三个数，分别用来标记运动方向
	do {
		airs[i].facing = (rand() % 3) - 1;
	} while (airs[i].facing == 0);

	//确定飞机初始时的y方向上的位置，0即表示屏幕的上部
	airs[i].y = 0;
	if (airs[i].facing < 0) {//如果飞机方向小于0，即反方向，飞机往左边移动
		airs[i].x = screen->w - airs[i].image->w - 1;
	}
	else {
		airs[i].x = 0;
	}
	airs[i].alive = 1;
}

void drawObject(object* sprite)			//画对象
{
	struct blit* update;

	update = &blits[numUpdates++];
	update->src = sprite->image;
	update->srcrect->x = 0;				//根据源目标的大小和位置坐标来画
	update->srcrect->y = 0;
	update->srcrect->w = sprite->image->w;
	update->srcrect->h = sprite->image->h;
	update->dstrect->x = sprite->x;
	update->dstrect->y = sprite->y;
	update->dstrect->w = sprite->image->w;
	update->dstrect->h = sprite->image->h;
}

void eraseObject(object* sprite)		//消除目标
{
	struct blit* update;
	int wrap;
	//背景水平重叠达到清除画面效果
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

	//一个背景一个背景的把屏幕重绘
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

//碰撞检测
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
		SDL_Delay(next_tick - this_tick);//延时
	}

	next_tick = this_tick + (1000.0 / FRAME_RATES);//下一帧
}

void runGame(void)
{
	int i, j;
	SDL_Event event;
	Uint8* keys;
	numUpdates = 0;
	SDL_Rect dst;			//开始把背景画上去
	dst.x = 0;
	dst.y = 0;
	dst.w = background->w;
	dst.h = background->h;
	SDL_BlitSurface(background, NULL, screen, &dst);
	SDL_UpdateRect(screen, 0, 0, 0, 0);

	//初始化大炮参数，存活，位置和运动方向
	cannon.alive = 1;
	cannon.x = (screen->w - cannon.image->w) / 2;
	cannon.y = (screen->h - cannon.image->h) - 1;
	cannon.facing = 0;

	drawObject(&cannon);

	//初始化炮弹的存活参数
	for (i = 0; i < MAX_SHOTS; ++i) {
		shots[i].alive = 0;
	}

	//初始化飞机的存活参数
	for (i = 0; i < MAX_AIRS; ++i) {
		airs[i].alive = 0;
	}

	createAir();				//产生飞机
	drawObject(&airs[0]);   	//画飞机
	UpdateScreen();

	while (cannon.alive == 1) {
		WaitFrame();
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				return;
		}
		keys = SDL_GetKeyState(NULL);
		for (i = 0; i < MAX_SHOTS; ++i) {			//清除炮弹
			if (shots[i].alive) {
				eraseObject(&shots[i]);
			}
		}
		for (i = 0; i < MAX_AIRS; ++i) {	//清除飞机
			if (airs[i].alive) {
				eraseObject(&airs[i]);
			}
		}
		eraseObject(&cannon);
		for (i = 0; i < MAX_AIRS + 1; ++i) {	//清除爆炸
			if (explosions[i].alive) {
				eraseObject(&explosions[i]);
			}
		}
		for (i = 0; i < MAX_AIRS + 1; ++i) {	//爆炸次数记录，并减少
			if (explosions[i].alive) {
				--explosions[i].alive;
			}
		}

		//产生新的飞机
		if ((rand() % AIR_ODDS) == 0) {	
			createAir();
		}

		//产生新的炮弹
		if (!reloading) {
			if (keys[SDLK_SPACE] == SDL_PRESSED) {
				for (i = 0; i < MAX_SHOTS; ++i) {
					if (!shots[i].alive) {
						break;
					}
				}

				//炮弹移动轨迹
				if (i != MAX_SHOTS) {
					shots[i].x = cannon.x + (cannon.image->w - shots[i].image->w) / 2;
					shots[i].y = cannon.y - shots[i].image->h;
					shots[i].alive = 1;
				}
			}
		}
		reloading = (keys[SDLK_SPACE] == SDL_PRESSED);
		cannon.facing = 0;

		//移动大炮
		if (keys[SDLK_RIGHT]) {
			++cannon.facing;
		}
		if (keys[SDLK_LEFT]) {
			--cannon.facing;
		}
		cannon.x += cannon.facing * CANNON_SPEED;

		//大炮碰撞屏幕边缘处理
		if (cannon.x < 0) {
			cannon.x = 0;
		}
		else if (cannon.x >= (screen->w - cannon.image->w)) {
				cannon.x = (screen->w - cannon.image->w) - 1;
		}

		//移动飞机
		for (i = 0; i < MAX_AIRS; ++i) {
			if (airs[i].alive) {
				//计算飞机位移
				airs[i].x += airs[i].facing * AIR_SPEED;

				//飞机触发边缘碰撞处理
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

		//炮弹的移动
		for (i = 0; i < MAX_SHOTS; ++i) {
			if (shots[i].alive) {
				shots[i].y -= SHOT_SPEED;  	//计算炮弹位移
				if (shots[i].y < 0) {
					shots[i].alive = 0;
				}
			}
		}

		//炮弹击中飞机，计算爆炸参数
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
			//得分上限
			if (score >= 1000) return;
		}

		//飞机和大炮碰撞的处理
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

		//画飞机
		for (i = 0; i < MAX_AIRS; ++i) {
			if (airs[i].alive) {
				drawObject(&airs[i]);
			}
		}

		//画炮弹
		for (i = 0; i < MAX_SHOTS; ++i) {
			if (shots[i].alive) {
				drawObject(&shots[i]);
			}
		}

		//画大炮
		if (cannon.alive) {
			drawObject(&cannon);
		}

		//画爆炸
		for (i = 0; i < MAX_AIRS + 1; ++i) {
			if (explosions[i].alive) {
				drawObject(&explosions[i]);
			}
		}
		UpdateScreen();

		//按下Esc退出
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
