#include<graphics.h>
#include<fstream.h>
#include<dos.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>


void pg1();    				/* to print the first presentation page */


clock_t start,end,ct;			/* variables to store time */


class tune
{
    char name[50];			/* to store name */
    int rno;		     	/* to store reference no */

    int check_r(int re);		/* to check if reference no. is repeating */

public:
    double t[200];			/* to store time interval b/w 2 consequtive keys*/
    char ch[200];		     	/* to store key pressed */
    int n;				/* to store total no. of keys pressed */
    double net_t;			/* to store net time interval of tune */
    void getdata();			/* to get data from user about the tune */
    void showdata();		/* to print data on screen */
    void modify();			/* to modify a tune */
    void get_ref();			/* to get refernce no. from user */
    int get_mod_ref();		/* to get reference no.(when modifying) */

    int ret_r()			/* accessor function to return reference no. */
    {
        return rno;
    }

    char* ret_name()		/* accessor function to return name of the tune */
    {
        return name;
    }

};


int tune::check_r(int re)
{
    tune r;
    ifstream ifile("piano.dat",ios::in|ios::binary);
    ifile.seekg(0);

    while(ifile)
    {
        ifile.read((char*)&r,sizeof(r));

        if(re==r.ret_r())
        {
            ifile.close();
            return 0;
        }
    }
    ifile.close();
    return 1;
}



void tune::getdata()
{
    clrscr();
    cleardevice();
    pg1();
    gotoxy(1,1);
    cout<<"\n Enter NAME of the tune:";
    pg1();
    gets(name);
    get_ref();
}


void tune::showdata()
{
    int y;
    y=wherey();
    gotoxy(25,20);
    gotoxy(11,y);
    cout<<name;
    gotoxy(40,y);
    cout<<rno;
    gotoxy(55,y);
    cout<<net_t;
}


void tune::modify()
{
    char n[50];
    int r;
    int flag;
    clrscr();
    cleardevice();
    gotoxy(1,2);
    cout<<"\n Enter new name(press '.' to retain previous one):";
    pg1();
    gets(n);
    r=get_mod_ref();
    if(r!=-1)
    {
        rno=r;
    }

    if(strcmpi(n,"."))
    {
        strcpy(name,n);
    }
}


void tune::get_ref()
{
    int flag;
    int x,y;
    clrscr();
    cleardevice();
    pg1();
    setcolor(9);
    settextstyle(0,0,2);
    gotoxy(1,1);
    cout<<"\n Enter REF. NO.:";
    pg1();
    cin>>rno;
    flag=check_r(rno);

    if(flag==0)
    {
        cout<<"\n\n !!!Error ref. no. ALREADY EXIST,enter a UNIQUE REF. NO.";
        pg1();
        getch();
        get_ref();
    }
}


int tune::get_mod_ref()
{
    int flag;
    int r;
    clrscr();
    cleardevice();
    gotoxy(1,2);
    cout<<"\n Enter new Reference no('-1' to retain previous one):";
    pg1();
    cin>>r;
    flag=check_r(r);

    if(flag==0)
    {
        cout<<"\n !!!!!!!Error ref. no. alreadry exist,enter a unique ref. no.";
        pg1();
        getch();
        r=get_mod_ref();
    }
    return r;
}


void startp();					/* to start the program */
void main_menu();				/* main menu */
void menu1();					/* sub menu 1 of the main menu(i.e.PLAY IT) */
void menu2();					/* sub menu 2 of the main menu(i.e.iTUNES) */
void m11();				  	/* sub menu 1 of 'PLAY IT'(i.e.AUTOMATIC) */
void m12();					/* sub menu 2 of 'PLAY IT'(i.e.TRY IT YOURSELF) */
void m21();					/* sub menu 2 of 'iTUNES'(i.e. LIST ALL) */
void menu22();					/* sub menu 2 of 'iTUNES'(i.e.SEARCH) */
void key(char x);                               /* to generate sound when a key is pressed */
void automatic(tune &rr);			/* to play a tune automatically */
void self(tune &rr);				/* to play a tune by the user */
void play(tune &r);			        /* to play a tune stored in the memory */
void save(tune &r);				/* to save the tune in the memory */
void del(int);					/* to delete a tune */
void last_ele();				/* to delete last repeating record */
void modification(tune &r);			/* to modify a tune */
void s_seriol_no();				/* to see a record by seriol no */
int s_ref();					/* to search a tune by its reference no. */
int s_name();					/* to search a record by its name */
int replay_skip();                              /* pop up menu to ask for replay/skip */
int mod_del(int x1,int y1,int s,tune &r);       /* popup menu to ask for modify/delete */
int play_yn(int x1,int y1,int x,tune &r);       /* popup menu to ask for YES/NO (play) */
int save_yn(int x1,int y1);                     /* pop up menu to ask for YES/NO (save) */
void d_table();					/* to draw a table for whole data */
void d_st();					/* to draw a short table for only 1 record */


