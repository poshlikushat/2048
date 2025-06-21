//
// Created by Куимов Михаил on 20.06.2025.
//

#ifndef TILE_H
#define TILE_H

struct Tile final {
  int x;
  int y;
  int value;
  int color;
  bool merged;

  explicit Tile(int x_ = 0, int y_ = 0, int value_ = 0, int color_ = 0);
};

#endif //TILE_H
