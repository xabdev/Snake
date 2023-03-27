#include <curses.h>
#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <random>


/* Windows Compile: g++ main.cpp -o Snake -static -lpdcurses */

int score = 0;
int hi_score = 0;
int cycles = 0;
int parts = 5;
int speed = 100000;
int color = 197;
int mc_color = 70;

bool movement[4] = { false, true, false, false };
int direction;

bool menu = true;
bool play = false;

struct Loc {
  int x;
  int y;
};

// Set up initial character position
Loc mc_loc = {0, 0};
Loc food_loc;
Loc prevLoc[200];

std::string mc = "O", mc_shadow = "o";
std::string food = "-";
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

void pauseGame() {
  nodelay(stdscr, false);
  getch();
  nodelay(stdscr, true);
}

int randNum(int end) {  
  std::random_device rd;
  std::mt19937 engine(rd());
  std::uniform_int_distribution<int> dist{1, end};
  int rand = dist(engine);
  return rand; 
}

void checkBorder(Loc& objt) {

  if (objt.x >= 48) { objt.x = 1; }
  else if (objt.x <= 0) { objt.x = 49;}
  if (objt.y > 18) { objt.y = 0; }
  else if (objt.y <= 0) { objt.y = 18;}
}

void changeDirection() {

  for (int i = 0; i < 4; i++) {
  movement[i] = (i == direction); }
}

void vJoy() {

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

void draw_mc_win(WINDOW *win) {

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

void foodPickup() {
  
  for (int i = 0; i < parts; i++){
    if ((prevLoc[i].x == food_loc.x && prevLoc[i].y == food_loc.y) || (prevLoc[i].x == food_loc.x -1 && prevLoc[i].y == food_loc.y)) {
    food_loc.x = randNum(48);
    food_loc.y = randNum(18);
    score++;
    cycles++;
    parts = parts + 3;
    speed = speed - 1000;
    }
  }
}

void foodGraphics() {
    
  if (food == "-") { food = "\\"; }
  else if (food == "\\") { food = "|";}
  else if (food == "|") { food = "/";} 
  else if (food == "/") { food = "-";}
}

void foodMain(WINDOW *win) {

  if (score == 0) { food_loc = {5, 5}; }
  foodPickup();
  foodGraphics();
  wattron(win, COLOR_PAIR(2) | A_BOLD);
  mvwprintw(win, food_loc.y, food_loc.x, "%s", food.c_str());
  wattroff(win, COLOR_PAIR(2) | A_BOLD);
}

void endGame(WINDOW *win) {

  for (int i = parts; i > 0; i--) {
    if (mc_loc.x == prevLoc[i].x && mc_loc.y == prevLoc[i].y) { 
      draw_mc_win(win);
      wattron(win, A_BOLD);
      mvwprintw(win, 9, 15, "G A M E  O V E R !");
      wattroff(win, A_BOLD);
      wrefresh(win);
      pauseGame();
      play = false;
      menu = true;
    }
  }
  
  if ( parts > 190) { play = false; menu = true; }
}

void speedCtrl() {

  usleep(speed);
}

void setDefault() {
  
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
      mvprintw(1, 2, "LENGTH: %d", parts);
      mvprintw(2, 2, "DELAY: %d", speed );
      mvprintw(1, 43, "X POS: %d", mc_loc.x );
      mvprintw(2, 43, "Y POS: %d", mc_loc.y );
      attroff(A_BOLD);
}


int main() {

  // Initialize ncurses screen
  initNc();
  initColor();

  WINDOW * win = newwin(20, 50, 3, 2);
    
  //Menu loop
  while (menu) {

    setDefault();
    wbkgd(win, COLOR_PAIR(3));  
    mMenu(win);
    usleep(50000);
    wrefresh(win);
    werase(win);
  
    // Main game loop
    while (play)  {
            
      vJoy();
      checkBorder(mc_loc);
      draw_mc_win(win);  
      colorTheme(win);
      statScreen();
      foodMain(win);
      box(win, 0, 0);
      wrefresh(win);
      werase(win);
      refresh();
      speedCtrl(); 
      endGame(win);
      }
   }

  endwin();
  return 0;
}
