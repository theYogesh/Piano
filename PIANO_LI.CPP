
#include<graphics.h>
#include<string.h>
#include<stdio.h>
#include<fstream.h>
#include<time.h>
#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>

void pg1();

clock_t start,end,ct;


class record
{
    char name[50];
    int rno;

    int check_r(int re);
public:
    double t[200];
    char ch[200];
    int n;

    double net_t;
    void get_ref();
    int get_mod_ref();
    void getdata();
    void showdata();
    void modify();

    int ret_r()
    {
        return rno;
    }

    char* ret_name()
    {
        return name;
    }
};

void record::get_ref()
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

int record::get_mod_ref()
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

void record::getdata()
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

void record::showdata()
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

void record::modify()
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

int record::check_r(int re)
{
    record r;
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




void startp();
void menu1();
void menu2();
void menu3();
void m11();
void m12();
void automatic(record &rr);
void key(char x);
int yn(int x1,int y1);
int rs();
void play(record &r);
void save(record &r);
void m21();
void m22();
void data_stored();
void seriol_no();
void modification(record &r);
void del(int);
void last_ele();
void d_table();
void d_st();
int m_yn(int x1,int y1,int s,record &r);
int s_yn(int x1,int y1,int x,record &r);
int menu22();
int s_ref();
int s_name();
void search();



void main()
{
    int i;
    int gdriver = DETECT, gmode, errorcode;
    initgraph( &gdriver, &gmode, "" );
    cleardevice();
    startp();
    closegraph();

}


void startp()
{
    int i;
    setbkcolor(7);
    getch();
    for (i = 1; !kbhit(); i++ )
    {
        cleardevice();
        if(i<=510)
        {
            setfillstyle(1,15);
            bar(i,0,getmaxx(),getmaxy()-i);
        }
        if(i<=350)
        {
            if(i%2==0)
                setcolor(9);
            else
                setcolor(12);
            settextstyle( 4, HORIZ_DIR, 18 );
            outtextxy(80,-100+i, "Piano" );
            setcolor(1);
            settextstyle(2,0,7);
            outtextxy(706-(i*2),425, "made by:" );
            outtextxy(706-(i*2),450, "Yoge$h & $hivank" );
            delay(10);
        }
        if(i>510)
            break;
    }
    setbkcolor(15);
    delay(200);
    clrscr();
    cleardevice();

    pg1();
    menu1();

}

void pg1()
{

    setcolor(12);
    settextstyle( 4, HORIZ_DIR, 18 );
    outtextxy(79,250, "Piano" );
    setcolor(4);
    outtextxy(80,250, "Piano" );
    setcolor(9);
    settextstyle(2,0,7);
    outtextxy(6,425, "made by:" );
    outtextxy(6,450, "Yoge$h & $hivank" );

}

void menu1()
{
    int ch = 1, x, c = 80;

    do
    {
        do
        {

            clrscr();
            cleardevice();
            pg1();
            setcolor(1);
            settextstyle(3, 0, 5 );
            outtextxy( 50,25, "MENU" );
            setfillstyle( 1, 7 );
            bar( 150,44,625,49);
            bar( 150,54,625,59);

            setfillstyle( 1, 7 );
            bar( 50, c,220, c + 25 );

            settextstyle( 0, 0,2 );
            setcolor( 1 );
            outtextxy( 70, 85, "Play iT" );
            outtextxy( 70, 115, "iTune$" );
            outtextxy( 70, 145, "ExIT" );

            x=getch();

            if(x==72)
            {

                if ( c > 80 )
                {
                    c = c-30;
                    ch--;
                }
            }
            else if(x==80)
            {
                if ( c < 120 )
                {
                    c= c+30;
                    ch++;
                };
            }
            else if(x==13)
            {
                x='y';
            }




        } while ( x != 'y' );

        switch ( ch )
        {
        case 1:
            menu2();
            break;
        case 2:
            menu3();
            break;

        case 3:
            exit( 0 );
            break;
        }
    } while (1);

    getch();
}

void menu2()
{

    int ch = 1, x, c = 110;

    do
    {
        do
        {

            clrscr();
            cleardevice();
            pg1();
            setcolor(1);
            settextstyle(3, 0, 5 );
            outtextxy( 50,25, "MENU" );
            setfillstyle( 1, 7 );
            bar( 150,44,625,49);
            bar( 150,54,625,59 );
            settextstyle( 0, 0,2 );
            setcolor( 1 );

            setfillstyle( 1, 7 );
            bar( 105, c,330, c + 25 );

            outtextxy( 70, 85, "Play iT" );

            settextstyle( 0, 0,2 );
            outtextxy( 125,115,"Automatic");
            outtextxy( 125,145,"Try yourself");
            outtextxy( 125,175,"<<return");

            settextstyle( 0, 0,2 );
            outtextxy( 70, 205, "iTune$" );
            outtextxy( 70, 235, "EXIT" );




            x=getch();

            if(x==72)
            {

                if ( c > 110 )
                {
                    c = c-30;
                    ch--;
                }
            }
            else if(x==80)
            {
                if ( c < 150 )
                {
                    c= c+30;
                    ch++;
                };
            }
            else if(x==13)
            {
                x='y';
            }




        } while ( x != 'y' );

        switch ( ch )
        {
        case 1:
            m11();
            break;
        case 2:
            m12();
            break;

        case 3:
            return;
            break;
        }
    } while (1);

    getch();
}

void menu3()
{

    int ch = 1, x, c = 140;

    do
    {
        do
        {

            clrscr();
            cleardevice();
            pg1();
            setcolor(1);
            settextstyle(3, 0, 5 );
            outtextxy( 50,25, "MENU" );
            setfillstyle( 1, 7 );
            bar( 150,44,625,49);
            bar( 150,54,625,59 );
            settextstyle( 0, 0,2 );
            setcolor( 1 );

            setfillstyle( 1, 7 );
            bar( 105, c,280, c + 25 );

            outtextxy( 70, 85, "Play iT" );
            outtextxy( 70, 115, "iTune$" );

            settextstyle( 0, 0,2 );
            outtextxy( 125,145,"List ALL");
            outtextxy( 125,175,"Search");
            outtextxy( 125,205,"<<return");

            settextstyle( 0, 0,2 );
            outtextxy( 70, 235, "EXIT" );




            x=getch();

            if(x==72)
            {

                if ( c > 140 )
                {
                    c = c-30;
                    ch--;
                }
            }
            else if(x==80)
            {
                if ( c < 180 )
                {
                    c= c+30;
                    ch++;
                };
            }
            else if(x==13)
            {
                x='y';
            }




        } while (x!='y');

        switch (ch)
        {
        case 1:
            m21();
            break;
        case 2:
            m22();
            break;

        case 3:
            return;
            break;
        }
    } while (1);

    getch();
}


void m11()
{
    record r;
    char x[2];
    clrscr();
    cleardevice();
    pg1();
    int ch2;
    setcolor(1);
    settextstyle(2,0,10);
    outtextxy(15,25,"Start in");
    delay(25);
    for(int i=3; i>=0; i--)
    {
        delay(999);
        x[0]=48+i;
        x[1]='\0';
        clrscr();
        cleardevice();
        pg1();
        setcolor(1);
        settextstyle(2,0,10);
        outtextxy(15,25,"Start in");
        if(i==0)
        {
            setcolor(12);
            settextstyle(1,0,6);
            outtextxy(190,75,"START");
            cout<<"\a";
            delay(500);
            clrscr();
            cleardevice();
            pg1();
            setcolor(1);
            settextstyle(2,0,10);
            outtextxy(15,25,"Start in");
            break;
        }

        setcolor(12);
        settextstyle(1,0,10);
        outtextxy(250 ,25,x);
    }

    automatic(r);
    getch();
    cleardevice();
    ch2=rs();
    if(ch2==1)
    {
        play(r);
    }


    clrscr();
    cleardevice();
    ch2=yn(20,55);
    if(ch2==1)
    {
        save(r);
    }
}

void automatic(record &rr)
{
    randomize();
    char x;
    int k,r,z;
    rr.t[0]=0;
    x=rr.ch[0]=random(10)+47;

    setcolor(12);
    settextstyle(2,0,8);
    outtextxy(15,100,"playing..................");
    z=random(50)+15;
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




void key(char x)
{


    if(x=='a'||x=='1')
    {
        sound(1000);


    }
    else if(x=='s'||x=='2')
    {
        sound(1500);


    }
    else if(x=='d'||x=='3')
    {
        sound(2000);


    }
    else if(x=='f'||x=='4')
    {
        sound(2500);


    }
    else if(x=='g'||x=='5')
    {
        sound(3000);


    }
    else if(x=='h'||x=='6')
    {
        sound(3500);


    }
    else if(x=='j'||x=='7')
    {
        sound(4000);


    }
    else if(x=='k'||x=='8')
    {
        sound(4500);

    }
    else if(x=='l'||x=='9')
    {
        sound(5000);

    }
    else if(x==';'||x=='0')
    {
        sound(5500);

    }
    else if(x=='-'||x=='"')
    {
        sound(6000);
    }

    delay(200);
    nosound();
}

void self(record &rr)
{

    char x;
    int k;
    rr.t[0]=0;
    x=rr.ch[0]=getch();
    key(x);
    setcolor(12);
    settextstyle(2,0,8);
    outtextxy(15,100,"playing..................");

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



void m12()
{
    record r;
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
        delay(999);
        x[0]=48+i;
        x[1]='\0';
        clrscr();
        cleardevice();
        pg1();
        setcolor(1);
        settextstyle(2,0,10);
        outtextxy(15,25,"Start in");
        if(i==0)
        {
            setcolor(12);
            settextstyle(1,0,6);
            outtextxy(190,75,"START");
            cout<<"\a";
            delay(500);
            clrscr();
            cleardevice();
            pg1();
            setcolor(1);
            settextstyle(2,0,10);
            outtextxy(15,25,"Start in");
            break;
        }

        setcolor(12);
        settextstyle(1,0,10);
        outtextxy(250 ,25,x);
    }

    setcolor(12);
    settextstyle(0,0,1);
    outtextxy(15,180,"press ENTER to END");
    self(r);
    getch();
    cleardevice();
    ch2=rs();
    if(ch2==1)
    {
        play(r);
    }

    clrscr();
    cleardevice();

    ch2=yn(20,55);
    if(ch2==1)
    {
        save(r);
    }
}





int yn(int x1,int y1)
{
    int ch = 1, x, c = y1-5;

    do
    {
        do
        {
            clrscr();
            cleardevice();
            pg1();

            setcolor(1);
            settextstyle(3,0,2);
            outtextxy(15,20,"Wanna SAVE this TUNE");

            setfillstyle( 1, 7 );
            bar( x1-5, c,x1+30, c + 15 );
            settextstyle( 0, 0,1 );
            outtextxy( x1,y1,"YES");
            outtextxy( x1,y1+14,"NO");

            x=getch();

            if(x==72)
            {

                if ( c > y1 )
                {
                    c = c-15;
                    ch--;
                }
            }
            else if(x==80)
            {
                if ( c < y1+1 )
                {
                    c= c+15;
                    ch++;
                };
            }
            else if(x==13)
            {
                x='y';
            }




        } while ( x != 'y' );

        switch ( ch )
        {
        case 1:
            return 1;
            break;
        case 2:
            return 2;
            break;
        }
    } while (1);

}

int rs()
{
    int ch = 1, x, c = 25;

    do
    {
        do
        {

            clrscr();
            cleardevice();
            pg1();

            setcolor(1);
            setfillstyle( 1, 7 );
            bar(15,c,120,c+25 );
            settextstyle( 0, 0,2 );
            outtextxy( 20,30,"Replay");
            outtextxy( 20,55,"Skip");

            x=getch();

            if(x==72)
            {

                if ( c > 25 )
                {
                    c = c-25;
                    ch--;
                }
            }
            else if(x==80)
            {
                if ( c < 32 )
                {
                    c= c+25;
                    ch++;
                };
            }
            else if(x==13)
            {
                x='y';
            }




        } while ( x != 'y' );

        switch ( ch )
        {
        case 1:
            return 1;
            break;
        case 2:
            return 2;
            break;
        }
    } while (1);

}

void play(record &r)
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


void save(record &r)
{
    clrscr();
    cleardevice();
    pg1();
    r.getdata();
    ofstream ofile("piano.dat",ios::app|ios::binary);
    cout<<"\n\n Press any key to save the tune:";
    pg1();
    ofile.write((char*)&r,sizeof(r));
    ofile.close();
    getch();
    cout<<"\n\n Tune is saved succesfully\n Press any key to return:";
    pg1();
    getch();

}

void m21()
{
    data_stored();
}

void m22()
{
    int ch;
    int flag;


    do
    {
        ch=menu22();
        if(ch==1)
        {

            flag=s_ref();
            if(flag==0)
            {
                cout<<"\n\n Record NOT FOUND:\n press any key to return.....";
                pg1();
                getch();
            }
        }

        if(ch==2)
        {


            flag=s_name();
            if(flag==0)
            {
                cout<<"\n\n Record NOT FOUND:\n press any key to return.....";
                pg1();
                getch();
            }

        }

        if(ch==3)
        {
            break;
        }


    } while(1);

}



int s_ref()
{
    int s,ch1,ch,no,flag=0;
    record r;
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

            ch=s_yn(25,150,s,r);

            if(ch==1)
            {
                play(r);
                getch();
            }


            ch1=m_yn(150,140,s,r);

            if(ch1==1)
            {
                modification(r);
                cout<<"\n\n\n\n\n\n\n\n Press any key to save changes:";
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
                iofile.seekg(sizeof(record)*(s-1));
                iofile.read((char*)&r,sizeof(r));
                ref=r.ret_r();
                del(ref);
            }
        }
    }
    iofile.close();
    return flag;
}

