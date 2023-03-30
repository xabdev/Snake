#pragma once
#include <random>
#include "location.h"
#include <ncurses.h>


class items {

    public:
        int randNum(int end);
        void foodGraphics();
        void foodMain(WINDOW *win);
        void foodPickup();
};
