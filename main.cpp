#include <curses.h>
#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include "player.h"
#include "items.h"
#include "maingame.h"
#include "location.h"


/* Windows Compile: g++ main.cpp -o Snake -static -lpdcurses */



std::string title = "SNAAAAAAAKE!?";

gameValues settings;



void colorTheme(WINDOW *win) {  
  wbkgd(win, COLOR_PAIR(129 + settings.cycles));
}

void mMenu(WINDOW *win) {

    wattron(win, A_BOLD);
    mvwprintw(win, 9, 21, "1> PLAY");
    mvwprintw(win, 10, 21, "2> EXIT");
    mvwprintw(win, 7, 19, "%s", title.c_str());
    wattroff(win, A_BOLD);
    mvwprintw(win, 18, 2, "Created by Jav");
    mvwprintw(win, 18, 23, "https://github.com/xabdev");
    box(win, 0, 0);
    wrefresh(win);

    int mmenu = getch();
  
    switch (mmenu) {
      case 49:

        settings.menu = false;
        settings.play = true;
        clear();

        break;

      case 50:
        settings.menu = false;
        settings.play = false;

        break;
    }
            werase(win);
}


void statScreen() {

      attron(A_BOLD);
      mvprintw(1, 24, "SCORE: %d", settings.score);
      mvprintw(2, 22, "HI-SCORE: %d", settings.hi_score);
      //mvprintw(1, 2, "LENGTH: %d", parts);
      mvprintw(2, 2, "DELAY: %d", settings.speed );
      //mvprintw(1, 43, "X POS: %d", mc_loc.x );
      //mvprintw(2, 43, "Y POS: %d", mc_loc.y );
      attroff(A_BOLD);
}


int main() {

  player Player1;
  items Items;
  maingame mainGame;

  // Initialize ncurses screen
  mainGame.initNcurses();

  WINDOW * win = newwin(20, 50, 3, 2);
    
  //Menu loop
  while (settings.menu) {

    //setDefault();
    wbkgd(win, COLOR_PAIR(3));  
    mMenu(win);
    usleep(50000);
    wrefresh(win);
    werase(win);
  
    // Main game loop
    while (settings.play)  {

      usleep(settings.speed);
      
      
      Player1.pSnake(win);
    
      Items.foodMain(win);
      
      box(win, 0, 0);
      
      wrefresh(win);
      werase(win);
      refresh();
      

      colorTheme(win);
      statScreen();
      
            
      }
   }

  endwin();
  return 0;
}