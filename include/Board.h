//
// Created by Куимов Михаил on 20.06.2025.
//

#ifndef BOARD_H
#define BOARD_H
#include "Tile.h"

enum class Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

class Board final{
  Tiles tiles_;
  void resetMergedFlags();
public:
  Board();
  ~Board();

  bool move(Direction direction);

  void spawnTile();

  [[nodiscard]] bool hasMoves() const;

  [[nodiscard]] const Tiles& getTiles() const;
};



#endif //BOARD_H