void main()
{

    int gdriver = DETECT, gmode, errorcode;
    initgraph( &gdriver, &gmode, "" );

    clrscr();
    cleardevice();
    startp();
    closegraph();

}


void startp()
{
    int i,max_rad,colo,x,y;
    long t;

    max_rad=getmaxy()/10;
    randomize();

    getch();
    while(!kbhit())
    {
        colo=random(getmaxcolor()+1);
        setcolor(colo);
        setfillstyle(1,colo);
        pieslice(random(640),random(480),0,360,random(max_rad));
    }

    getch();

    x=getmaxx()/2;
    y=getmaxy()/2;

    setcolor(15);
    setfillstyle(1,15);

    for(i=0; (i<=400)&&(!kbhit()); i=i+4)
    {
        pieslice(x,y,0,360,i+40);
    }

    if(kbhit())
        getch();
    else
        delay(100);

    setbkcolor(15);

    for(i=1; (!kbhit())&&(i<=79+275); i++)
    {

        cleardevice();
        setcolor(4);
        settextstyle( 4, HORIZ_DIR, 18 );
        outtextxy(-275+i,250, "Piano" );
        setcolor(1);
        settextstyle(2,0,7);
        outtextxy(714-(i*2),425, "made by:" );
        outtextxy(714-(i*2),450, "Yoge$h & $hivank" );
        delay(10);
    }

    setbkcolor(15);
    delay(200);
    clrscr();
    cleardevice();
    pg1();
    main_menu();
    setcolor(8);
    setfillstyle(1,8);

    for(i=0; (i<=400)&&(!kbhit()); i=i+10)
    {
        pieslice(x,y,0,360,i+40);
    }

}


void pg1()
{

    setcolor(12);
    settextstyle( 4, HORIZ_DIR, 18 );
    outtextxy(79,250, "Piano" );
    setcolor(4);
    outtextxy(80,250, "Piano" );
    setcolor(1);
    settextstyle(2,0,7);
    outtextxy(6,425, "made by:" );
    outtextxy(6,450, "Yoge$h & $hivank" );

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

    setcolor(1);
    rectangle(1,1,getmaxx()-1,getmaxy()-1);
    rectangle(3,3,getmaxx()-3,getmaxy()-3);
}


void main_menu()
{
    int ch=1,c=80;
    int flag;
    char x;

    do
    {
        clrscr();
        cleardevice();
        pg1();
        setcolor(1);
        settextstyle(3,0,5);
        outtextxy(50,25,"MENU");

        setfillstyle(1,7);
        bar(150,44,625,49);
        bar(150,54,625,59);

        bar(50,c,220,c+25);

        settextstyle(0,0,2);
        outtextxy(70,85,"Play iT");
        outtextxy(70,115,"iTune$");
        outtextxy(70,145,"ExIT");

        do
        {

            do
            {

                x=getch();

                flag=1;

                if((x!=72)&&(x!=80)&&(x!=13))
                {
                    flag=0;
                }

                else
                {
                    if((x==72)&&(c==80))
                        flag=0;

                    else if((x==80)&&(c==140))
                        flag=0;

                }

            } while(flag==0);

            if(x==72)
            {
                setfillstyle(1,15);
                bar(50,c-30,220,c+30);
                setfillstyle(1,7);
                bar(50,c-30,220,c-5);

                if(ch==2)
                {
                    settextstyle(0,0,2);
                    outtextxy(70,85,"Play iT");
                    outtextxy(70,115,"iTune$");
                }

                else if(ch==3)
                {
                    settextstyle(0,0,2);
                    outtextxy(70,115,"iTune$");
                    outtextxy(70,145,"ExIT");
                }

                c=c-30;
                ch--;

            }

            else if(x==80)
            {

                setfillstyle(1,15);
                bar(50,c,220,c+55);
                setfillstyle(1,7);
                bar(50,c+30,220,c+55);

                if(ch==1)
                {
                    settextstyle(0,0,2);
                    outtextxy(70,85,"Play iT");
                    outtextxy(70,115,"iTune$");
                }

                else if(ch==2)
                {
                    settextstyle(0,0,2);
                    outtextxy(70,115,"iTune$");
                    outtextxy(70,145,"ExIT");

                }

                c=c+30;
                ch++;

            }

            else if(x==13)
            {
                x='y';
            }

        } while (x!='y');


        if(ch==1)
            menu1();

        else if(ch==2)
            menu2();

    } while(ch!=3);

}


