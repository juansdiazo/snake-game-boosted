#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
  // We first capture the head's cell before updating.
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  

  UpdateHead();
  
  // Capture the head's cell after updating.
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  

  // Update snake body if the head has moved to a new cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  // Update head coordinates according to keyboard input
  switch (direction) // origin is the upper left corner (in SDL)
  {
    case Direction::kUp:
      head_y -= speed; 
      break;
    case Direction::kDown:
      head_y += speed;
      break;
    case Direction::kLeft:
      head_x -= speed;
      break;
    case Direction::kRight:
      head_x += speed;
      break;
  }
  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width); // modulo by grid width
  head_y = fmod(head_y + grid_height, grid_height); // modulo by grid height
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else { // when snake eats food the body size grows
    growing = false;
    size++; 
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false; // happens when head is equal to body's coordinates
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake (used when placing food)
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true; // cell occupied by head
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true; // cell occupied by body
    }
  }
  return false;
}

void Snake::ResetSnake() {
  head_x = 0;
  head_y = grid_height;
  body.clear();
}