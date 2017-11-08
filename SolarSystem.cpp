#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>

void planetMotion(int xrad, int yrad, int midx, int midy, int x[60], int y[60])
{
    int i,j=0;
    for(i=360; i>0; i=i-6)
    {
        x[j]=midx-(xrad*cos((i*M_PI)/180));
        y[j++]=midy-(yrad*sin((i*M_PI)/180));
    }
    return ;
}

int main()
{
    int gd=DETECT,gm,err;
    int i=0, midx,midy;
    int xrad[8],yrad[8],x[8][60],y[8][60];
    int pos[8], planet[8],tmp;

    initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
    err=graphresult();
    if(err!=grOk)
    {
        printf("Graphics error : %s",grapherrormsg(err));
        return 0;
    }

    midx=getmaxx()/2;
    midy=getmaxy()/2;
    planet[0]=11;
    for(i=1;i<8;i++)
    {
        planet[i]=planet[i-1]+1;
    }

    for(i=0;i<8;i++)
        pos[i]=i*6;

    xrad[0]=60;
    yrad[0]=30;
    for(i=1;i<8;i++)
    {
        xrad[i]=xrad[i-1]+30;
        yrad[i]=yrad[i-1]+15;
    }

    for(i=0;i<8;i++)
        planetMotion(xrad[i],yrad[i],midx,midy,x[i],y[i]);

    while(!kbhit())
    {
        setcolor(WHITE);
        for(i=0;i<8;i++)
            ellipse(midx,midy,0,360,xrad[i],yrad[i]);
        setcolor(YELLOW);
        setfillstyle(SOLID_FILL,YELLOW);
        circle(midx,midy,20);
        floodfill(midx,midy,YELLOW);

        setcolor(CYAN);
        setfillstyle(SOLID_FILL,CYAN);
        pieslice(x[0][pos[0]],y[0][pos[0]],0,360,planet[1]);

        setcolor(LIGHTMAGENTA);
        setfillstyle(SOLID_FILL,LIGHTMAGENTA);
        pieslice(x[1][pos[1]],y[1][pos[1]],0,360,planet[1]);

        setcolor(LIGHTBLUE);
        setfillstyle(SOLID_FILL,LIGHTBLUE);
        pieslice(x[2][pos[2]],y[2][pos[2]],0,360,planet[2]);

        setcolor(RED);
        setfillstyle(SOLID_FILL,RED);
        pieslice(x[3][pos[3]],y[3][pos[3]],0,360,planet[3]);

        setcolor(BROWN);
        setfillstyle(SOLID_FILL,BROWN);
        pieslice(x[4][pos[4]],y[4][pos[4]],0,360,planet[4]);

        setcolor(GREEN);
        setfillstyle(SOLID_FILL,DARKGRAY);
        pieslice(x[5][pos[5]],y[5][pos[5]],0,360,planet[5]);

        setcolor(BROWN);
        setfillstyle(SOLID_FILL,BROWN);
        pieslice(x[6][pos[6]],y[6][pos[6]],0,360,planet[6]);

        setcolor(BLUE);
        setfillstyle(SOLID_FILL,BLUE);
        pieslice(x[7][pos[7]],y[7][pos[7]],0,360,planet[7]);

        for(i=0;i<9;i++)
        {
            if(pos[i]<=0)
                pos[i]=59;
            else
                pos[i]=pos[i]-1;
        }

        delay(100);
        cleardevice();
    }

    closegraph();
    return 0;
}