void menu1()
{
    int ch=1,flag,c=110;
    char x;

    do
    {

        clrscr();
        cleardevice();
        pg1();

        setcolor(1);
        settextstyle(3,0,5);
        outtextxy(50,25,"MENU");
        settextstyle(0,0,2);
        outtextxy(70,85,"Play iT");

        setfillstyle(1,7);
        bar(150,44,625,49);
        bar(150,54,625,59);

        bar(105,c,330,c+25);

        settextstyle(0,0,2);
        outtextxy(125,115,"Automatic");
        outtextxy(125,145,"Try yourself");
        outtextxy(125,175,"<<return");
        outtextxy(70,205,"iTune$");
        outtextxy(70,235,"EXIT");

        do
        {
            do
            {
                x=getch();

                flag=1;

                if((x!=72)&&(x!=80)&&(x!=13))
                {
                    flag=0;
                }

                else
                {
                    if((x==72)&&(c==110))
                        flag=0;

                    else if((x==80)&&(c==170))
                        flag=0;

                }

            } while(flag==0);


            if(x==72)
            {
                setfillstyle(1,15);
                bar(105,c-30,330,c+30);
                setfillstyle(1,7);
                bar(105,c-30,330,c-5);

                if(ch==2)
                {
                    settextstyle(0,0,2);
                    outtextxy(125,115,"Automatic");
                    outtextxy(125,145,"Try yourself");
                }

                else if(ch==3)
                {
                    settextstyle(0,0,2);
                    outtextxy(125,145,"Try yourself");
                    outtextxy(125,175,"<<return");
                }

                c=c-30;
                ch--;

            }

            else if(x==80)
            {

                setfillstyle(1,15);
                bar(105,c,330,c+55);
                setfillstyle(1,7);
                bar(105,c+30,330,c+55);

                if(ch==1)
                {

                    settextstyle(0,0,2);
                    outtextxy(125,115,"Automatic");
                    outtextxy(125,145,"Try yourself");

                }

                else if(ch==2)
                {

                    settextstyle(0,0,2);
                    outtextxy(125,145,"Try yourself");
                    outtextxy(125,175,"<<return");

                }

                c=c+30;
                ch++;

            }

            else if(x==13)
            {
                x='y';
            }

        } while (x!='y');

        if(ch==1)
            m11();

        else if(ch==2)
            m12();


    } while (ch!=3);

}

void menu2()
{

    int ch=1,flag,c=140;
    char x;

    do
    {

        clrscr();
        cleardevice();
        pg1();
        setcolor(1);
        settextstyle(3,0,5);
        outtextxy(50,25,"MENU");

        setfillstyle(1,7);
        bar(150,44,625,49);
        bar(150,54,625,59);

        settextstyle(0,0,2);
        outtextxy(70,85,"Play iT");
        outtextxy(70,115,"iTune$");

        bar(105,c,280,c+25);

        settextstyle(0,0,2);
        outtextxy(125,145,"List ALL");
        outtextxy(125,175,"Search");
        outtextxy(125,205,"<<return");
        outtextxy(70,235,"EXIT");

        do
        {

            do
            {
                x=getch();

                flag=1;

                if((x!=72)&&(x!=80)&&(x!=13))
                {
                    flag=0;
                }

                else
                {
                    if((x==72)&&(c==140))
                        flag=0;

                    else if((x==80)&&(c==200))
                        flag=0;

                }

            } while(flag==0);

            if(x==72)
            {
                setfillstyle(1,15);
                bar(105,c-30,280,c+30);
                setfillstyle(1,7);
                bar(105,c-30,280,c-5);

                if(ch==2)
                {

                    settextstyle(0,0,2);
                    outtextxy(125,145,"List ALL");
                    outtextxy(125,175,"Search");

                }

                else if(ch==3)
                {

                    settextstyle(0,0,2);
                    outtextxy(125,175,"Search");
                    outtextxy(125,205,"<<return");

                }

                c=c-30;
                ch--;

            }

            else if(x==80)
            {

                setfillstyle(1,15);
                bar(105,c,280,c+55);
                setfillstyle(1,7);
                bar(105,c+30,280,c+55);

                if(ch==1)
                {

                    settextstyle(0,0,2);
                    outtextxy(125,145,"List ALL");
                    outtextxy(125,175,"Search");

                }

                else if(ch==2)
                {

                    settextstyle(0,0,2);
                    outtextxy(125,175,"Search");
                    outtextxy(125,205,"<<return");

                }

                c=c+30;
                ch++;

            }

            else if(x==13)
            {
                x='y';
            }

        } while (x!='y');

        if(ch==1)
            m21();

        else if(ch==2)
            menu22();

    } while(ch!=3);

}


void m11()
{

    tune r;
    char x[2];
    int ch2;

    clrscr();
    cleardevice();
    pg1();

    setcolor(1);
    settextstyle(2,0,10);
    outtextxy(15,25,"Starting in...");
    delay(50);

    for(int i=3; i>=0; i--)
    {

        if(i==0)
        {
            setcolor(12);
            settextstyle(1,0,6);
            outtextxy(190,75,"START");
            cout<<"\a";
            delay(500);
            setcolor(15);
            settextstyle(1,0,6);
            outtextxy(190,75,"START");

            setcolor(15);
            settextstyle(2,0,10);
            outtextxy(15,25,"Starting in...");
            break;
        }

        x[0]=48+i;
        x[1]='\0';

        setcolor(12);
        settextstyle(1,0,10);
        outtextxy(250,25,x);

        delay(999);

        setcolor(15);
        settextstyle(1,0,10);
        outtextxy(250 ,25,x);

    }

    automatic(r);
    getch();
    cleardevice();
    ch2=replay_skip();
    if(ch2==1)
    {
        play(r);
    }

    clrscr();
    cleardevice();

    ch2=save_yn(20,55);
    if(ch2==1)
    {
        save(r);
    }
}


