#include "level.h"

#include <vector>
#include "SDL.h"

void Level::UpdateLevel() {
  // Update obstacles depending on the level
  switch (level_number) // origin is the upper left corner (in SDL)
  {
    case 1:
    {
      obstacles.clear();
      food_count = 0; 
      break;
    }
    case 2:
    {  
      // 1 obstacle (x, y, w, h)
      obstacles.clear();
      SDL_Rect obstacle2{grid_width/4, grid_height/4, grid_width/2, grid_height/2}; 
      obstacles.push_back(obstacle2);
      food_count = 0;
      break;
    }
    case 3:
    {    
      // 2 obstacles
      obstacles.clear();
      SDL_Rect obstacle31{grid_width/8, grid_height/8, grid_width*3/8, grid_height*3/8};
      obstacles.push_back(obstacle31); 
      SDL_Rect obstacle32{grid_width/2, grid_height/2, grid_width*3/8, grid_height*3/8}; 
      obstacles.push_back(obstacle32);
      food_count = 0;
      break;
      
    }
    
    case 4:
    {
      // 4 obstacles
      obstacles.clear();
      SDL_Rect obstacle31{grid_width/8, grid_height/8, grid_width/8, grid_height*3/4};
      obstacles.push_back(obstacle31); 
      SDL_Rect obstacle32{grid_width*3/8, grid_height/8, grid_width/4, grid_height/8}; 
      obstacles.push_back(obstacle32);
      SDL_Rect obstacle33{grid_width*6/8, grid_height/8, grid_width/8, grid_height*3/4}; 
      obstacles.push_back(obstacle33);
      SDL_Rect obstacle34{grid_width*3/8, grid_height*6/8, grid_width/4, grid_height/8}; 
      obstacles.push_back(obstacle34);
      food_count = 0;
      break;  
      
    }

    case 5:
    {
      // 9 obstacles
      obstacles.clear();
      SDL_Rect obstacle31{grid_width/8, grid_height/8, grid_width/8, grid_height/8};
      obstacles.push_back(obstacle31); 
      SDL_Rect obstacle32{grid_width*3/8, grid_height/8, grid_width/8, grid_height/8}; 
      obstacles.push_back(obstacle32);
      SDL_Rect obstacle33{grid_width*5/8, grid_height/8, grid_width/8, grid_height/8}; 
      obstacles.push_back(obstacle33);

      SDL_Rect obstacle34{0, grid_height*3/8, grid_width/4, grid_height/4};
      obstacles.push_back(obstacle34); 
      SDL_Rect obstacle35{grid_width*3/8, grid_height*3/8, grid_width/4, grid_height/4}; 
      obstacles.push_back(obstacle35);
      SDL_Rect obstacle36{grid_width*3/4, grid_height*3/8, grid_width/4, grid_height/4}; 
      obstacles.push_back(obstacle36);

      SDL_Rect obstacle37{grid_width/4, grid_height*3/4, grid_width/8, grid_height/8};
      obstacles.push_back(obstacle37); 
      SDL_Rect obstacle38{grid_width/2, grid_height*3/4, grid_width/8, grid_height/8}; 
      obstacles.push_back(obstacle38);
      SDL_Rect obstacle39{grid_width*3/4, grid_height*3/4, grid_width/8, grid_height/8}; 
      obstacles.push_back(obstacle39);



      food_count = 0;
      break;
    }
  }
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
