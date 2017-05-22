#include<stdlib.h>
#include <graphics.h>
#include<iostream.h>
#include <stdio.h>
#include <conio.h>

void st()
{
    int left, top, right, bottom;
    int x,i;
    rectangle(0,0,getmaxx(),getmaxy());
    rectangle(2,2,getmaxx()-2,getmaxy()-2);

    setfillstyle(1, 9);
    floodfill(3, 3,getmaxcolor());

    x=20;
    i=1;

    while(i<=11)
    {
        left =  x;
        x=x+45;
        top = 50;
        right = x;
        x=x+10;
        bottom = 200;

        bar3d(left,top,right,bottom,5,3);

        setfillstyle(SOLID_FILL, 15);
        floodfill(left+1, top+2,getmaxcolor());
        setfillstyle(SOLID_FILL, 0);
        floodfill(right-2, top-2,getmaxcolor());
        floodfill(right+2,top+2,getmaxcolor());
        i++;
    }

    setcolor(11);
    setfillstyle(SOLID_FILL,11);
    pieslice(639-50,479-70,0,360,100);
    setcolor(14);
    setfillstyle(SOLID_FILL,14);
    pieslice(639-210,479-25,0,360,50);

    setcolor(13);
    setfillstyle(SOLID_FILL,13);
    pieslice(639-180,479-180,0,360,40);

    setcolor(12);
    setfillstyle(SOLID_FILL,12);
    pieslice(25,300,0,360,50);

    x=20;
    i=1;
    setcolor(0);
    while(i<=11)
    {
        left =  x;
        x=x+45;
        top = 50;
        right = x;
        x=x+10;
        bottom = 200;
        setfillstyle(1,15);
        bar3d(left,top,right,bottom,5,1);

        i++;
    }

    x=20;
    i=1;
    while(i<=11)
    {
        left =  x;
        x=x+45;
        top = 50;
        right = x;
        x=x+10;
        bottom = 200;

        setfillstyle(SOLID_FILL, 15);
        bar(left,top,right,bottom);

        i++;
    }


    setcolor(1);
    settextstyle(4,0,50);
    outtextxy(85,200,"piano");

    setcolor(0);
    settextstyle(3,0,1);
    outtextxy(10,420,"Made By:-");

    setcolor(1);
    settextstyle(0,0,2);
    outtextxy(10,455,"Yogesh");

}
void main(void)
{
    int gdriver = DETECT, gmode, errorcode;
    int x,i;
    int left, top, right, bottom;

    initgraph(&gdriver, &gmode, "");
    errorcode = graphresult();

    cleardevice();

    getch();

    st();

    getch();
    closegraph();
    getch();
    getch();
}