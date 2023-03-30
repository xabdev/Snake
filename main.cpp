#include <curses.h>
#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include "player.h"
#include "items.h"


/* Windows Compile: g++ main.cpp -o Snake -static -lpdcurses */

int score = 0;
int hi_score = 0;
int cycles = 0;

int speed = 100000;
int color = 197;
int mc_color = 70;



bool menu = true;
bool play = false;



// Set up initial character position


std::string title = "SNAAAAAAAKE!?";


void initNc() {
  initscr();
  start_color();

  // Define the color pairs for the extended 256 colors
  //for (int i = 0; i < 247; i++) {init_pair(i, i, COLOR_BLACK);}

  noecho();
  cbreak();
  keypad(stdscr, true);
  curs_set(0);
  nodelay(stdscr, TRUE);
}

void initColor() {

  init_pair(1, 82, COLOR_BLACK);
  init_pair(2, 214, COLOR_BLACK);
  init_pair(3, 205, 233);
  
  for (int i = 129; i < 247; i++) {init_pair(i, i, 233);}

}

void colorTheme(WINDOW *win) {  
  wbkgd(win, COLOR_PAIR(129 + cycles));
}





void speedCtrl() {

  usleep(speed);
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
    werase(win);
    int mmenu = getch();
  
    switch (mmenu) {
      case 49:
        werase(win);
        menu = false;
        play = true;
        clear();
        werase(win);
        break;

      case 50:
        menu = false;
        play = false;
        werase(win);
        break;
    }
}


void statScreen() {

      attron(A_BOLD);
      mvprintw(1, 24, "SCORE: %d", score);
      mvprintw(2, 22, "HI-SCORE: %d", hi_score);
      //mvprintw(1, 2, "LENGTH: %d", parts);
      mvprintw(2, 2, "DELAY: %d", speed );
      //mvprintw(1, 43, "X POS: %d", mc_loc.x );
      //mvprintw(2, 43, "Y POS: %d", mc_loc.y );
      attroff(A_BOLD);
}


int main() {

  player Player1;
  items Items;

  // Initialize ncurses screen
  initNc();
  initColor();

  WINDOW * win = newwin(20, 50, 3, 2);
    
  //Menu loop
  while (menu) {

    //setDefault();
    wbkgd(win, COLOR_PAIR(3));  
    mMenu(win);
    usleep(50000);
    wrefresh(win);
    werase(win);
  
    // Main game loop
    while (play)  {

      speedCtrl(); 

      Player1.pSnake(win);
    
      Items.foodMain(win);
      box(win, 0, 0);
      wrefresh(win);
      refresh();
      werase(win);

      colorTheme(win);
      statScreen();
      
            
      }
   }

  endwin();
  return 0;
}
