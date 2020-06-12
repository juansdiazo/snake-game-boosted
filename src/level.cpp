#include <vector>
#include "SDL.h"
#include "level.h"

void Level::UpdateLevel() {
  // Update obstacles depending on the level
  switch (level_number) // origin is the upper left corner (in SDL)
  {
    case 1: {  
      // 1 obstacle (x, y, w, h)
      obstacles.clear();
      addObstacle(grid_width/4, grid_height/4, grid_width/2, grid_height/2);
      food_count = 0;
      break;
    }
    case 2: {    
      // 2 obstacles
      obstacles.clear();
      addObstacle(grid_width/8, grid_height/8, grid_width*3/8, grid_height*3/8);
      addObstacle(grid_width/2, grid_height/2, grid_width*3/8, grid_height*3/8);
      food_count = 0;
      break;   
    } 
    case 3: {
      // 3 obstacles
      obstacles.clear();
      addObstacle(grid_width/8, grid_height/8, grid_width/8, grid_height*3/4);
      addObstacle(grid_width*7/16, grid_height/8, grid_width/8, grid_height*3/4);
      addObstacle(grid_width*6/8, grid_height/8, grid_width/8, grid_height*3/4);
      food_count = 0;
      break;    
    }
    case 4: {
      // 4 obstacles
      obstacles.clear();
      addObstacle(grid_width/8, grid_height/4, grid_width/8, grid_height/2);
      addObstacle(grid_width*3/8, grid_height/8, grid_width/4, grid_height/8);
      addObstacle(grid_width*3/4, grid_height/4, grid_width/8, grid_height/2);
      addObstacle(grid_width*3/8, grid_height*3/4, grid_width/4, grid_height/8);
      food_count = 0;
      break;    
    }
    case 5: {
      // 9 obstacles
      obstacles.clear();
      addObstacle(grid_width/8, grid_height/8, grid_width/8, grid_height/8);
      addObstacle(grid_width*3/8, grid_height/8, grid_width/8, grid_height/8);
      addObstacle(grid_width*5/8, grid_height/8, grid_width/8, grid_height/8);
      addObstacle(0, grid_height*3/8, grid_width/4, grid_height/4);
      addObstacle(grid_width*3/8, grid_height*3/8, grid_width/4, grid_height/4);
      addObstacle(grid_width*3/4, grid_height*3/8, grid_width/4, grid_height/4);
      addObstacle(grid_width/4, grid_height*3/4, grid_width/8, grid_height/8);
      addObstacle(grid_width/2, grid_height*3/4, grid_width/8, grid_height/8);
      addObstacle(grid_width*3/4, grid_height*3/4, grid_width/8, grid_height/8);
      food_count = 0;
      break;
    }
  }
}

void Level::addObstacle(int x_position, int y_position, int width, int height){ // position wrt grid
  SDL_Rect obstacle{x_position, y_position, width, height}; 
  obstacles.push_back(obstacle);
}

//check if cell is occupied by obstacle
bool Level::ObstacleCell(int x, int y) {
  bool cell_in_obstacle = false;
  int left, right, top, bottom;
  for (auto &obstacle : obstacles){
    left = obstacle.x;
    right = obstacle.x + obstacle.w;
    top = obstacle.y;
    bottom = obstacle.y + obstacle.h;
    // true if cell is within the rectangle boundaries
    if ((x >= left && x < right) && (y >= top && y < bottom)){
        return cell_in_obstacle = true;
    }
  }
  return cell_in_obstacle;  
}
