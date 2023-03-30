#include "items.h"
#include "location.h"


Loc food_loc;
std::string food = "-";
extern Loc prevLoc[200];
extern int parts;
extern int score;
extern int speed;
extern int cycles;


int items::randNum(int end) {
  std::random_device rd;
  std::mt19937 engine(rd());
  std::uniform_int_distribution<int> dist{1, end};
  int rand = dist(engine);
  return rand;
}


void items::foodGraphics() {
  if (food == "-") { food = "\\"; }
  else if (food == "\\") { food = "|";}
  else if (food == "|") { food = "/";} 
  else if (food == "/") { food = "-";}
}


void items::foodPickup() {
    (score == 0) ? food_loc = {5, 5} : Loc{};
    for (int i = 0; i < parts; i++){
    if ((prevLoc[i].x == food_loc.x && prevLoc[i].y == food_loc.y) || (prevLoc[i].x == food_loc.x -1 && prevLoc[i].y == food_loc.y)) {
    food_loc.x = randNum(48);
    food_loc.y = randNum(18);
    score++;
    parts = parts + 3;
    speed = speed - 1000;
    cycles++;
    }
  }
}


void items::foodMain(WINDOW *win) {
  
  wattron(win, COLOR_PAIR(2) | A_BOLD);
  mvwprintw(win, food_loc.y, food_loc.x, "%s", food.c_str());
  wattroff(win, COLOR_PAIR(2) | A_BOLD);
  
  foodPickup();
  foodGraphics();

}