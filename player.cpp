#include "player.h"
#include <string>
#include "location.h"


player::player() {}
player::~player(){}




std::string mc = "O", mc_shadow = "o";
int parts = 5;

bool movement[4] = { false, true, false, false };
int direction;


Loc mc_loc = {0, 0};
Loc prevLoc[200];

extern bool play;
extern bool menu;
extern int score;
extern int speed;
extern int hi_score;


void player::pauseGame() {

  nodelay(stdscr, false);
  getch();
  nodelay(stdscr, true);

}


void player::draw_mc_win(WINDOW *win) {

  for (int i = parts; i > 0; i--) {
  prevLoc[i] = prevLoc[i-1]; 
  }
  wattron(win, COLOR_PAIR(1));
  wattron(win, A_BOLD);
  mvwprintw(win, mc_loc.y, mc_loc.x, "%s", mc.c_str());
  wattroff(win, A_BOLD);
  
  prevLoc[0] = mc_loc; 

  for (int i = parts; i > 0; i--) {
    mvwprintw(win, prevLoc[i].y, prevLoc[i].x, "%s", mc_shadow.c_str());
  }
  
  wattroff(win, COLOR_PAIR(1));
}

void player::checkBorder() {

  if (mc_loc.x >= 48) { mc_loc.x = 1; }
  else if (mc_loc.x <= 0) { mc_loc.x = 49;}
  if (mc_loc.y > 18) { mc_loc.y = 0; }
  else if (mc_loc.y <= 0) { mc_loc.y = 18;}

}



void player::changeDirection() {

    for (int i = 0; i < 4; i++) {
    movement[i] = (i == direction); }


}

void player::vJoy() {


  int mc_move = getch();
  
  switch (mc_move) {

    case KEY_UP:
      if (movement[2]) { break; }
      direction = 0;
      changeDirection();
      break;

    case KEY_DOWN:
      if (movement[0]) { break; }
      direction = 2;
      changeDirection();
      break;

    case KEY_RIGHT:
      if (movement[3]) { break; }
      direction = 1;
      changeDirection();
      break;

    case KEY_LEFT:
      if (movement[1]) { break; }
      direction = 3;
      changeDirection();
      break;
  }

  if (movement[0]) {mc_loc.y--;}
  if (movement[1]) {mc_loc.x+=2;}
  if (movement[2]) {mc_loc.y++;}
  if (movement[3]) {mc_loc.x-=2;}

}

void player::setDefault() {

  if (score > hi_score) { hi_score = score;}
  score = 0;
  parts = 5;
  speed = 80000;
  mc_loc.x = 1;
  mc_loc.y = 1;
  for (int i = 0; i != 98; i++) {
    prevLoc[i].x = 0 , prevLoc[i].y = 0;
  }

}



void player::gameOver(WINDOW *win ) {

  for (int i = parts; i > 0; i--) {
    if (mc_loc.x == prevLoc[i].x && mc_loc.y == prevLoc[i].y) { 
      draw_mc_win(win);
      wattron(win, A_BOLD);
      mvwprintw(win, 9, 15, "G A M E  O V E R !");
      wattroff(win, A_BOLD);
      wrefresh(win);
      play = false;
      menu = true;
      setDefault();
      pauseGame();
      
    }
  }
}

void player::pSnake(WINDOW *win) {

  vJoy();
  draw_mc_win(win);
  checkBorder();
  gameOver(win);




}




