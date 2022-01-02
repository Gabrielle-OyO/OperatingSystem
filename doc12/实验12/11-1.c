#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL_ttf.h>
int main(int argc, char **argv)
{
    SDL_Surface *screen, *text; /*指针text指向文字屏幕*/ /*图像指针, image2代表人物，image代表怪物*/
    SDL_Surface *image2, *image;
    SDL_Event event;                        /*事件对象*/
    TTE_Font *Nfont;                        /*文字样式对象*/
    Uint32 color;                           /*定义一个颜色值*/
    int bAppRun = l, right, left, up, down; /*程序运行和人物运动方向标志*/
    int bTopBottom = l;                     /*屏幕上下*/
    int bLeftRight = l;                     /*屏幕左右 */
    Uint32Tstart, Tstop;                    /*时间开始和结束*/
    SDL_Rect dRect, dRect2, dRect3;         /*目标矩形，分别代表怪物、人物、文字*/
    if(SDL_Init (SDL_INIT_VIDEO ( SDL_INIT_TIMER) ==-l)
    {
        /*初始化视频子系统和计时器子系统*/
        fprintf(stderr, "不能初始化%s\n", SDL_GetError());
        exit(1);
    }
    atexit(SDL_Quit);                                       /*退出*/
    screen = SDL_SetVideoMode(960, 720, 16, SDL_SWSURFACE); /*设置视频模式*/
    if (screen == NULL)
    {
        fprintf(stderr, "不能初始化960*720，16位色的视频模式: %s \n", SDLGetError());
        exit(1);
    }
    image2=SDL_LoadBMP (" . / 1 . bmp" ) ; /*加载人物图片*/
    image = SDL_LoadBMP("./ 2 .bmp"); /*加载怪物图片*/
    if (image == NULL|| image2 ==NULL)
    {
        fprintf(stderr, "Couldn 't load BMP,%s\n", SDL_GetError());
        exit(1);
    }
    dRect.x=0;/*怪物目标矩形的左上角坐标*/
    dRect.y=0;
    dRect.w=image->w ;/*目标矩形的宽和高是位图的宽和高*/
    dRect.h=image->h;
    if(SDL_BlitSurface (image ,NULL,screen , &dRect)<0)
    {
        fprintf(stderr, "BlitSurface error: %s \n", SDL_GetError());
        SDL_Freesurface(image);
        exit(l);
    }
    dRect2.x = 0; /*人物目标矩形的左上角坐标*/
    dRect2.y = 480;
    dRect2.w = image2->w;
    dRect2.h = image2->h;
    if (SDL_BlitSurface(image2, NULL, screen, &dRect2) < 0)
    {
        fprintf(stderr, "BlitSurface error: 品s \n ", SDL_GetError());
        SDL_Freesurface(image2);
        exit(l);
    }
    SDL_UpdateRect(screen, 0, 0, 0, 0); /*更新屏幕*/
    Tstart = SDLGetTicks();             /*计时开始*/
    while (bAppRun == 1)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN) /*判断是否有按键*/
                switch (event.key.keysym.sym)
                {                 /*判断按键类型*/
                case SDLK_ESCAPE: /*按下ESC键直接退出*/
                    bAppRun = 0;
                    break;
                case SDLK_RIGHT: /*按下右键，右运动标志参数为真，其余为假*/
                    right = l;
                    left = 0;
                    up = 0;
                    down = 0;
                    break;
                case SDLK_LEFT: /*按下左键，左运动标志参数为真，其余为假*/
                    left = 1;
                    right = 0;
                    up = 0;
                    down = 0;
                    break;
                case SDLK_UP: /*按下上键，上运动标志参数为真，其余为假*/
                    up = l;
                    right = 0;
                    left = 0;
                    down = 0;
                    break;
                case SDLK_DOWN: /*按下下键，下运动标志参数为真，其余为假*/
                    down = l;
                    right = 0;
                    left = 0;
                    up = 0;
                    break;
                }
        }
        Tstop = SDL_GetTicks();
        if ((Tstop - Tstart) > 5)
        {
            SDL_FillRect(screen, &dRect, 0);
            if (bTopBottom == 1)
            { /*如果碰到屏幕上部或下部*/
                if ((dRect.y + dRect.h + 3) < screen->h)
                {
                    dRect.y += 3;
                }
                else
                {
                    bTopBottom = 0;
                    dRect.y = screen->h - dRect.h;
                }
            }
            else
            {
                if ((dRect.y - 3) > 0)
                {
                    dRect.y -= 3;
                }
                else
                {
                    bTopBottom = 1;
                    dRect.y = 0;
                }
            }
            if (bLeftRight == 1)
            { /*如果碰到右边或是左边*/
                if ((dRect.x + dRect.w + 3) < screen->w)
                {
                    .dRect.x += 3;
                }
                else
                {
                    bLeftRight = 0;
                    dRect.x = screen->w - dRect.w;
                }
            }
            else
            {
                if ((dRect.x - 3) > 0)
                    dRect.x -= 3;
                else
                {
                    bLeftRight = l;
                    dRect.x = 0;
                }
            }
            if (SDL_BlitSurface(image, NULL, screen, &dRect) < 0)
            {
                /*把目标快速转化*/
                fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
                SDL_FreeSurface(image);
            }
            SDL_Flip(screen); /*屏幕缓冲*/
        }
        if ((Tstop - Tstart) > 15)
        {
            Tstart = Tstop;
            SDL_FillRect(screen, &dRect2, 0);
            if (right == 1)
            {
                /*判断是否已经碰到屏幕右边沿 */
                if ((dRect2.x + dReet2.w + 3) < screen->w)
                    dRect2.x += 3;
            }
            if (left == 1)
            {
                if ((dRect2.x - 3) > 0) /*判断是否已经碰到屏幕左边沿 */
                    dRect2.x -= 3;
            }
            if (up == 1)
            {
                if ((dRect2.y - 3) > 0) /*判断是否已经碰到屏幕上边沿*/
                    dRect2.y -= 3;
            }
            if (down == 1)
            {
                /*判断是否已经碰到屏幕下边沿*/
                if ((idRect2.y + dRect2.h + 3) < screen->h)
                    dRect2 - y += 3;
            }
            if (SDL_Blitsurface(image2, NULL, screen, &dRect2) < 0)
            {
                /*把目标快速转化*/
                fprintf(stderr, "BlitSurface error : ts}n", SDL_GetError());
                SDL_FreeSurface(image2);
                exit(l);
            }
            SDL_Flip(screen);
        }
        if ((dRect2.x >= dPect.x - image2->w) & &(dRect2.x <= dRect.x + image->w))
        {
            /*判断怪物是否和人物接触*/
            if ((dRect2.y >= dRect.y - image2->h) && (dRect2.y <= dRect.y + image->h))
                break;
        }
        SDL_FreeSurface(image);
        SDL_FreeSurface(image2); /*释放图像*/
        int x;
        for (x = 0; x <= 255; x++) /*用循环来实现背景色渐变*/
        {
            color = SDL_MapRGB(screen->format, 255, x, x); /*设置颜色*/
            SDL_FillRect(screen, NULL, color);             /*填充整个屏幕*/
            SDL_UpdateRect(screen, 0, 0, 0, 0);            /*更新整个屏幕*/
            SDL_Delay(5);
        }
        SDL_Csolor red = {255, 0, 0, 0}; /*设置字体颜色*/
        int fontsize = 50;               /*设置字体大小*/
        if (TTF_Init() != 0)
        {
            fprintf(stderr, "can't init ttf font! n");
            exit(1);
        }
        /*打开字体库*/
        Nfont = TTF_OpenFont("/usr/share/fonts/truetype/droid/Droidsans.ttf"，fontsize);
        TTF_SetFontstyle(Nfont, TTF_STYLE_NORMAL); /*设置字体样式*/
        text = TTF_RenderUTF8_Blended(Nfont, "GAME OVER", red);
        TTF_CloseFont(Nfont); /*关闭字体库*/
        TTF_Quit();           /*退出*/
        dRect3.x = 200;       /*在点(200,300)处开始写*/
        dRect3.y = 300;
        dRect3.w = text->w; /*目标矩形的宽和高分别的是所写字的宽和高*/
        dRect3.h = text->h;
        SDL_BlitSurface(text, NULL, screen, &dRect3); /*把目标快速转化*/
        SDL_UpdateRect(screen, 0, 0, 0, o);
        sDL_Freesurface(text);
        SDL_Delay(3000); /*停留3秒*/
        return 0;
}