void m12()
{
    tune r;
    int ch2;
    char x[2];

    clrscr();
    cleardevice();
    pg1();

    setcolor(1);
    settextstyle(2,0,10);
    outtextxy(15,25,"Start in");
    delay(50);

    for(int i=3; i>=0; i--)
    {

        if(i==0)
        {
            setcolor(12);
            settextstyle(1,0,6);
            outtextxy(190,75,"START");
            cout<<"\a";
            delay(500);
            setcolor(15);
            settextstyle(1,0,6);
            outtextxy(190,75,"START");

            setcolor(15);
            settextstyle(2,0,10);
            outtextxy(15,25,"Start in");
            break;
        }

        x[0]=48+i;
        x[1]='\0';

        setcolor(12);
        settextstyle(1,0,10);
        outtextxy(250 ,25,x);

        delay(999);

        setcolor(15);
        settextstyle(1,0,10);
        outtextxy(250 ,25,x);

    }

    setcolor(12);
    settextstyle(0,0,1);
    outtextxy(15,180,"press ENTER to END");
    self(r);
    getch();
    cleardevice();
    ch2=replay_skip();

    if(ch2==1)
    {
        play(r);
    }

    clrscr();
    cleardevice();

    ch2=save_yn(20,55);
    if(ch2==1)
    {
        save(r);
    }

}


void m21()
{
    clrscr();
    cleardevice();
    d_table();

    int i,j;
    tune r;
    i=1;

    ifstream ifile("piano.dat",ios::in|ios::binary);

    ifile.seekg(0);
    gotoxy(0,3);

    while(!ifile.eof())
    {

        if((i%20==1)&&(i!=1))
        {

            d_table();
            setcolor(12);
            settextstyle(2,0,8);
            outtextxy(15,430,"press any key to see the NEXT PAGE...........");
            getch();
            clrscr();
            cleardevice();
            d_table();
        }

        ifile.read((char*)&r,sizeof(r));

        if(ifile.eof())
            break;

        cout<<" "<<i;
        r.showdata();
        i++;
        cout<<"\n";

    }

    ifile.close();
    d_table();
    gotoxy(5,48);
    char chc;

    setcolor(12);
    settextstyle(2,0,8);
    outtextxy(15,430,"press 'S' to select a SPECIFIC TUNE:");
    gotoxy(24,40);

    chc=getche();
    if(chc=='S'||chc=='s')
    {
        s_seriol_no();
    }


}


void menu22()
{

    int ch=1,c=95;
    int flag;
    char x;

    do
    {

        clrscr();
        cleardevice();
        pg1();

        setcolor(9);
        settextstyle(3,0,5);
        outtextxy(40,35,"SEARCH BY:");

        setfillstyle(1,7);
        bar(65,c,300,c+25);

        setcolor(1);
        settextstyle(0,0,2);
        outtextxy(90,100,"REFERENCE NO");
        outtextxy(90,130,"NAME");
        outtextxy(90,160,"<<return");

        do
        {

            do
            {

                x=getch();

                flag=1;

                if((x!=72)&&(x!=80)&&(x!=13))
                {
                    flag=0;
                }

                else
                {
                    if((x==72)&&(c==95))
                        flag=0;

                    else if((x==80)&&(c==155))
                        flag=0;

                }

            } while(flag==0);

            if(x==72)
            {
                setfillstyle(1,15);
                bar(65,c-30,300,c+30);
                setfillstyle(1,7);
                bar(65,c-30,300,c-6);

                if(ch==2)
                {

                    settextstyle(0,0,2);
                    outtextxy(90,100,"REFERENCE NO");
                    outtextxy(90,130,"NAME");

                }

                else if(ch==3)
                {

                    settextstyle(0,0,2);
                    outtextxy(90,130,"NAME");
                    outtextxy(90,160,"<<return");

                }

                c=c-30;
                ch--;

            }

            else if(x==80)
            {

                setfillstyle(1,15);
                bar(65,c,300,c+60);
                setfillstyle(1,7);
                bar(65,c+30,300,c+56);

                if(ch==1)
                {

                    settextstyle(0,0,2);
                    outtextxy(90,100,"REFERENCE NO");
                    outtextxy(90,130,"NAME");

                }

                else if(ch==2)
                {

                    settextstyle(0,0,2);
                    outtextxy(90,130,"NAME");
                    outtextxy(90,160,"<<return");

                }

                c=c+30;
                ch++;

            }

            else if(x==13)
            {
                x='y';
            }


        } while (x!='y');

        if(ch==1)
        {

            flag=s_ref();
            if(flag==0)
            {
                cout<<"\n\n Tune NOT FOUND:\n press any key to return.....";
                pg1();
                getch();
                return;
            }

        }

        else if(ch==2)
        {
            flag=s_name();
            if(flag==0)
            {
                cout<<"\n\n Record NOT FOUND:\n press any key to return.....";
                pg1();
                getch();
                return;
            }
        }

    } while (ch!=3);


}


