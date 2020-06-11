#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "SDL.h"

class Level {
 public:
  // level constructor
  Level(std::size_t grid_width, std::size_t grid_height)
    : grid_width(grid_width),
      grid_height(grid_height),
      level_number(1),
      food_count(0) {}

  // public methods of level object
  //void SnakeReset();
  void UpdateLevel(); 
  //void PlaceObstacles();
  //void PlaceObstacle(int x, int y, int w, int h);
  bool ObstacleCell(int x, int y); 
  
  // public attributes of snake object
  int level_number;
  int food_count;
  std::vector<SDL_Rect> obstacles;
  //SDL_Rect obstacle;
  
 private:
  // private methods 

  // private attributes 
  int grid_width;
  int grid_height;
};

#endif