int s_name()
{

    char name[100];
    int s,ch1,ch,no,flag=0;
    record r;
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

            ch=s_yn(25,150,s,r);

            if(ch==1)
            {
                play(r);
                getch();
            }


            ch1=m_yn(150,140,s,r);

            if(ch1==1)
            {
                modification(r);
                cout<<"\n\n\n\n\n\n\n\n Press any key to save changes:";
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
                iofile.seekg(sizeof(record)*(s-1));
                iofile.read((char*)&r,sizeof(r));
                ref=r.ret_r();
                del(ref);
            }
        }
    }
    iofile.close();
    return flag;

}






void data_stored()
{
    clrscr();
    cleardevice();
    d_table();
    int i,j;
    record r;
    i=1;
    ifstream ifile("piano.dat",ios::in|ios::binary);

    ifile.seekg(0);
    gotoxy(0,3);
    while(!ifile.eof())
    {

        if(i%21==0)
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
        if(ifile.eof())break;
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
        seriol_no();
    }
}

void seriol_no()
{
    clrscr();
    cleardevice();
    pg1();
    int s,ch1,ch;
    record r;
    cout<<"\n Enter seriol no. of tune:";
    pg1();
    cin>>s;

    fstream iofile("piano.dat",ios::in|ios::out|ios::binary);
    iofile.seekg(sizeof(record)*(s-1));
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

        ch=s_yn(25,150,s,r);

        if(ch==1)
        {
            play(r);
            getch();
        }


        ch1=m_yn(150,140,s,r);

        if(ch1==1)
        {
            modification(r);
            cout<<"\n\n\n\n\n\n\n\n Press any key to save changes:";
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
            iofile.seekg(sizeof(record)*(s-1));
            iofile.read((char*)&r,sizeof(r));
            ref=r.ret_r();
            del(ref);
        }
    }
    iofile.close();
}



