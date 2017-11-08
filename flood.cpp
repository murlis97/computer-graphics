#include<stdio.h>
#include<graphics.h>
#include<math.h>
void bf_4(int x , int y ,int  fc , int bc)
{
    if(getpixel(x,y)!=bc&& getpixel(x,y)!=fc)
    {
        putpixel(x,y,fc);
        bf_4(x+1,y,fc,bc);
        bf_4(x,y+1,fc,bc);
        bf_4(x-1,y,fc,bc);
        bf_4(x,y-1,fc,bc);
    }
}
void plotPoints(int x,int y,int xc,int yc)
{
    putpixel(x+xc,y+yc,WHITE);
    putpixel(y+xc,x+yc,WHITE);
    putpixel(-x+xc,y+yc,WHITE);
    putpixel(-y+xc,x+yc,WHITE);
    putpixel(x+xc,-y+yc,WHITE);
    putpixel(y+xc,-x+yc,WHITE);
    putpixel(-x+xc,-y+yc,WHITE);
    putpixel(-y+xc,-x+yc,WHITE);
}
void drawCircle(int xc ,int yc , int r)
{
    int po,x=0,y=r,p;
    po=3-2*r;
    p=po;
    do
    {
        plotPoints(x,y,xc,yc);
        if(p<0)
        {
            p=p+4*x+6;
            x=x+1;
        }
        else
        {
            p=p+4*(x-y)+10;
            x=x+1;
            y=y-1;
        }
     }while(x<=y);
}

int main()
{
    int sx, sy, gd=DETECT, gm;
    float r;
    initgraph(&gd , &gm , "C:\\TURBOC3\\BGI");
    sx=getwindowwidth()/2;
    sy=getwindowheight()/2;
    r=100;
    printf("%d,%d",sx,sy);
    drawCircle(sx,sy-((r*2)/3),r);
    drawCircle(sx+(r/sqrt(3)),sy+(r/3),r);
    drawCircle(sx-(r/sqrt(3)),sy+(r/3),r);
    while(1)
    {
        bf_4(sx,sy-((r*2)/3),LIGHTBLUE,WHITE);
        bf_4(sx+(r/sqrt(3)),sy+(r/3),YELLOW,WHITE);
        bf_4(sx-(r/sqrt(3)),sy+(r/3),RED,WHITE);
        bf_4(sx+10,sy+10,LIGHTRED,WHITE);
        bf_4(sx+50,sy,LIGHTMAGENTA,WHITE);
        bf_4(sx-50,sy,LIGHTGREEN,WHITE);
        bf_4(sx,sy+50,GREEN,WHITE);
    }
    getch();
}
