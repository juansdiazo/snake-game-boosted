#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "SDL.h"

class Level {
 public:
  // level constructor
  Level(int grid_width, int grid_height)
    : grid_width(grid_width),
      grid_height(grid_height),
      level_number(1),
      food_count(0) {}

  // public methods of level object
  void UpdateLevel(); 
  void addObstacle(int x_position, int y_position, int width, int height); // position wrt grid
  bool ObstacleCell(int x, int y); 
  
  // public attributes of snake object
  int level_number;
  int food_count;
  std::vector<SDL_Rect> obstacles;
  
 private:

  // private attributes 
  int grid_width;
  int grid_height;
};

#endif
