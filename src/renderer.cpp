#include "renderer.h"
#include <iostream>
#include <string>

// Renderer constructor (3 steps)
Renderer::Renderer(const std::size_t screen_width, const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width), screen_height(screen_height),
      grid_width(grid_width), grid_height(grid_height) {
  // 1. Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) { // possible to initialize with audio or timer
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // 2. Create Window (returns pointer to window)
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // 3. Create renderer object (we call this object to render to created window)
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  // also returns a pointer
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food, Level const level) { // pass snake and food
  SDL_Rect block; // Rectangle block with a width and a height
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;
  SDL_Rect obstacle_scaled;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF); // black (obj,r,g,b,a)
  SDL_RenderClear(sdl_renderer); // set black background on game screen

  // Render obstacle
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF); // blue
  for (SDL_Rect const &obstacle : level.obstacles) { // for each obstacle in level obstacles vector
    obstacle_scaled.x = obstacle.x * block.w;
    obstacle_scaled.y = obstacle.y * block.h;
    obstacle_scaled.w = obstacle.w * block.w;
    obstacle_scaled.h = obstacle.h * block.h;
    SDL_RenderFillRect(sdl_renderer, &obstacle_scaled);
  }

  // Render food                       
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF); // red
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block); // fill block with color and render

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF); // white
  for (SDL_Point const &point : snake.body) { // for each point in snake body vector
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w; // cast to int because
  block.y = static_cast<int>(snake.head_y) * block.h; // head coord. are float
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0x00, 0xFF); // green (alive)
  } else {                               
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF); // yellow (dead)
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int current_level) {
  std::string title{"Your Score: " + std::to_string(score) + "\tLevel: " + std::to_string(current_level)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
