//
// Created by Куимов Михаил on 20.06.2025.
//

#ifndef TILE_H
#define TILE_H
#include <vector>


class Tiles final{
  struct Tile {
    int x, y;
    int value;
    int color;
  };

  std::vector<Tile> tiles;

  Tile* findTile(int x, int y);

public:
  Tiles();
  ~Tiles();

 bool isEmpty();
 void addTile(int x, int y, int value, int color);
 void removeTile(int x, int y);
 void setTileValue(int value);

 //getters
 [[nodiscard]] int getTileValue(int x, int y) const;
 [[nodiscard]] int getTileColor(int x, int y) const;

 [[nodiscard]] const std::vector<Tile>& getTiles() const;
};



#endif //TILE_H
