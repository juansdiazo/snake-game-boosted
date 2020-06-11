#include <iostream>
#include "game.h"

int main() {
  // Constant expressions that define misc. game settings:
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  // Game object is created:
  Game game(kGridWidth, kGridHeight, kScreenWidth,kScreenHeight);

  // Game loop is started
  game.Run(kMsPerFrame);

  // Printout at the end of the game
  std::cout << "Game has terminated successfully!\n";
  //std::cout << "Score: " << game.GetScore() << "\n";
  game.HighScore();
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}