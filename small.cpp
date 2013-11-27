#include<iostream>
#include<ctime>
#include<cstdlib>
#include<curses.h>
#include<algorithm>
#define mid 75
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
    start_color();
    init_pair(1,COLOR_RED,COLOR_BLACK);
}
void printcir()
{
    mvaddch(1,2+20,circle[0]);
    mvaddch(1,4+20,circle[1]);
    mvaddch(1,6+20,circle[2]);
    mvaddch(1,8+20,circle[3]);
    mvaddch(2,1+20,circle[15]);
    mvaddch(2,9+20,circle[4]);
    mvaddch(3,0+20,circle[14]);
    mvaddch(3,10+20,circle[5]);
    mvaddch(4,0+20,circle[13]);
    mvaddch(4,10+20,circle[6]);
    mvaddch(5,1+20,circle[12]);
    mvaddch(5,9+20,circle[7]);
    mvaddch(6,8+20,circle[8]);
    mvaddch(6,6+20,circle[9]);
    mvaddch(6,4+20,circle[10]);
    mvaddch(6,2+20,circle[11]);
}
int main()
{
    init();
    time_t timenow=clock();
    int cpos=0,dotpos=1,combo=0,maxcombo=0,money=0,mult=1,combo_m=1;
    int m_money=50,p_money=200,cm_money=100;
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
                    money+=(combo+=combo_m)*mult;
                    mvprintw(4,2,"              ");
                    mvprintw(4,2,"+%d",combo*mult);
                    maxcombo=max(maxcombo,combo);

                }
                else
                {
                    combo=(int)(combo*prot);
                    mvprintw(4,2,"           ");
                }
                break;
            case 'm':
                if(money >= m_money)
                {
                    money-=m_money;
                    m_money+=10;
                    mult++;
                }
                break;
            case 'p':
                if(money>=p_money)
                {
                    money-=p_money;
                    p_money+=50;
                    prot+=(1.0-prot)*0.05;
                }
                break;
            case 'c':
                if(money>=cm_money)
                {
                    money-=cm_money;
                    cm_money+=50;
                    combo_m++;
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
        mvprintw(2,2,"%d combos!",combo);
        mvprintw(2,40,"%d maxcombos!",maxcombo);
        mvprintw(5,2,"%d dollars",money);
        mvprintw(8,2,"money (m)ultiplyer ($%d) : %d",m_money,mult);
        mvprintw(10,2,"combo (p)rotecter ($%d) : %.2f%%",p_money,prot*100);
        mvprintw(12,2,"(c)ombo multiplyer ($%d) : %d",cm_money,combo_m);
        mvprintw(4,40,"press space when . and O meet!");
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
