#include "maingame.h"
#include <ncurses.h>







void maingame::initColor() {

  init_pair(1, 82, COLOR_BLACK);
  init_pair(2, 214, COLOR_BLACK);
  init_pair(3, 205, 233);
  
  for (int i = 129; i < 247; i++) {init_pair(i, i, 233);}

}


void maingame::initNcurses() {

  initscr();
  start_color();
  noecho();
  cbreak();
  keypad(stdscr, true);
  curs_set(0);
  nodelay(stdscr, TRUE);
  initColor();
  

}






