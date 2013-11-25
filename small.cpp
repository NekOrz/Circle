#include<iostream>
#include<ctime>
#include<cstdlib>
#include<curses.h>
#include<algorithm>
#define mid 200
#define DEBUG

using namespace std;
int maxX,maxY;
char circle[16];
void init()
{
    //noecho();
    initscr();
    srand(time(NULL));
    curs_set(0);
    nodelay(stdscr,TRUE);
    getmaxyx(stdscr,maxY,maxX);
}
void printcir()
{
    mvaddch(1,2,circle[0]);
    mvaddch(1,4,circle[1]);
    mvaddch(1,6,circle[2]);
    mvaddch(1,8,circle[3]);
    mvaddch(2,1,circle[15]);
    mvaddch(2,9,circle[4]);
    mvaddch(3,0,circle[14]);
    mvaddch(3,10,circle[5]);
    mvaddch(4,0,circle[13]);
    mvaddch(4,10,circle[6]);
    mvaddch(5,1,circle[12]);
    mvaddch(5,9,circle[7]);
    mvaddch(6,8,circle[8]);
    mvaddch(6,6,circle[9]);
    mvaddch(6,4,circle[10]);
    mvaddch(6,2,circle[11]);
}
int main()
{
    init();
    time_t timenow=clock();
    int cpos=0,dotpos=1,combo=0,maxcombo=0,money=0,mult=1;
    int m_money=50,p_money=200;
    float prot=0.0;
    bool upgrade[20];
    char c;
    for(int i=0;i<16;i++)
        circle[i]='*';
    while(1)
    {
        printcir();
        if(((clock()-timenow)/mid)>0)
        {
            timenow=clock();
            circle[dotpos]='*';
            circle[cpos]='*';
            while(dotpos==cpos)
                cpos=rand()%16;
            dotpos=(dotpos+1)%16;
            if(dotpos==cpos)
                circle[cpos]='#';
            else
            {
                circle[cpos]='O';
                circle[dotpos]='.';
            }
        }
        refresh();
        noecho();
        if((c=getch())!=ERR)
        {
            switch(c)
            {
            case ' ':
                if (cpos == dotpos)
                {
                    echo();
                    mvprintw(4,15,"                            ");
                    mvprintw(4,15,"+%d",combo*mult);
                    money+=(combo++)*mult;
                    maxcombo=max(maxcombo,combo);

                }
                else
                {
                    combo=(int)(combo*prot);
                    mvprintw(4,15,"                            ");
                }
                break;
            case 'm':
                if(money > m_money)
                {
                    money-=m_money;
                    m_money+=10;
                    mult++;
                }
                break;
            case 'p':
                if(money>p_money)
                {
                    money-=p_money;
                    p_money+=50;
                    prot+=(1.0-prot)*0.05;
                }
                break;
            #ifdef DEBUG
            case 'j':
                money+=5000;
                combo+=500;

            #endif // DEBUG
            }
        }
        echo();
        mvprintw(2,15,"%d combos!",combo);
        mvprintw(2,30,"%d maxcombos!",maxcombo);
        mvprintw(5,15,"%d dollars",money);
        mvprintw(8,2,"money (m)ultiplyer ($%d) : %d",m_money,mult);
        mvprintw(10,2,"combo (p)rotecter ($%d) : %.2f%%",p_money,prot*100);
        //mvprintw()
        refresh();
    }
/*
  ####
 #    #
#      #
#      #
 #    #
  ####
*/
}
