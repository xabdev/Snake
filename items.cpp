#include "items.h"
#include "location.h"


Loc food_loc;
std::string food = "-";
extern Loc prevLoc[200];
extern gameValues settings;



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
    (settings.score == 0) ? food_loc = {5, 5} : Loc{};
    for (int i = 0; i < settings.parts; i++){
    if ((prevLoc[i].x == food_loc.x && prevLoc[i].y == food_loc.y) || (prevLoc[i].x == food_loc.x -1 && prevLoc[i].y == food_loc.y)) {
    food_loc.x = randNum(48);
    food_loc.y = randNum(18);
    settings.score++;
    settings.parts +=5;
    settings.speed = settings.speed - 1000;
    settings.cycles++;
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