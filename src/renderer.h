#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include "level.h"

class Renderer {
 public:
  // renderer constructor and destructor
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  // public methods of renderer object
  void Render(Snake const snake, SDL_Point const &food, Level const level); // render snake, food and level to screen
  void UpdateWindowTitle(int score, int current_level); // update bar at top of window

 private:
  // private attributes
  SDL_Window *sdl_window; // pointer to an sdl window object
  SDL_Renderer *sdl_renderer;
  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif