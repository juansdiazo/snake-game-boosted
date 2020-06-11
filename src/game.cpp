#include "game.h"
#include <iostream>
#include "SDL.h"
#include <fstream>

#include <sstream>
#include <string>
#include <map>

Game::Game(std::size_t grid_width, std::size_t grid_height,
           std::size_t screen_width, std::size_t screen_height) // game constructor
    : snake(grid_width, grid_height), // initialize snake
      level(grid_width, grid_height), // initialize snake
      renderer(screen_width, screen_height, grid_width, grid_height),
      engine(dev()), // initialize seed
      random_w(0, static_cast<int>(grid_width-1)), // in grid range 
      random_h(0, static_cast<int>(grid_height-1)) {
  //PlaceObstacle(grid_width/4, grid_height/4, grid_width/2, grid_height/2);
  PlaceFood(); 
}

void Game::Run(std::size_t target_frame_duration) {
  while (true) {
    RunLevel(target_frame_duration); 
    if (controller.quit) {
      return;
    }  
    else {
      level.level_number++;
      if (level.level_number >= 6){ // levels declared + 1
        level.level_number = 1;
      }
    }
    
    level.UpdateLevel();
    PlaceFood();
    snake.ResetSnake();
  }
}

void Game::RunLevel(std::size_t target_frame_duration) {
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    
    while (true) {
      frame_start = SDL_GetTicks(); // timestamp of frame start

      // Input, Update, Render - the main game loop (1 frame)
      renderer.Render(snake, food, level);

      controller.HandleInput(snake);

      if (controller.quit) {
        return;
      }

      if (level.food_count >= 1) {
        break;    
      }

      
      Update();

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

void Game::Update() {
  if (!snake.alive) return; // if snake is not alive do something

  snake.Update(); // update snake head and body

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  if (level.ObstacleCell(new_x,new_y)) {
    snake.alive = false; // happens when head touches obstacle
  }

  // Check if there's food in this new position
  if (food.x == new_x && food.y == new_y) {// If so do 4 things:
    score++; // 1. increase score
    level.food_count++;
    PlaceFood(); // 2. place new food item in a rnd position
    snake.GrowBody(); // 3. grow snake's body
    snake.speed += 0.02; // 4. increase snake's speed
  }
}

// int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check location is not occupied by snake before placing food.
    if (!snake.SnakeCell(x, y) && !level.ObstacleCell(x,y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

/*
void Game::PlaceObstacle(int x, int y, int w, int h) {
  obstacle.x = x;
  obstacle.y = y;
  obstacle.w = w;
  obstacle.h = h;
}

//check if cell is occupied by obstacle
bool Game::ObstacleCell(int x, int y) {
  int left, right, top, bottom;
  
  left = obstacle.x;
  right = obstacle.x + obstacle.w;
  top = obstacle.y;
  bottom = obstacle.y + obstacle.h;

  // true if cell is within the rectangle boundaries
  return ((x >= left && x < right) && (y >= top && y < bottom));  
}
*/

void Game::HighScore(){
    std::string line, name, str_score;
    // multimap as it allows keys with same value and sort in ascending order
    std::multimap<int, std::string, std::greater<int>> top_five; 

    std::ifstream input_file;
    input_file.open("../highscores.txt");
    
    // Read highscores file and store in multimap
    if(input_file){ 
        while (getline(input_file,line)){ 
            std::istringstream line_stream(line);
            while (line_stream >> str_score >> name){
                int score_int = std::stoi(str_score);
                top_five.insert({score_int, name});   
            }
        } 
    }
    else
    {
        std::cout << "Problem creating file stream! \n"; 
    }
    input_file.close();
    //int new_score = Game::GetScore();
    std::string new_name;
    
    // create iterator to position of <key,value> pair in position 5 
    std::multimap<int, std::string, std::greater<int>>::iterator pos_five_ite = top_five.end();
    std::advance(pos_five_ite, -1); 
    int pos_five_score = top_five.rbegin()->first; // score in position 5 (rbegin pointer one before end)

    if (score >= pos_five_score) // update if score in top 5
    {
        top_five.erase(pos_five_ite); // erase position 5 entry 
        std::cout << "Enter your name: ";
        std::cin >> new_name;
        top_five.insert({score,new_name}); // new entry
    }

    std::ofstream output_file; 
    output_file.open("../highscores.txt");
   
    std::cout << "\nTOP 5 HIGHSCORES \n";
    std::cout << "\nSCORE \t NAME\n";

    for (auto itr = top_five.begin(); itr != top_five.end(); ++itr) {  
        std::cout << itr->first << '\t' << itr->second << '\n'; // printed to screen
        output_file << itr->first << " " << itr->second << '\n';  // saved in file (in ascending order)
    }
    output_file.close(); 
}