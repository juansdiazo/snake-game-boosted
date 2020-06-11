#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller { 
 public: 
  void HandleInput(Snake &snake);
  bool quit{false};

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite);
};

#endif