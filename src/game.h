#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "snake.h"
#include "level.h"
#include "controller.h"
#include "renderer.h"

class Game {
 public:
  // game constructor
  Game(std::size_t grid_width, std::size_t grid_height, 
       std::size_t screen_width, std::size_t screen_height);
  
  // public methods of game object
  void Run(std::size_t target_frame_duration);
  void RunLevel(std::size_t target_frame_duration);

  //public attributes of game object;
  int score = 0;
  int current_level = 1;
  int GetSize() const;
  void HighScore();
  //SDL_Rect obstacle;
  
 private:
 // private attributes of game object
  Level level;

  Snake snake;
  SDL_Point food;

  Renderer renderer;
  Controller controller;

  std::random_device dev; // used as seed for random device
  std::mt19937 engine; // pseudo-rnd-num-gen uses mersenne_twister alg.
  std::uniform_int_distribution<int> random_w; // used to place food
  std::uniform_int_distribution<int> random_h; // x-y coordinates

  // private methods of game object
  void PlaceFood();
  void Update();
};

#endif