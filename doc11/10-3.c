#include<stdlib.h>
#include<SDL.h>
#include<unistd.h>
#include<math.h>

int main()
{
    SDL_Surface *screen;
    Uint32 white,black;

    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        fprintf(stderr,"Can not initialize SDL:%s\n",SDL_GetError());
        exit(1);
    }

    screen=SDL_SetVideoMode(640,480,16,SDL_SWSURFACE);
    if(screen==NULL)
    {
        fprintf(stderr,"Can not set 640*480,16bit color video mode:%s\n",SDL_GetError());
        exit(1);
    }
    atexit(SDL_Quit);

    white=SDL_MapRGB(screen->format,255,255,255);
    black=SDL_MapRGB(screen->format,0,0,0);

    int s_x=0,s_y=240;
    int e_x,e_y;
    const int r=20;
    for(int i=0;i<320;i++)
    {
        e_x=2*i;
        e_y=240+200*sin(e_x/180.0*3.14);

        Draw_Circle(screen,e_x,e_y,r,white);
        SDL_UpdateRect(screen,0,0,0,0);
        SDL_Delay(5);
        
        Draw_Circle(screen,e_x,e_y,r,black);
        SDL_UpdateRect(screen,0,0,0,0);

        s_x=e_x;
        s_y=e_y;
    }
    sleep(5);
    return 0;
}
