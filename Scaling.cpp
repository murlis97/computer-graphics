
#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include<stdlib.h>

int origin[2][1000],h,w;



int plotLineWRTOrigin(int res, int axis)
{
	//This function plots the line on the screen
	float h = (float)getwindowheight();
	float w = (float)getwindowwidth();
	int i;
	for(i=0;i<=res;i++)
	{
    	if(axis == 2)
    	{
        	float y = origin[1][i];
        	putpixel(w/2,y, GREEN);
    	}
    	else if(axis == 1)
    	{
        	float x = origin[0][i];
        	putpixel(x,h/2, GREEN);
    	}
    	else
    	{
        	float x = (w/2)+origin[0][i];
        	float y = (h/2)-origin[1][i];
        	putpixel(x,y, GREEN);
    	}

	}
	return 1;
}

int drawLineByBresenhamsAlgo(float x1, float y1, float x2, float y2)
{
	//Logic of this Algorithm
	float dy,dx,x,y,incx, incy;
	int signx, signy, P;
	dx = x2-x1;
	dy = y2-y1;
	int flag=0;
	dx<0?signx = -1 : signx = 1;
	dy<0?signy = -1 : signy = 1;
	if(abs(dy) > abs(dx))
	{
    	float temp = dx;
    	dx = dy;
    	dy =temp;
    	flag=1;
	}

	P = 2*abs(dy) - abs(dx);

	origin[0][0]= x1;
	origin[1][0] = y1;

	x=x1;
	y= y1;

	for(int i = 0;i<=abs(dx);i++)
	{
    	if(P<0)
    	{
        	if(flag==0)
        	{
            	origin[0][i+1]=x+signx;
            	origin[1][i+1]=y;
            	x=x+signx;
        	}
        	else
        	{
            	origin[0][i+1]=x;
            	origin[1][i+1]=y+signy;
            	y=y+signy;
        	}
        	P=P+2*abs(dy);
    	}
    	else
    	{
        	origin[0][i+1]=x+signx;
        	origin[1][i+1]=y+signy;
        	x=x+signx;
        	y=y+signy;
        	P= P + 2*abs(dy) - 2*abs(dx);
    	}
	}
	return abs(dx);
}

void callDraw(int p[][16], int rest)
{
	cleardevice();

	float h = (float)getwindowheight();
	float w = (float)getwindowwidth();
	int res;

	//Y-axis
	res=drawLineByBresenhamsAlgo(0,0,0,h);
	res = plotLineWRTOrigin(res,2); //code 2 is for Y axis

	//X-axis
	res=drawLineByBresenhamsAlgo(0,0,w,0);
	res = plotLineWRTOrigin(res,1); //Code 1 is for X-axis
	int i;
	for(i=0;i<15;i=i+2)
	{
    	rest = drawLineByBresenhamsAlgo(p[0][i],p[1][i],p[0][i+1],p[1][i+1]);
    	rest = plotLineWRTOrigin(rest,0); //Code 0 is for any line other than X and Y axis
	}
}
void Transform(int p[][16], float t[3][3])
{
	int i,j,k,sum=0,c[3][16],res=0;
	for(i=0;i<3;i++)
    	for(j=0;j<16;j++)
        	c[i][j]=0;
	for(i=0;i<3;i++)
    	for(j=0;j<16;j++)
    	{
        	sum=0;
        	for(k=0;k<3;k++)
            	sum=sum+t[i][k]*p[k][j];
        	c[i][j]=sum;

    	}
	/*
	for(i=0;i<17;i=i+2)
	{
    	res = drawLineByBresenhamsAlgo(c[0][i],c[1][i],c[0][i+1],c[1][i+1]);
    	res = plotLineWRTOrigin(res,0); //Code 0 is for any line other than X and Y axis
	}
	*/
	for(i=0;i<3;i++)
	{
    	for(j=0;j<16;j++)
         	p[i][j] = c[i][j];
	}

}

int main()
{
	int gd = DETECT, gm,i,ch,res=0;
	float tx,ty,a;
	//set all points of the flag to be drawn
	int p[3][16]=
    {
        {80,80,80,240,240,240,240,80,80,140,140,80,128,240,128,240},
        {80,200,200,200,200,80,80,80,80,140,140,200,152,152,128,128},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
	setcolor(GREEN);

	float h = (float)getwindowheight();
	float w = (float)getwindowwidth();

	//Y-axis
	res=drawLineByBresenhamsAlgo(0,0,0,h);
	res = plotLineWRTOrigin(res,2); //code 2 is for Y axis

	//X-axis
	res=drawLineByBresenhamsAlgo(0,0,w,0);
	res = plotLineWRTOrigin(res,1); //Code 1 is for X-axis

	for(i=0;i<15;i=i+2)
	{
    	res = drawLineByBresenhamsAlgo(p[0][i],p[1][i],p[0][i+1],p[1][i+1]);
    	res = plotLineWRTOrigin(res,0); //Code 0 is for any line other than X and Y axis
	}

	//wow
	//outtextxy(20,30,"Original Image" );

	do
	{
    	int x,y;
    	printf("Enter the point to scale about : ");
    	scanf("%d%d",&x, &y);
    	fflush(stdin);

    	float t[3][3] = {{1,0,-x},{0,1,-y},{0,0,1}};
    	Transform(p,t);

    	printf("\n\nEnter Scaling units in X-direction : ");
    	scanf("%f",&tx);
    	printf("\n\nEnter Scaling units in Y-direction : ");
    	scanf("%f",&ty);
    	float d[3][3] = {{tx,0,0},{0,ty,0},{0,0,1}};
    	Transform(p,d);

    	float l[3][3] = {{1,0,x},{0,1,y},{0,0,1}};
    	Transform(p,l);

    	callDraw(p,res);
        for(i=0;i<15;i=i+2)
        {
            printf("\n%d,%d",p[0][i],p[1][i]);
        }
        printf("\n\n");

    	//getch();
    	//system("cls");
	}while(ch!=6);
    getch();
}
