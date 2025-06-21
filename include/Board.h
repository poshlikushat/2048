//
// Created by Куимов Михаил on 20.06.2025.
//

#ifndef BOARD_H
#define BOARD_H
#include "Tile.h"
#include <vector>
#include <random>

enum class Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

class Board final{
  std::vector<Tile> tiles_;
  std::mt19937 rng_;

  void resetMergedFlags();
  Tile* findTile(int x, int y);
public:
  Board();
  ~Board() = default;

  void reset();
  bool move(Direction direction);

  void spawnTile();

  [[nodiscard]] bool hasMoves() const;

  [[nodiscard]] const std::vector<Tile>& getTiles() const;
};



#endif //BOARD_H