void key(char x)
{

    if(x=='`')
    {
        sound(1000);
    }

    else if(x=='1')
    {
        sound(1300);
    }

    else if(x=='2')
    {
        sound(1600);
    }

    else if(x=='3')
    {
        sound(1900);
    }

    else if(x=='4')
    {
        sound(2200);
    }

    else if(x=='5')
    {
        sound(2500);
    }

    else if(x=='6')
    {
        sound(2800);
    }

    else if(x=='7')
    {
        sound(3100);
    }

    else if(x=='8')
    {
        sound(3400);
    }

    else if(x=='9')
    {
        sound(3700);
    }

    else if(x=='0')
    {
        sound(4000);
    }

    else if(x=='-')
    {
        sound(4300);
    }

    else if(x=='=')
    {
        sound(4600);
    }

    else if(x==8)
    {
        sound(5000);
    }


    delay(200);
    nosound();

}


void automatic(tune &rr)
{

    randomize();
    char x;
    int k,r,z;
    rr.t[0]=0;
    x=rr.ch[0]=random(10)+47;
    z=random(40)+15;
    setcolor(12);
    settextstyle(2,0,8);
    outtextxy(15,100,"playing..................");

    key(x);
    start=clock();
    rr.net_t=start;
    k=1;

    do
    {
        r=random(300);
        delay(r);
        x=random(10)+47;
        rr.ch[k]=x;
        end=clock();
        rr.t[k]=((end-start)/CLK_TCK);
        key(x);
        start=end;
        k++;

    } while(k<=z);

    rr.n=z;
    rr.net_t=(end-rr.net_t)/18.2;
    setcolor(12);
    settextstyle(2,0,10);
    outtextxy(15,130,"END");

}


void self(tune &rr)
{

    char x;
    int k;
    rr.t[0]=0;
    x=rr.ch[0]=getch();
    setcolor(12);
    settextstyle(2,0,8);
    outtextxy(15,100,"playing..................");
    key(x);
    start=clock();
    rr.net_t=start;
    k=1;
    do
    {

        x=getch();
        rr.ch[k]=x;
        end=clock();
        rr.t[k]=((end-start)/CLK_TCK);
        key(x);
        start=end;
        k++;

    } while(x!=13);

    rr.n=k;
    rr.net_t=(end-rr.net_t)/18.2;
    setcolor(12);
    settextstyle(2,0,10);
    outtextxy(15,130,"END");

}


void play(tune &r)
{

    setcolor(12);
    settextstyle(2,0,8);
    outtextxy(15,82,"playing..................");

    delay(500);
    start=clock();
    int i;
    char c;
    double x,j;
    int k=r.n;

    for(i=0; i<k; i++)
    {
        c=r.ch[i];
        x=r.t[i];
        j=0;

        while(j<=x)
        {
            end=clock();
            j=((end-start)/CLK_TCK);
        }

        key(c);
        start=end;
    }

    setcolor(12);
    settextstyle(2,0,10);
    outtextxy(15,105,"END");

}


void save(tune &r)
{

    clrscr();
    cleardevice();
    pg1();

    ifstream ifile("piano.dat",ios::in|ios::binary);
    ifile.seekg(0,ios::end);
    long size=ifile.tellg();
    ifile.close();
    int n=size/sizeof(tune);

    if(n>=35)
    {
        clrscr();
        cleardevice();
        pg1();
        cout<<"\n\n\n\n ! ! ! OVERFLOW ! ! ! \n Not Enough Memory\n Delete some tunes first\n\n\n Press any key to RETURN....\a";
        pg1();
        getch();
        return;
    }

    r.getdata();
    ofstream ofile("piano.dat",ios::app|ios::binary);

    cout<<"\n\n\n Press any key to save the tune:";
    pg1();
    ofile.write((char*)&r,sizeof(r));

    ofile.close();
    getch();
    cout<<"\n\n\n Tune is saved succesfully\n Press any key to return:";
    pg1();
    getch();

}


void del(int ref)
{

    char ch;
    tune r;
    int flag=0;
    ifstream ifile("piano.dat",ios::in|ios::binary);
    ofstream ofile("temp.dat",ios::in|ios::binary);

    ifile.seekg(0);
    while(!ifile.eof())
    {

        ifile.read((char*)&r,sizeof(r));

        if((ref==r.ret_r())&&(flag!=1))
        {

            flag=1;
            cout<<"\n\n\n\n\n Press 'Y' to confirm deletion : ";
            pg1();
            ch=getche();
            cout<<ch;

            if(ch!='Y'&&ch!='y')
            {
                ofile.write((char*)&r,sizeof(r));
            }

        }

        else
        {
            ofile.write((char*)&r,sizeof(r));
        }
    }

    ifile.close();
    ofile.close();

    remove("piano.dat");
    rename("temp.dat","piano.dat");
    last_ele();

    if(ch=='y'||ch=='Y')
    {
        cout<<"\n\n Deletion successful\n Press any key to retrun......";
    }

    else
    {
        cout<<"\n\n Element NOT deleted\n press any key to return......";
    }

    pg1();
    getch();

}


