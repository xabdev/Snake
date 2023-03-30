#pragma once

struct Loc {
  int x;
  int y;
};



struct gameValues {

  int score = 0;
  int hi_score = 0;
  int cycles = 0;
  int parts = 6;

  int speed = 100000;
  int color = 197;
  int mc_color = 70;

  bool menu = true;
  bool play = false;

};

