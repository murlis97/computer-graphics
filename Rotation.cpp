#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include<stdlib.h>

int xc,yc,gd=DETECT,gm;

void matrixmul(float a[3][3],int b[3][16],int *c)
{
    int sum=0,i,j,k;
    for(i=0;i<3;i++)
        for(j=0;j<16;j++)
        {
            sum=0;
            for(k=0;k<3;k++)
                sum=sum+a[i][k]*b[k][j];
            *((c+i*16) + j)=sum;
        }
}

void drawaxis()
{
    setlinestyle(3,1,1);
    line(0,yc,2*xc,yc);
    line(xc,0,xc,2*yc);
    setlinestyle(0,1,3);
}

void Rotate(int p[][16], int tx , int ty , float a)
{
    int i,j,k,c[3][16],c1[3][16],c2[3][16];
    float t1[3][3] = {{1,0,-tx},{0,1,-ty},{0,0,1}};
    float r[3][3] = {{cos(a),-sin(a),0},{sin(a),cos(a),0},{0,0,1}};
    float t2[3][3] = {{1,0,tx},{0,1,ty},{0,0,1}};
    matrixmul(t1,p,(int *)c);
    matrixmul(r,c,(int *)c1);
    matrixmul(t2,c1,(int *)c2);
    for(i=0;i<15;i=i+2)
        line(xc+c2[0][i],yc-c2[1][i],xc+c2[0][i+1],yc-c2[1][i+1]);
}

int main()
{
    float tx,ty,a;
    int p[3][16]=
    {
        {80,80,80,240,240,240,240,80,80,140,140,80,128,240,128,240},
        {80,200,200,200,200,80,80,80,80,140,140,200,152,152,128,128},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    initgraph(&gd, &gm, "C:\\TurboC++\\Disk\\TurboC3\\BGI");
    xc=getwindowwidth()/2;
    yc=getwindowheight()/2;
    setlinestyle(1,1,1);
    for(int i=0;i<15;i=i+2)
        line(p[0][i]+xc,-p[1][i]+yc,p[0][i+1]+xc,-p[1][i+1]+yc);
    drawaxis();
    printf("\nEnter the co-ordinates of the point about which rotation is to be performed : ");
    printf("\nX-coordinate : ");
    scanf("%f",&tx);
    printf("\nY-coordinate : ");
    scanf("%f",&ty);
    printf("\n\nEnter angle of rotation (in degrees) : ");
    scanf("%f",&a);
    a=(a*3.14)/180;
    Rotate(p,tx,ty,a);
    putpixel(tx+xc,yc-ty,WHITE);
    getch();
}
