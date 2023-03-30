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


};