void last_ele()
{
    long x;
    int n,i;
    tune r;
    ifstream ifile("piano.dat",ios::in|ios::binary);
    ofstream ofile("temp.dat",ios::in|ios::binary);

    ifile.seekg(0,ios::end);
    x=ifile.tellg();
    n=x/sizeof(tune);
    ifile.seekg(0);
    i=1;

    while(i<n)
    {

        ifile.read((char*)&r,sizeof(r));
        ofile.write((char*)&r,sizeof(r));
        i++;

    }

    ifile.close();
    ofile.close();
    remove("piano.dat");
    rename("temp.dat","piano.dat");

}


void modification(tune &r)
{

    pg1();
    char ch;
    r.modify();
    cout<<"\n Want to MODIFY the tune also(Y/N) : ";
    pg1();
    ch=getche();

    cout<<ch;

    if(ch=='y'||ch=='Y')
    {
        self(r);
    }

}


void s_seriol_no()
{

    clrscr();
    cleardevice();
    pg1();
    int s,ch1,ch;
    tune r;

    cout<<"\n Enter seriol no. of tune:";
    pg1();
    cin>>s;

    fstream iofile("piano.dat",ios::in|ios::out|ios::binary);
    iofile.seekg(sizeof(tune)*(s-1));
    iofile.read((char*)&r,sizeof(r));

    if(iofile.eof())
    {
        cout<<"\n\n Wrong Serial no:";
        pg1();
    }

    else
    {
        clrscr();
        cleardevice();
        d_st();
        cout<<"\n\n\n "<<s;
        r.showdata();

        ch=play_yn(25,150,s,r);

        if(ch==1)
        {
            play(r);
            getch();
        }

        ch1=mod_del(150,140,s,r);

        if(ch1==1)
        {

            modification(r);
            cout<<"\n\n\n\n\n Press any key to save changes:";
            pg1();
            getch();

            iofile.seekg(sizeof(r)*(s-1));
            iofile.write((char*)&r,sizeof(r));

            cout<<"\n\n Modification successfull\n Press any key to return:";
            pg1();
            getch();

        }

        if(ch1==2)
        {

            int ref;
            iofile.seekg(sizeof(tune)*(s-1));
            iofile.read((char*)&r,sizeof(r));
            ref=r.ret_r();
            del(ref);
        }

    }

    iofile.close();

}


int s_ref()
{

    int s,ch1,ch,no,flag=0;
    tune r;
    long pos;
    clrscr();
    cleardevice();

    fstream iofile("piano.dat",ios::in|ios::out|ios::binary);

    cout<<"\n\n Enter Reference no:";
    pg1();
    cin>>no;

    iofile.seekg(0);

    while(!iofile.eof())
    {
        pos=iofile.tellg();

        iofile.read((char*)&r,sizeof(r));
        if(no==r.ret_r())
        {
            flag=1;
            cout<<"\n\n Tune FOUND\n press any key to see......";
            pg1();
            getch();

            s=(pos/sizeof(r))+1;

            clrscr();
            cleardevice();
            d_st();
            cout<<"\n\n\n "<<s;
            r.showdata();

            ch=play_yn(25,150,s,r);

            if(ch==1)
            {
                play(r);
                getch();
            }


            ch1=mod_del(150,140,s,r);

            if(ch1==1)
            {

                modification(r);
                cout<<"\n\n\n\n\n\n\n Press any key to save changes:";
                pg1();
                getch();
                iofile.seekg(sizeof(r)*(s-1));
                iofile.write((char*)&r,sizeof(r));
                cout<<"\n\n Modification successfull\n Press any key to return:";
                pg1();
                getch();
                return 1;

            }
            if(ch1==2)
            {

                int ref;
                iofile.seekg(sizeof(tune)*(s-1));
                iofile.read((char*)&r,sizeof(r));
                ref=r.ret_r();
                del(ref);
                return 1;

            }

            if(ch1==3)
                return 1;
        }
    }

    iofile.close();
    return flag;

}