void modification(record &r)
{
    pg1();
    char ch;
    r.modify();
    cout<<"\n Want to MODIFY the tune also(Y/N):";
    pg1();
    ch=getche();
    if(ch=='y'||ch=='Y')
    {
        self(r);
    }

}


void del(int ref)
{

    char ch;
    record r;
    ifstream ifile("piano.dat",ios::in|ios::binary);
    ofstream ofile("temp.dat",ios::in|ios::binary);

    ifile.seekg(0);
    while(!ifile.eof())
    {
        ifile.read((char*)&r,sizeof(r));
        if(ref==r.ret_r())
        {
            cout<<"\n\n\n\n\n Press 'Y' to confirm deletion:";
            pg1();
            ch=getche();
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
    record r;
    ifstream ifile("piano.dat",ios::in|ios::binary);
    ofstream ofile("temp.dat",ios::in|ios::binary);

    ifile.seekg(0,ios::end);
    x=ifile.tellg();
    n=x/sizeof(record);
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



void d_table()
{
    setcolor(1);
    settextstyle(1,0,1);
    outtextxy(4,10,"S.No.");
    outtextxy(72,10,"Name");
    outtextxy(310,10,"Ref.No.");
    outtextxy(430,10,"Time");
    setfillstyle(1,1);
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

int m_yn(int x1,int y1,int s,record &r)
{
    int ch = 1, x, c = y1-5;

    do
    {
        do
        {


            clrscr();
            cleardevice();
            d_st();
            cout<<"\n\n\n "<<s;
            r.showdata();

            setcolor(1);
            settextstyle( 2, 0,9 );
            outtextxy( x1-50,y1-40,"OPTIONS.......");

            setfillstyle( 1, 7 );
            bar( x1-25, c,x1+100, c + 30 );
            setcolor(9);
            settextstyle( 2, 0,7 );
            outtextxy( x1,y1,"Modify");
            outtextxy( x1,y1+25,"Delete");
            outtextxy( x1,y1+50,"<<return");
            x=getch();

            if(x==72)
            {

                if ( c > y1 )
                {
                    c = c-25;
                    ch--;
                }
            }
            else if(x==80)
            {
                if ( c < y1+40 )
                {
                    c= c+25;
                    ch++;
                };
            }
            else if(x==13)
            {
                x='y';
            }




        } while ( x != 'y' );



        clrscr();
        cleardevice();
        d_st();
        cout<<"\n\n\n "<<s;
        r.showdata();

        return ch;
    } while (1);



}

int s_yn(int x1,int y1,int s,record &r)
{

    int ch = 1, x, c = y1-5;

    do
    {
        do
        {


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

            x=getch();

            if(x==72)
            {

                if ( c > y1 )
                {
                    c = c-15;
                    ch--;
                }
            }
            else if(x==80)
            {
                if ( c < y1+1 )
                {
                    c= c+15;
                    ch++;
                };
            }
            else if(x==13)
            {
                x='y';
            }




        } while ( x != 'y' );



        clrscr();
        cleardevice();
        d_st();
        cout<<"\n\n\n "<<s;
        r.showdata();



        switch ( ch )
        {
        case 1:
            return 1;
            break;
        case 2:
            return 2;
            break;
        }
    } while (1);



}

int menu22()
{

    int ch = 1, x, c = 95;

    do
    {
        do
        {

            clrscr();
            cleardevice();
            pg1();

            setcolor( 9 );
            settextstyle( 3, 0,5 );
            outtextxy( 40, 35, "SEARCH BY:" );

            setfillstyle( 1, 7 );
            bar( 65, c,300, c + 24 );

            setcolor( 1 );
            settextstyle( 0, 0,2 );
            outtextxy( 90, 100, "REFERENCE NO" );
            outtextxy( 90, 130, "NAME" );
            outtextxy( 90, 160, "<<return" );

            x=getch();

            if(x==72)
            {

                if ( c > 100 )
                {
                    c = c-30;
                    ch--;
                }
            }
            else if(x==80)
            {
                if ( c < 140 )
                {
                    c= c+30;
                    ch++;
                };
            }
            else if(x==13)
            {
                x='y';
            }




        } while ( x != 'y' );

        return ch;


    } while (1);

}