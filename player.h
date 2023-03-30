#pragma once
#include <ncurses.h>


class player {

    public:
        player();
        ~player();

        void draw_mc_win(WINDOW *win);
        void checkBorder();
        void changeDirection();
        void vJoy();
        void gameOver(WINDOW *win);
        void pauseGame();
        void setDefault();
        void pSnake(WINDOW *win);
        void moveSnake();


};




/*

  if (movement[0]) {mc_loc.y--;}
  if (movement[1]) {mc_loc.x+=2;}
  if (movement[2]) {mc_loc.y++;}
  if (movement[3]) {mc_loc.x-=2;}


*/