int s_name()
{

    char name[100];
    int s,ch1,ch,no,flag=0;
    tune r;
    long pos;
    clrscr();
    cleardevice();

    fstream iofile("piano.dat",ios::in|ios::out|ios::binary);

    cout<<"\n\n Enter NAME:";
    pg1();
    gets(name);

    iofile.seekg(0);
    while(!iofile.eof())
    {
        pos=iofile.tellg();

        iofile.read((char*)&r,sizeof(r));

        if(strcmpi(name,r.ret_name())==0)
        {

            flag=1;
            cout<<"\n\n Tune FOUND\n press any key to see......";
            pg1();
            getch();

            s=(pos/sizeof(r))+1;

            clrscr();
            cleardevice();
            d_st();
            cout<<"\n\n\n "<<s;
            r.showdata();

            ch=play_yn(25,150,s,r);

            if(ch==1)
            {
                play(r);
                getch();
            }

            ch1=mod_del(150,140,s,r);

            if(ch1==1)
            {
                modification(r);
                cout<<"\n\n\n\n\n\n\n Press any key to save changes:";
                pg1();
                getch();
                iofile.seekg(sizeof(r)*(s-1));
                iofile.write((char*)&r,sizeof(r));
                cout<<"\n\n Modification successfull\n Press any key to return:";
                pg1();
                getch();
                return 1;
            }

            if(ch1==2)
            {

                int ref;
                iofile.seekg(sizeof(tune)*(s-1));
                iofile.read((char*)&r,sizeof(r));
                ref=r.ret_r();
                del(ref);
                return 1;
            }

            if(ch1==3)
                return 1;

        }
    }

    iofile.close();
    return flag;

}


int replay_skip()
{
    int ch=1,flag,c=25;
    char x;

    clrscr();
    cleardevice();
    pg1();

    setcolor(1);
    setfillstyle(1,7);
    bar(15,c,120,c+25);
    settextstyle(0,0,2);
    outtextxy(20,30,"Replay");
    outtextxy(20,55,"Skip");

    do
    {

        do
        {
            x=getch();

            flag=1;

            if((x!=72)&&(x!=80)&&(x!=13))
            {
                flag=0;
            }

            else
            {
                if((x==72)&&(c==25))
                    flag=0;

                else if((x==80)&&(c==50))
                    flag=0;
            }

        } while(flag==0);

        if(x==72)
        {
            setfillstyle(1,15);
            bar(15,c-25,120,c+25);
            setfillstyle(1,7);
            bar(15,c-25,120,c);

            settextstyle(0,0,2);
            outtextxy( 20,30,"Replay");
            outtextxy( 20,55,"Skip");

            c=c-25;
            ch--;

        }

        else if(x==80)
        {

            setfillstyle(1,15);
            bar(15,c,120,c+50);
            setfillstyle(1,7);
            bar(15,c+25,120,c+50);
            settextstyle(0,0,2);

            outtextxy( 20,30,"Replay");
            outtextxy( 20,55,"Skip");

            c=c+25;
            ch++;

        }


        else if(x==13)
        {
            x='y';
        }

    } while(x!='y');

    return ch;

}


int mod_del(int x1,int y1,int s,tune &r)
{

    int ch=1,flag,c=y1;
    char x;

    do
    {

        clrscr();
        cleardevice();
        d_st();
        cout<<"\n\n\n "<<s;
        r.showdata();

        setcolor(1);
        settextstyle(2,0,9);
        outtextxy(x1-50,y1-40,"OPTIONS.......");

        setfillstyle( 1, 7 );
        bar(x1-15,c,x1+100,c+25);
        setcolor(9);
        settextstyle(2,0,7);
        outtextxy(x1,y1,"Modify");
        outtextxy(x1,y1+25,"Delete");
        outtextxy(x1,y1+50,"<<return");


        do
        {

            do
            {

                x=getch();

                flag=1;

                if((x!=72)&&(x!=80)&&(x!=13))
                {
                    flag=0;
                }

                else
                {
                    if((x==72)&&(c==y1))
                        flag=0;

                    else if((x==80)&&(c==y1+50))
                        flag=0;

                }

            } while(flag==0);

            if(x==72)
            {

                setfillstyle(1,15);
                bar(x1-15,c-25,x1+110,c+25);
                setfillstyle(1,7);
                bar(x1-15,c-25,x1+110,c);

                if(ch==2)
                {

                    settextstyle(2,0,7);
                    outtextxy( x1,y1,"Modify");
                    outtextxy( x1,y1+25,"Delete");

                }

                else if(ch==3)
                {

                    settextstyle(2,0,7);
                    outtextxy( x1,y1+25,"Delete");
                    outtextxy( x1,y1+50,"<<return");

                }

                c=c-25;
                ch--;

            }

            else if(x==80)
            {

                setfillstyle(1,15);
                bar(x1-15,c,x1+110,c+50);

                setfillstyle(1,7);
                bar(x1-15,c+25,x1+110,c+50);


                if(ch==1)
                {

                    settextstyle(2,0,7);
                    outtextxy( x1,y1,"Modify");
                    outtextxy( x1,y1+25,"Delete");

                }

                else if(ch==2)
                {

                    settextstyle(2,0,7);
                    outtextxy( x1,y1+25,"Delete");
                    outtextxy( x1,y1+50,"<<return");

                }

                c=c+25;
                ch++;

            }

            else if(x==13)
            {
                x='y';
            }

        } while(x!='y');

        clrscr();
        cleardevice();
        d_st();
        cout<<"\n\n\n "<<s;
        r.showdata();

        return ch;

    } while(1);

}


