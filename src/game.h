#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  // game constructor
  Game(std::size_t grid_width, std::size_t grid_height);
  
  // public methods of game object
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

  SDL_Rect obstacle;
  
 private:
 // private attributes of game object
  Snake snake;
  SDL_Point food;
  int score{0};

  std::random_device dev; // used as seed for random device
  std::mt19937 engine; // pseudo-rnd-num-gen uses mersenne_twister alg.
  std::uniform_int_distribution<int> random_w; // used to place food
  std::uniform_int_distribution<int> random_h; // x-y coordinates

  // private methods of game object
  void PlaceFood();
  void Update();

  void PlaceObstacle(int x, int y, int w, int h);
  bool ObstacleCell(int x, int y); 
};

#endif