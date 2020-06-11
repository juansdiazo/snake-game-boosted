#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::HandleInput(Snake &snake){
  SDL_Event e; // A union that contains structures for event types
  // poll for currently pending events
  while (SDL_PollEvent(&e)) { // event passed as reference
    if (e.type == SDL_QUIT) {
      quit = true;
      return;
    } else if (e.type == SDL_KEYDOWN) { // check if event is a key press
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp, // input dir.
                          Snake::Direction::kDown); // opposite dir.
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
      }
    }
  }
  const Uint8* keystates = SDL_GetKeyboardState(NULL);
  if (keystates[SDL_SCANCODE_ESCAPE] != 0u) {
    quit = true;
    return;
  }
}