int play_yn(int x1,int y1,int s,tune &r)
{

    int ch = 1,flag, c = y1-5;
    char x;

    clrscr();
    cleardevice();
    d_st();
    cout<<"\n\n\n "<<s;
    r.showdata();

    setcolor(9);
    settextstyle(1,0,2);
    outtextxy(x1,y1-30,"Wanna PLAY this TUNE.......");

    setfillstyle( 1, 7 );
    bar( x1-5, c,x1+30, c + 15 );
    settextstyle( 0, 0,1 );
    outtextxy( x1+5,y1,"YES");
    outtextxy( x1+5,y1+14,"NO");

    do
    {

        do
        {

            x=getch();

            flag=1;
            if((x!=72)&&(x!=80)&&(x!=13))
            {
                flag=0;
            }

            else
            {
                if((x==72)&&(c==y1-5))
                    flag=0;

                else if((x==80)&&(c==y1+10))
                    flag=0;

            }

        } while(flag==0);


        if(x==72)
        {
            setfillstyle(1,15);
            bar(x1-5,c-15,x1+30,c+15);
            setfillstyle(1,7);
            bar(x1-5,c-15,x1+30,c);

            settextstyle(0,0,1);
            outtextxy( x1+5,y1,"YES");
            outtextxy( x1+5,y1+14,"NO");

            c=c-15;
            ch--;

        }

        else if(x==80)
        {

            setfillstyle(1,15);
            bar(x1-5,c,x1+30,c+30);
            setfillstyle(1,7);
            bar(x1-5,c+15,x1+30,c+30);

            settextstyle(0,0,1);
            outtextxy( x1+5,y1,"YES");
            outtextxy( x1+5,y1+14,"NO");

            c=c+15;
            ch++;

        }

        else if(x==13)
        {
            x='y';
        }

    } while(x!='y');

    clrscr();
    cleardevice();
    d_st();
    cout<<"\n\n\n "<<s;
    r.showdata();

    return ch;

}


int save_yn(int x1,int y1)
{

    int ch=1,flag,c=y1-5;
    char x;

    clrscr();
    cleardevice();
    pg1();

    setcolor(1);
    settextstyle(3,0,2);
    outtextxy(15,20,"Wanna SAVE this TUNE");

    setfillstyle(1,7);
    bar(x1-5,c,x1+30,c+15);
    settextstyle(0,0,1);
    outtextxy(x1,y1,"YES");
    outtextxy(x1,y1+14,"NO");

    do
    {

        do
        {
            x=getch();

            flag=1;

            if((x!=72)&&(x!=80)&&(x!=13))
            {
                flag=0;
            }

            else
            {
                if((x==72)&&(c==y1-5))
                    flag=0;

                else if((x==80)&&(c==(y1+10)))
                    flag=0;

            }

        } while(flag==0);

        if(x==72)
        {
            setfillstyle(1,15);
            bar(x1-5,c-15,x1+30,c+15);
            setfillstyle(1,7);
            bar(x1-5,c-15,x1+30,c);

            settextstyle(0,0,1);
            outtextxy(x1,y1,"YES");
            outtextxy(x1,y1+14,"NO");

            c=c-15;
            ch--;

        }

        else if(x==80)
        {

            setfillstyle(1,15);
            bar(x1-5,c,x1+30,c+30);
            setfillstyle(1,7);
            bar(x1-5,c+15,x1+30,c+30);

            settextstyle(0,0,1);
            outtextxy(x1,y1,"YES");
            outtextxy(x1,y1+14,"NO");

            c=c+15;
            ch++;

        }

        else if(x==13)
        {
            x='y';
        }

    } while(x!='y');

    return ch;

}


void d_table()
{

    setcolor(1);
    settextstyle(1,0,1);
    outtextxy(4,10,"S.No.");
    outtextxy(72,10,"Name");
    outtextxy(310,10,"Ref.No.");
    outtextxy(430,10,"Time");

    setfillstyle(1,1);
    bar(0,0,639,2);
    bar(0,35,639,37);
    bar(0,0,2,400);
    bar(64,0,66,400);
    bar(637,0,639,400);
    bar(306,0,308,400);
    bar(426,0,428,400);
    bar(0,398,639,400);

    cout<<"\n\n\n";

}


void d_st()
{

    pg1();
    setcolor(1);
    settextstyle(1,0,1);
    outtextxy(4,10,"S.No.");
    outtextxy(72,10,"Name");
    outtextxy(310,10,"Ref.No.");
    outtextxy(430,10,"Time");

    setfillstyle(1,1);
    bar(0,0,639,2);
    bar(0,0,2,70);
    bar(0,35,639,37);
    bar(637,0,639,70);
    bar(68,0,70,70);
    bar(306,0,308,70);
    bar(426,0,428,70);
    bar(0,68,639,70);

}
