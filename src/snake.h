#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  // snake constructor
  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(0), // starts in left-upper corner
        head_y(grid_height) {}

  // public methods of snake object
  void Update(); // every loop
  void GrowBody(); // once it eats food
  bool SnakeCell(int x, int y); // is the coordinate part of the snake?
  void ResetSnake();

  // public attributes of snake object
  float speed{0.1f};
  float head_x;
  float head_y;
  int size{1};
  bool alive{true};
  std::vector<SDL_Point> body;
  Direction direction = Direction::kUp;

 private:
  // private methods (called with update)
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  // private attributes
  bool growing{false}; // set to true when snake eats food 
  int grid_width;
  int grid_height;
};

#endif