//******************************************
//Header files
//******************************************
#include <string.h>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
//******************************************
//Global Objects(variables, identifiers, etc)
//******************************************
using namespace std;
char gl[60];//To store scrambled word
char san[60];//To store answer
int status[2]={0,0};//To store various user choices
int xstart=36;//Variables to make boxes and display letters
int ystart=6;//......
int yend=14;//.......
int xend;//.........
int gr2=0;//A choice variable
int gr=0;//A choice variable
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);//For changing coordinates
COORD CursorPosition;//For getting coordinates
fstream hg;//A global file variable used only for highscore file
//*****************************************
//FUNCTION PROTOTYPES
//*****************************************
int arrowkey(int yi,int yf);
void choice();
void choice1();
void choice2();
void gotoXY(int x,int y);
//******************************************
//Class used
//******************************************
class highscore
{
    int maxstreak,totalgames,level;
    char nam[25];
public:
    void create(int streak,int total,char na[25],int l)
    {
        level=l;
        maxstreak=streak;
        totalgames=total;
        strcpy(nam,na);
    }
    int rettot()
    {
        return totalgames;
    }
    void show()
    {
        cout<<"LEVEL                                  : ";
        switch(level)
        {
            case 0:puts("EASY");
                   break;
            case 1:puts("MEDIUM");
                   break;
            case 2:puts("HARD");
                   break;
            case 3:puts("FIENDISH");
                   break;
        }
        cout<<"NAME                                   : ";
        puts(nam);
        cout<<"MAX SCORE                              : "<<maxstreak<<endl;
        cout<<"TOTAL NO. OF GAMES PLAYED IN THIS LEVEL: "<<totalgames<<endl;

    }
    highscore()
    {
       strcpy(nam,"NOT AVAILABLE");
       maxstreak=0;
       totalgames=0;
    }
    int retstre()
    {
       return maxstreak;
    }
    char* retname()
    {
       return nam;
    }
    int retlevel()
    {
       return level;
    }
};//class ends here
highscore lev;
//******************************************
//Functions
//******************************************
//Function to reset the highscore file
void writer()
{
   char n[25];
   strcpy(n,"NOT AVAILABLE");
   hg.open("high.dat",ios::out|ios::binary);
   for(int i=0;i<4;i++)
   {
     lev.create(0,0,n,i);
     hg.write((char*)&lev,sizeof(highscore));
   }
   hg.close();
}
//Function to update total games
void newriter(int i)
{
   int pos,no,found=0,to;
   char *n;
   hg.open("high.dat",ios::in|ios::out|ios::binary);
   while(hg.read((char*)&lev,sizeof(highscore))&&!found)
   {
     int g=lev.rettot();
     to=lev.retstre();
     n=lev.retname();
     if(i==lev.retlevel())
     {
       pos=-1*sizeof(lev);
       hg.seekp(pos,ios::cur);
       lev.create(to,g+1,n,i);
       hg.write((char*)&lev,sizeof(highscore));
       found=1;
     }
   }
   hg.close();
}
//Function to update highscore
void update(int h,int i)
{
   int pos,no,found=0;
   char n[25];
   hg.open("high.dat",ios::in|ios::out|ios::binary);
   while(hg.read((char*)&lev,sizeof(highscore))&&!found)
   {
     int g=lev.rettot()+1;
     if(i==lev.retlevel())
     {
       if(lev.retstre()<h)
       {
         system("cls");
         gotoXY(35,0);
         cout<<"Scramble your head";
         gotoXY(35,5);
         cout<<"You scored high in this level.."<<endl;
         gotoXY(35,10);
         cout<<"Enter your name: ";
         scanf(" %19[^\n]", n);
         pos=-1*sizeof(lev);
         hg.seekp(pos,ios::cur);
         lev.create(h,g+1,n,i);
         hg.write((char*)&lev,sizeof(highscore));
         gotoXY(35,20);
         cout<<"High score saved, press any key!!\n";
         getch();
       }
        found=1;
      }
    }
    hg.close();
}
//Function to display highscores
void display_sp()
{
    hg.open("high.dat",ios::in|ios::binary);
    cout<<endl;
    cout<<endl;
    cout<<"        HIGH SCORES FOR ALL LEVELS"<<endl;
    cout<<"========================================================"<<endl;
    while(hg.read((char*)&lev,sizeof(highscore)))
    {
      lev.show();
      cout<<"========================================================"<<endl;
    }
    cout<<endl;
    cout<<"Press any key to continue"<<endl;
    getch();
    hg.close();
}
//Function to set sursor position
void gotoXY(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console,CursorPosition);
}
//Function to draw a box
void box(int l,int x,int y)
{
    char pv=179,ph=196,pc1=218,pc2=191,pc3=192,pc4=217;//ASCII Codes for box shapes
    int x1=36+x,x2=37+x,x3=35+x,y1=5+y,y2=6+y,y3=7+y;
    gotoXY(x1,y1);
    cout<<ph;
    gotoXY(x3,y2);
    cout<<pv;
    gotoXY(x1,y3);
    cout<<ph;
    gotoXY(x2,y2);
    cout<<pv;
    gotoXY(x3,y1);
    cout<<pc1;
    gotoXY(x2,y1);
    cout<<pc2;
    gotoXY(x3,y3);
    cout<<pc3;
    gotoXY(x2,y3);
    cout<<pc4;
    l--;
    while(l)
    {
        x1=x1+3;
        x2=x2+3;
        x3=x3+3;
        gotoXY(x3,y2);
        cout<<pv;
        gotoXY(x3,y1);
        cout<<pc1;
        gotoXY(x3,y3);
        cout<<pc3;
        gotoXY(x1,y1);
        cout<<ph;
        gotoXY(x1,y3);
        cout<<ph;
        gotoXY(x2,y1);
        cout<<pc2;
        gotoXY(x2,y3);
        cout<<pc4;
        gotoXY(x2,y2);
        cout<<pv;
        l--;
    }
    xend=x1;
}
//Fuction to display characters in box
void display(char s[60],int l)
{
    box(l,0,0);
    int x1=xstart;
    int y1=ystart;
    for(int i=0;i<l;i++)
    {
       gotoXY(x1,y1);
       cout<<s[i];
       x1=x1+3;
    }
}
//The main interface of the game
void disgame(char s[60],int tot)
{

    int l=0,i,x=xstart,y=ystart,ch;
    for(l=0;s[l]!='\0';l++);
    for(int j=0;j<l;j++)
        san[j]=' ';
    san[l]='\0';
    gotoXY(35,0);//The end point is 79 and 20
    cout<<"Scramble your head";
    gotoXY(35,2);
    cout<<"SCORE: "<<tot;
    display(s,l);
    box(l,0,8);
    gotoXY(x,y);
    int co=0;
    while(1)
    {
      ch=getch();
      if(ch==224)
      { ch=getch();
        if(ch==77)//right
          (x==xend)?x=xstart:x=x+3;
        if(ch==75)//left
          (x==xstart)?x=xend:x=x-3;
        if(ch==72)//up
          (y==ystart)?y=yend:y=ystart;
        if(ch==80)//down
          (y==yend)?y=ystart:y=yend;
        gotoXY(x,y);
      }
    else if(ch==13)
      {
        i=(x-xstart)/3;
        if(s[i]!=' '&&y==ystart)
          {
           int k;
           for(k=0;san[k]!=' ';k++);
           san[k]=s[i];
           gotoXY(x,y);
           cout<<" ";
           gotoXY(xstart+k*3,y+8);
           cout<<s[i];
           s[i]=' ';
           gotoXY(x,y);
           co++;
          }
        else if(san[i]!=' '&&y==yend)
          {
           int k;
           for(k=0;s[k]!=' ';k++);
           s[k]=san[i];
           gotoXY(x,y);
           cout<<" ";
           gotoXY(xstart+k*3,ystart);
           cout<<s[k];
           san[i]=' ';
           gotoXY(x,y);
           co--;
          }
          if(co==l)
           {
            gotoXY(35,19);
            cout<<"PLEASE CHECK YOUR ANSWER!!";
            gotoXY(35,21);
            cout<<"Are you sure of your answer?";
            gotoXY(35,23);
            cout<<"1.YES";
            gotoXY(35,25);
            cout<<"2.NO";
            int r=arrowkey(23,25);
            for(int xcle=33;xcle<79;xcle++)
                for(int ycle=19;ycle<27;ycle+=2)
                 {
                  gotoXY(xcle,ycle);
                  cout<<" ";
                 }
           if(r)
            {
              co=l-1;
              s[0]=san[i];
              san[i]=' ';
              gotoXY(xstart+i*3,yend);
              cout<<" ";
              gotoXY(xstart,ystart);
              cout<<s[0];
              gotoXY(xstart,ystart);
              x=xstart;
              y=ystart;
              i=0;
            }
        if(r==0)
            break;
          }
      }
    }
    gotoXY(0,30);
}
//Function to separate common length words
//Logic: This function will read words of similar lenght from TEST.txt and write to a file called LEVEL.txt
void levelfinder(int num)
{
    string line;
    ifstream f ("TEST.txt");
    ofstream fp("LEVEL.txt");
    if(!fp||!f)
    {
        system("cls");
        gotoXY(20,10);
        perror("SYSTEM ERROR CONTACT DEVELOPER");
        Sleep(1000);
        exit(0);
    }
    while( getline(f, line) )
        {
        if(line.size()==num)
          fp<< line << endl;
        }
    f.close();
    fp.close();
}
void levelfinder2(int num)
 {
    string line;
    ifstream f ("TEST2.txt");
    ofstream fp("LEVEL2.txt");
    if(!fp||!f)
    {
        system("cls");
        gotoXY(20,10);
        perror("SYSTEM ERROR CONTACT DEVELOPER");
        Sleep(1000);
        exit(0);
    }
    while( getline(f, line) )
    {
        if(line.size()==num)
            fp<< line << endl;
    }
    f.close();
    fp.close();
}
//Function to generate random numbers
unsigned long int random()
{
    return rand();
}
//Function to scramble words
void scramble(char s[60])
{
    char t,st[60];
    unsigned long int l,a,b;
    l=strlen(s);
    strcpy(st,s);
    for(int i=0;i<l;i++)// this loop swaps random letters of the word many times so as to form a scrambled word.
    {
        a=random()%l;
        b=random()%l;
        t=s[a];
        s[a]=s[b];
        s[b]=t;
    }
    if(!strcmp(st,s))
        scramble(s);
    strcpy(gl,s);//Copies the scrambled string to the global variable.
}
//Function to check similar strings
//Logic: A similar string is the one which has the same letter as the other one, for ex cat and tac are similar.
bool similar(char s[60], char r[60])
{
    int a,d=0;
    a=strlen(s);
    for(int i=0;i<a;i++)
     for(int j=0;j<a;j++)
       if(s[i]==r[j])
            {   d++;
                r[j]=1;
                break;
            }
    if(d==a)
        return true;
    return false;
}
//Function to unscramble a word: This function will find the possible solutions to a scramble and store it in a file called ANS.txt
//The logic is that it will find all the words similar to the scramble from LEVEL.txt
void unscramble(char s[60])
{
    char r[60];
    int b=strlen(s);
    string line;
    levelfinder(b);
    ifstream f ("LEVEL.txt");
    ofstream fp("ANS.txt");
    if(!fp||!f)
    {
        system("cls");
        gotoXY(20,10);
        perror("SYSTEM ERROR CONTACT DEVELOPER");
        Sleep(1000);
        exit(0);
    }
    while( getline(f, line) )
    {
       int l=line.size();
       for(int i=0;i<l;i++)
         r[i]=line[i];
         r[l]='\0';
         if(similar(s,r))
                 fp<<line<<endl;
    }
    f.close();
    fp.close();
}
//Function to find the number of words in a list
//Logic: This function is necessary to generate a valid random number and hence a valid random word.
unsigned long int number()
{
    int c;
    string line;
    unsigned long int t=0;
    ifstream f("LEVEL2.txt");
    if(!f)
    {
        system("cls");
        gotoXY(20,10);
        perror("SYSTEM ERROR CONTACT DEVELOPER");
        Sleep(1000);
        exit(0);
    }
    while( getline(f, line) )
        t++;
    f.close();
    return t;
}
//Function to select a random word from the list
void select(int l)
{
    ifstream fp("LEVEL2.txt");
    string line;
    if(!fp)
    {
        system("cls");
        gotoXY(20,10);
        perror("SYSTEM ERROR CONTACT DEVELOPER");
        Sleep(1000);
        exit(0);
    }
    unsigned long int c=number();// the number of words in a file.
    unsigned long int a=random()%c;// to create a valid random number. Invalid numbers are those not bound by the limits.
    fp.seekg(a*(l+2));
    getline(fp,line);
    for(int i=0;i<l;i++)
       gl[i]=line[i];// copies it to the global variable.
    gl[l]='\0';
   fp.close();
}
//Function to check whether the user entered answer is correct
//Logic: This function compares the user entered input to those in the FINAL.txt and determines whether the ans is correct or not.
bool check(char s[60])
{
    string line;
    char r[60];
    ifstream fp("ANS.txt");
    if(!fp)
    {
        system("cls");
        gotoXY(20,10);
        perror("SYSTEM ERROR CONTACT DEVELOPER");
        Sleep(1000);
        exit(0);
    }
    int l=strlen(s);
    while(getline(fp,line))
    {
       for(int i=0;i<l;i++)
         r[i]=line[i];
       r[l]='\0';
      if(!strcmpi(s,r))
        {
            fp.close();
            return true;
        }
    }
      fp.close();
      return false;
}
//Function to show correct answers: Reads all the words in the FINAL.txt
void show()
{
    int x=35,y=21;
    ifstream fp("ANS.txt");
    if(!fp)
    {
        system("cls");
        gotoXY(20,10);
        perror("SYSTEM ERROR CONTACT DEVELOPER");
        Sleep(1000);
        exit(0);
    }
    string line;
    while(getline(fp,line))
    {
       gotoXY(x,y);
       cout<<line<<endl;
       y+=2;
    }
    gotoXY(35,y+2);
    cout<<"Press any key to continue";
    getch();
}
//Function to move using arrow keys
int arrowkey(int yi,int yf)
{
    int y=yi,r,ch,x=33,z;
    char ar=175;
    gotoXY(33,yi);
    cout<<ar;
    gotoXY(33,yi);
    z=yi;
    while(1)
    {
    ch=getch();
    if(ch==224)
      {
        ch=getch();
        if(ch==80)//down
           (y==yf)?(y=yi,z=yf):(z=y,y=y+2);
        if(ch==72)//up
           (y==yi)?(y=yf,z=yi):(z=y,y=y-2);
        gotoXY(x,z);
        cout<<" ";
        gotoXY(x,y);
        cout<<ar;
      }
    else if(ch==13)
    {
        r=(y-yi)/2;
        return r;
    }
  }
}
//Function to display strings in slow motion
void slowmotion(string s)
{
    for(int i=0;s[i]!='@';i++)
    {
      (s[i]=='%')?cout<<endl:cout<<s[i];
      Sleep(50);
    }
}
//Function to clear characters stored in the string
void clear(string s)
{
    for(int i=0;s[i]!='\0';i++)
        s[i]=' ';
}
//Function to clear a particular portion of a screen
void clearscreen()
{
    for(int x=0;x<90;x++)
        for(int y=2;y<4;y++)
        {
          gotoXY(x,y);
          cout<<" ";
        }
}
//Function to print and control highscore menu
void highscores()
{
    while(1)
    {
      system("cls");
      int yi=5,yf=9,x=35,y=yi,r,ch;
      system("cls");
      gotoXY(35,0);
      cout<<"Scramble your head";
      gotoXY(x,y);
      cout<<"1.SHOW SCORES";
      gotoXY(x,y+2);
      cout<<"2.CLEAR SCORES";
      gotoXY(x,y+4);
      cout<<"3.BACK";
      gotoXY(35,15);
      cout<<"Please select any of the above";
      gotoXY(x,y);
      r=arrowkey(yi,yf);
      system("cls");
      if(r==0)
      {
         system("cls");
         display_sp();
      }
     if(r==1)
     {
        system("cls");
        gotoXY(35,0);
        cout<<"Scramble your head";
        gotoXY(35,15);
        cout<<"High scores cleared";
        writer();
        Sleep(2000);
     }
      if(r==2)
      {
        system("cls");
        break;
      }
    }
    choice2();
}
//Function that shows the main choice
void choice()
{
    int yi=5,yf=11,x=35,y=yi,r,ch;
    system("cls");
    gotoXY(35,0);
    cout<<"Scramble your head";
    gotoXY(x,y);
    cout<<"1.PLAY";
    gotoXY(x,y+2);
    cout<<"2.HOW TO PLAY?(A short demo..)";
    gotoXY(x,y+4);
    cout<<"3.OTHER INFORMATION";
    gotoXY(x,y+6);
    cout<<"4.EXIT";
    gotoXY(35,15);
    cout<<"Please select any of the above";
    gotoXY(x,y);
    r=arrowkey(yi,yf);
    system("cls");
    if(r==0)
         choice1();
    if(r==1)
    {    system("cls");
         gotoXY(35,0);
         cout<<"Scramble your head";
         gotoXY(0,2);
         string s="The objective of this game is simple, a scrambled word %will be given in a set of small boxes and you have to unscramble it.@";
         slowmotion(s);
         cout<<endl;
         clear(s);
         Sleep(500);
         char sa[]="dcra";
         display(sa,4);
         box(4,0,8);
         gotoXY(0,20);
         Sleep(2000);
         clearscreen();
         gotoXY(35,0);
         cout<<"Scramble your head";
         gotoXY(0,2);
         Sleep(500);
         s="Use the arrow keys to navigate between the boxes.@";
         slowmotion(s);
         Sleep(2000);
         clear(s);
         gotoXY(xstart,ystart);
         Sleep(1000);
         gotoXY(xstart+3,ystart);
         Sleep(2000);
         gotoXY(xstart+6,ystart);
         Sleep(500);
         gotoXY(xstart+6,yend);
         Sleep(250);
         gotoXY(xstart+3,yend);
         Sleep(750);
         gotoXY(xstart,yend);
         Sleep(1000);
         gotoXY(xstart,ystart);
         Sleep(2000);
         clearscreen();
         gotoXY(35,0);
         cout<<"Scramble your head";
         gotoXY(0,2);
         s="Place the cursor above the box and press enter to transfer it to the other set of boxes.@";
         slowmotion(s);
         clear(s);
         gotoXY(xstart,ystart);
         Sleep(1000);
         gotoXY(xstart,ystart);
         cout<<" ";
         gotoXY(xstart,yend);
         cout<<"d";
         gotoXY(xstart,ystart);
         Sleep(2000);
         clearscreen();
         gotoXY(35,0);
         cout<<"Scramble your head";
         gotoXY(0,2);
         s="Proceed like that to complete the answer of the scramble in the lower set of boxes.%Await further instructions... @";
         slowmotion(s);
         clear(s);
         Sleep(1000);
         gotoXY(xstart,ystart);
         cout<<" ";
         gotoXY(xstart,yend);
         cout<<"d";
         gotoXY(xstart,yend);
         Sleep(1500);
         cout<<" ";
         gotoXY(xstart,ystart);
         cout<<"d";
         gotoXY(xstart,ystart);
         Sleep(1700);
         gotoXY(xstart+3,ystart);
         cout<<" ";
         gotoXY(xstart,yend);
         cout<<"c";
         gotoXY(xstart,yend);
         Sleep(1000);
         gotoXY(xend,ystart);
         cout<<" ";
         gotoXY(xstart+3,yend);
         cout<<"a";
         gotoXY(xend,ystart);
         Sleep(500);
         gotoXY(xstart+6,ystart);
         cout<<" ";
         gotoXY(xstart+6,yend);
         cout<<"r";
         gotoXY(xstart+6,ystart);
         Sleep(1000);
         gotoXY(xstart,ystart);
         cout<<" ";
         gotoXY(xend,yend);
         cout<<"d";
         gotoXY(xstart,ystart);
         Sleep(1500);
         system("cls");
         gotoXY(35,0);
         cout<<"Scramble your head";
         gotoXY(25,10);
         s="Thank you for watching and happy learning@";
         slowmotion(s);
         Sleep(2000);
         for(int i=0;i<9;i++)
         {
           gotoXY(65-i,10);
           Sleep(150);
           cout<<' ';
         }
         string s2="gaming...(*_*)@";
         slowmotion(s2);
         Sleep(3000);
         choice();
     }
     if(r==2)
     {
         system("cls");
         gotoXY(35,0);
         cout<<"Scramble your head";
         gotoXY(0,2);
         cout<<"Developed by REX JOMY JOSEPH";
         gotoXY(35,5);
         cout<<"WARNING";
         gotoXY(0,7);
         cout<<"The application is not tested on other machines, so it may behave in ways not intended"<<endl;
         cout<<"by the developer. The damages caused by the program is not beared up on the developer"<<endl;
         cout<<"and should be used under your own risk. If your anti virus program prevents its running"<<endl;
         cout<<"stop the anti virus program. I can assure you that this is not a malicious application."<<endl;
         cout<<"In case of any queries regarding the usage of the software watch the demo or contact"<<endl;
         cout<<"the developer"<<endl;
         gotoXY(35,16);
         cout<<"Copyright (c) 2012 HSSS XII A";
         gotoXY(0,18);
         cout<<"All rights reserved. This software or any portion thereof"<<endl;
         cout<<"may not be reproduced or used in any manner whatsoever"<<endl;
         cout<<"without the express written permission of the developer"<<endl;
         cout<<"except for the use of demonstrating it to others."<<endl;
         getch();
         choice();
     }
     if(r==3)
        exit(0);
}
//Function to show the second choice
void choice1()
{
     int yi=5,yf=11,x=35,y=yi,r,r2,ch;
     system("cls");
     gotoXY(35,0);
     cout<<"Scramble your head";
     gotoXY(x,y);
     cout<<"1.PLANTS";
     gotoXY(x,y+2);
     cout<<"2.ANIMALS";
     gotoXY(x,y+4);
     cout<<"3.OTHERS";
     gotoXY(x,y+6);
     cout<<"BACK to main menu";
     gotoXY(35,15);
     cout<<"Please select a theme";
     gotoXY(x,y);
     gr2=arrowkey(yi,yf);
     if(gr2==3)
         choice();
     status[0]=gr2;
     choice2();
}
//Function to show the third and final choice
void choice2()
{
     int yi=5,yf=15,x=35,y=yi,ch;
     system("cls");
     gotoXY(35,0);
     cout<<"Scramble your head";
     gotoXY(x,y);
     cout<<"1.EASY";
     gotoXY(x,y+2);
     cout<<"2.MEDIUM";
     gotoXY(x,y+4);
     cout<<"3.HARD";
     gotoXY(x,y+6);
     cout<<"4.FIENDISH";
     gotoXY(x,y+8);
     cout<<"BACK";
     gotoXY(x,y+10);
     cout<<"VIEW HIGH SCORES";
     gotoXY(35,19);
     cout<<"Please select any of the above";
     gotoXY(x,y);
     gr=arrowkey(yi,yf);
     if(gr==4)
         choice1();
     if(gr==5)
         highscores();
     if(gr!=5)
         status[1]=gr;
}
//Game function
//This is the function which controls the game
int game(int tot)
{
     int num,i,l,j,ts=0,L;
     int a[4][3]={{3,4,5},{6,7,8},{9,10,11},{12,13,14}};
     unsigned long int no;
     char s[60],x[60],y[60],z[60],tar[60];
     srand(time(NULL));
     gotoXY(35,0);//The end point is 79 and 20
     cout<<"Scramble your head";
     L=status[1];
     int row=L;
     int colum=rand()%3;
     l=a[row][colum];
     system("cls");
     levelfinder2(l);
     select(l);
     for(j=0;j<l;j++)
         z[j]=gl[j];
     z[l]='\0';
     scramble(z);
     disgame(gl,tot);
     unscramble(z);
     gotoXY(35,17);
     (check(san))?(cout<<"You are correct",ts=1):(cout<<"You are wrong",ts=0);
     gotoXY(35,19);
     cout<<"All the possible Solutions for the given scramble:";
     show();
     return ts;
}
//Main Game Function: This is the main function which connects all the functions
void maingame()
{
     int r,stat=0,airam=0;
     string line="duh";
     ifstream f("LICENSE.txt");
     if(f)
     {
        getline(f,line);
        if(line=="ACTIVATED")
           stat=1;
     }
     else
     {
        gotoXY(25,5);
        cout<<"LICENSE FILE MISSING, CANNOT START WITHOUT IT, CONTACT DEVELOPERS";
        gotoXY(35,10);
        cout<<"SHUTTING DOWN THE PROGRAM IN 9 seconds";
        for(int i=8;i>0;i--)
        {
           Sleep(1000);
           gotoXY(64,10);
           cout<<i;
           gotoXY(73,10);
        }
        gotoXY(72,10);
        cout<<" ";
        Sleep(1000);
        f.close();
        exit(0);
     }
    f.close();
    ofstream fp("LICENSE.txt",ios::app);
    while(!stat)
    {
       gotoXY(35,7);
       cout<<"2. EXIT"<<endl;
       gotoXY(35,5);
       cout<<"1. ACTIVATE PRODUCT"<<endl;
       r=arrowkey(5,7);
       if(r)
          exit(0);
       system("cls");
       gotoXY(35,2);
       cout<<"ENTER 4 digit KEY";
       gotoXY(35,5);
       char ter;
       int key=0;
       for(int i=0;i<4;i++)
       {
          ter=getch();
          cout<<"* ";
          key=key+ter-48;
          key=key*10;
       }
       key=key/10;
       if(~key==-1235)
       {
           stat=1;
           fp<<"ACTIVATED";
           gotoXY(25,10);
           cout<<"PRODUCT ACTIVATED, ENJOY FOR THE REST OF YOUR LIFE";
           Sleep(4000);
           fp.close();
       }
       else
       {
           gotoXY(35,10);
           cout<<"WRONG KEY, TRY AGAIN IN 3 seconds";
           for(int i=2;i>0;i--)
           {
             Sleep(1000);
             gotoXY(59,10);
             cout<<i;
             gotoXY(68,10);
           }
           gotoXY(67,10);
           cout<<" ";
           Sleep(1000);
           system("cls");
      }
    }
    int tot=0,ts;
    choice();
    while(1)
    {
      system("cls");
      ts=game(tot);
      if(!ts)
      {
        system("cls");
        gotoXY(35,0);
        cout<<"Scramble your head";
        gotoXY(35,3);
        cout<<"Game Over...";
        gotoXY(35,5);
        cout<<"Your Score: "<<tot;
        gotoXY(35,7);
        cout<<"Press any key...";
        getch();
        update(tot,status[1]);
        newriter(status[1]);
        tot=-1;
        choice2();
      }
      tot++;
    }
}
//**************************************************
//Main function
//**************************************************
int main()
{
    maingame();
    return 0;
}
