#include<string.h>
#include<stdio.h>
#include<fstream.h>
#include<time.h>
#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>

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
    cout<<"\nEnter REFERENCE NO.:";
    cin>>rno;
    flag=check_r(rno);

    if(flag==0)
    {
        cout<<"\n!!!!!!!Error ref. no. alreadry exist,enter a unique ref. no.";
        get_ref();
    }
}

int record::get_mod_ref()
{
    int flag;
    int r;

    cout<<"\nEnter new Reference no('-1' to retain previous one):";
    cin>>r;
    flag=check_r(r);

    if(flag==0)
    {
        cout<<"\n!!!!!!!Error ref. no. alreadry exist,enter a unique ref. no.";
        r=get_mod_ref();
    }
    return r;

}

void record::getdata()
{
    cout<<"\nEnter name of the tune:";
    gets(name);

    get_ref();
}

void record::showdata()
{
    int y;
    y=wherey();

    gotoxy(10,y);
    cout<<name;
    gotoxy(40,y);
    cout<<rno;
    gotoxy(50,y);
    cout<<net_t;
}

void record::modify()
{
    char n[50];
    int r;
    int flag;
    cout<<"\nEnter new name(press '.' to retain previous one):";
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

    while(!ifile.eof())
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

clock_t start,end,ct;

void key(char x);
void play(record &r);
void save(record &r);
void data_stored();
void automatic(record &rr);
void self(record &rr);
void seriol_no();
void search();
void modification(record &r);
int s_ref();
int s_name();
void del(int);
int check_r(int);
void last_ele();

void main()
{
    clrscr();
    record rr;
    int r,r1;
    int ch,ch2,ch3;
    do
    {
        clrscr();
        randomize();
        cout<<"\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PIANO~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        cout<<"\n\n\t\t\tMENU\n\t\t\t1.Play It\n\t\t\t2.Tune$\n\t\t\t3.About\n\t\t\t4.EXIT\n\t\t\tEnter your choice:";
        cin>>ch;
        if(ch==1)
        {

            do
            {
                clrscr();
                cout<<"\n\t\t\t1.Automatic\n\t\t\t2.Self\n\t\t\t3.Return to menu\n\t\t\tEnter your choice:";
                cin>>ch2;
                if(ch2==1)
                {
                    automatic(rr);
                    cout<<"\nWanna play it again(1/2):";
                    cin>>ch3;
                    if(ch3==1)
                    {
                        play(rr);
                    }
                    getch();

                    cout<<"\n\nWant to save this tune(1/2):";
                    cin>>ch3;
                    if(ch3==1)
                    {
                        save(rr);
                    }
                }
                if(ch2==2)
                {
                    self(rr);
                    cout<<"\nWanna play it again(1/2):";
                    cin>>ch3;
                    if(ch3==1)
                    {
                        play(rr);
                    }
                    getch();

                    cout<<"\n\nWant to save this tune(1/2):";
                    cin>>ch3;
                    if(ch3==1)
                    {
                        save(rr);
                    }
                }

            } while(ch2!=3);
        }
        if(ch==2)
        {
            do
            {
                clrscr();
                cout<<"\n\t\t\t1.Tunes stored\n\t\t\t2.search\n\t\t\t3.return to main\n\t\t\tEnter your choice:";
                cin>>ch2;
                if(ch2==1)
                {

                    getch();
                    data_stored();
                }
                if(ch2==2)
                {
                    search();

                }
            } while(ch2!=3);
        }

    } while(ch!=4);
    cout<<"\n\nPress any key to exit............................";
    getch();
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


void play(record &r)
{
    cout<<"\nPlaying";
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
    cout<<"\nIts Over";
}


void save(record &r)
{
    clrscr();
    r.getdata();
    ofstream ofile("piano.dat",ios::app|ios::binary);
    cout<<"\n\nPress any key to save the tune:";
    ofile.write((char*)&r,sizeof(r));
    ofile.close();
    getch();
    cout<<"\n\nTune is saved succesfully\nPress any key to return:";
    getch();

}


void automatic(record &rr)
{
    randomize();
    char x;
    int k,r,z;
    rr.t[0]=0;
    x=rr.ch[0]=random(10)+47;
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
    cout<<"\n\nIts Over";
}

void self(record &rr)
{

    char x;
    int k;
    rr.t[0]=0;
    x=rr.ch[0]=getch();
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
    cout<<"\n\nIts Over";
}





void data_stored()
{
    clrscr();
    int i,j;
    gotoxy(1,2);
    cout<<"S.No.";
    gotoxy(10,2);
    cout<<"Name";
    gotoxy(40,2);
    cout<<"Ref.No.";
    gotoxy(50,2);
    cout<<"Time";

    cout<<"\n";

    for(j=1; j<=80; j++)
    {
        delay(10);
        cout<<"=";
    }
    cout<<endl;
    i=1;
    record r;
    ifstream ifile("piano.dat",ios::in|ios::binary);

    ifile.seekg(0);
    while(!ifile.eof())
    {

        if(i%40==0)
        {
            getch();
            gotoxy(1,2);
            cout<<"S.No.";
            gotoxy(10,2);
            cout<<"Name";
            gotoxy(40,2);
            cout<<"Ref.No.";
            gotoxy(50,2);
            cout<<"Time";
            cout<<"\n";

            for(j=1; j<=80; j++)
            {
                cout<<"=";
            }
            cout<<endl;

        }

        ifile.read((char*)&r,sizeof(r));
        if(ifile.eof())break;
        cout<<i;
        r.showdata();
        i++;
        cout<<"\n";

    }

    ifile.close();

    getch();

    gotoxy(5,48);
    char chc;
    cout<<"Press 'S' to see a specific record:";
    chc=getche();
    if(chc=='S'||chc=='s')
    {
        seriol_no();
    }
}



void seriol_no()
{
    clrscr();
    int s;
    record r;
    char ch;
    cout<<"\nEnter seriol no. of tune:";
    cin>>s;

    fstream iofile("piano.dat",ios::in|ios::out|ios::binary);
    iofile.seekg(sizeof(record)*(s-1));
    iofile.read((char*)&r,sizeof(r));
    if(iofile.eof())
    {
        cout<<"\nWrong Serial no:";
    }

    else
    {
        getch();
        gotoxy(1,5);
        cout<<"S.No.";
        gotoxy(10,5);
        cout<<"Name";
        gotoxy(40,5);
        cout<<"Ref.No.";
        gotoxy(50,5);
        cout<<"Time";
        cout<<"\n";

        for(int j=1; j<=80; j++)
        {
            cout<<"=";
        }

        cout<<"\n";
        cout<<s;
        r.showdata();
        cout<<"\n\n\n\nWant to play this tune (Y/N):";
        ch=getche();
        if(ch=='y'||ch=='Y')
        {
            play(r);
        }
        cout<<"\n\n\t\t\t1.To modify\n\t\t\t2.To delete\n\t\t\t3To return";
        ch=getche();
        if(ch=='1')
        {
            modification(r);
            cout<<"\n\nPress any key to save changes:";
            getch();
            iofile.seekg(sizeof(r)*(s-1));
            iofile.write((char*)&r,sizeof(r));
            cout<<"\n\nModification successfull\nPress any key to return:";
        }
        if(ch=='2')
        {
            int ref;
            iofile.seekg(sizeof(record)*(s-1));
            iofile.read((char*)&r,sizeof(r));
            ref=r.ret_r();
            del(ref);
        }
    }
    iofile.close();
    getch();
}

void modification(record &r)
{
    char ch;
    r.modify();
    cout<<"\nWant to modify the tune also(Y/N):";
    ch=getche();
    if(ch=='y'||ch=='Y')
    {
        self(r);
    }

}

void search()
{
    int flag;
    int ch;
    do
    {
        clrscr();
        cout<<"\n\t\t\tSearch by:-\n\t\t\t1.reference no\n\t\t\t2.name\n\n\n\t\t\t3.return to previous menu\n\n\nEnter your choice:";
        cin>>ch;
        if(ch==1)
        {
            flag=s_ref();
            if(flag==0)
            {
                cout<<"\n\nRecord not found:";
                getch();
            }

            cout<<"\nPress any key to return to the menu:";
            getch();

        }

        if(ch==2)
        {
            flag=s_name();
            if(flag==0)
            {
                cout<<"\n\nRecord not found:";
                getch();
            }
            cout<<"\nPress any key to return to the menu:";
            getch();

        }


    } while(ch!=3);

}

int s_ref()
{
    clrscr();
    int ch,no;
    char ch1;
    long pos;
    record r;
    fstream iofile("piano.dat",ios::in|ios::out|ios::binary);

    cout<<"\n\nEnter Reference no:";
    cin>>no;

    iofile.seekg(0);
    while(!iofile.eof())
    {
        pos=iofile.tellg();

        iofile.read((char*)&r,sizeof(r));
        if(no==r.ret_r())
        {
            cout<<"\n\nRecord found\n\n";
            gotoxy(10,5);
            cout<<"Name";
            gotoxy(40,5);
            cout<<"Ref.No.";
            gotoxy(50,5);
            cout<<"Time";
            cout<<"\n";
            for(int j=1; j<=80; j++)
            {
                cout<<"=";
            }
            cout<<"\n";
            r.showdata();
            cout<<"\n\n\n\nWant to play this tune (Y/N):";
            ch1=getche();
            if(ch1=='y'||ch1=='Y')
            {
                play(r);
            }
            getch();
            cout<<"\n\n\t\t\t1.To modify\n\t\t\t2.To delete\n\t\t\t3.To return";
            ch1=getche();
            if(ch1=='1')
            {
                modification(r);
                cout<<"\n\nPress any key to save changes:";
                getch();
                iofile.seekg(pos);
                iofile.write((char*)&r,sizeof(r));
                cout<<"\n\nModification successfull\nPress any key to return:";
                getch();

            }
            if(ch1=='2')
            {
                int ref;
                iofile.seekg(pos);
                iofile.read((char*)&r,sizeof(r));
                ref=r.ret_r();
                del(ref);
            }
            iofile.close();
            return 1;
        }
    }
    iofile.close();
    return 0;
}

int s_name()
{
    clrscr();
    int ch;
    char name[100];
    char ch1;
    long pos;
    record r;
    fstream iofile("piano.dat",ios::in|ios::out|ios::binary);


    cout<<"\n\nEnter Name of the tune:";
    gets(name);

    iofile.seekg(0);
    while(!iofile.eof())
    {
        pos=iofile.tellg();
        iofile.read((char*)&r,sizeof(r));
        if(strcmpi(name,r.ret_name())==0)
        {
            cout<<"\n\nRecord found\n\n";
            gotoxy(10,5);
            cout<<"Name";
            gotoxy(40,5);
            cout<<"Ref.No.";
            gotoxy(50,5);
            cout<<"Time";
            cout<<"\n";
            for(int j=1; j<=80; j++)
            {
                cout<<"=";
            }
            cout<<"\n";
            r.showdata();
            cout<<"\n\n\n\nWant to play this tune (Y/N):";
            ch1=getche();
            if(ch1=='y'||ch1=='Y')
            {
                play(r);
            }
            getch();
            cout<<"\n\n\t\t\t1.To modify\n\t\t\t2.To delete\n\t\t\t3.To return";
            ch1=getche();
            if(ch1=='1')
            {
                modification(r);
                cout<<"\n\nPress any key to save changes:";
                getch();
                iofile.seekg(pos);
                iofile.write((char*)&r,sizeof(r));
                cout<<"\n\nModification successfull\nPress any key to return:";
                getch();

            }
            if(ch1=='2')
            {
                int ref;
                iofile.seekg(pos);
                iofile.read((char*)&r,sizeof(r));
                ref=r.ret_r();
                del(ref);
            }

            iofile.close();
            return 1;
        }
    }
    iofile.close();
    return 0;
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
            cout<<"\nPress 'Y' to confirm deletion:";
            ch=getche();
            if(ch!='Y'&&ch!='y')
                ofile.write((char*)&r,sizeof(r));
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