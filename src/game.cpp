#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height) // game constructor
    : snake(grid_width, grid_height), // initialize snake
      engine(dev()), // initialize seed
      random_w(0, static_cast<int>(grid_width)), // in grid range 
      random_h(0, static_cast<int>(grid_height)) {
  PlaceFood(); 
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks(); // timestamp of frame start

    // Input, Update, Render - the main game loop (1 frame)
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food);

    frame_end = SDL_GetTicks(); // timestamp of frame end

    frame_count++; // increase counter (keep track of frames every render)
    frame_duration = frame_end - frame_start; // duration of this frame 

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // Time control: If frame_duration is smaller than target, delay 
    // the loop to achieve correct frame rate (nice/smooth gameplay)
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check location is not occupied by snake before placing food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return; // if snake is not alive do something

  snake.Update(); // update snake head and body

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food in this new position
  if (food.x == new_x && food.y == new_y) {// If so do 4 things:
    score++; // 1. increase score
    PlaceFood(); // 2. place new food item in a rnd position
    snake.GrowBody(); // 3. grow snake's body
    snake.speed += 0.02; // 4. increase snake's speed
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }