// Board.cpp
#include "../include/Board.h"
#include <algorithm>
#include <cmath>

Tile* Board::findTile(int x, int y) {
    for (auto& tile : tiles_) {
        if (tile.x == x && tile.y == y)
            return &tile;
    }
    return nullptr;
}

Board::Board() : rng_(std::random_device{}()) {
    reset();
}

void Board::spawnTile() {
    std::vector<std::pair<int,int>> empties;
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (!findTile(x, y))
                empties.emplace_back(x, y);
        }
    }
    if (empties.empty())
        return;

    std::uniform_int_distribution<size_t> distPos(0, empties.size() - 1);
    auto [x, y] = empties[distPos(rng_)];

    std::uniform_int_distribution<int> distVal(1, 10);
    int v = (distVal(rng_) == 1 ? 4 : 2);

    int color = static_cast<int>(std::log2(v)) - 1;

    tiles_.emplace_back(x, y, v, color);
}

bool Board::hasMoves() const {
    for (int y = 0; y < 4; ++y)
        for (int x = 0; x < 4; ++x)
            if (!const_cast<Board*>(this)->findTile(x, y))
                return true;
    return false;
}

const std::vector<Tile>& Board::getTiles() const {
    return tiles_;
}

void Board::reset() {
    tiles_.clear();
    spawnTile();
    spawnTile();
}

bool Board::move(const Direction direction) {
    resetMergedFlags();
    bool moved = false;

    for (int line = 0; line < 4; ++line) {
        std::vector<Tile*> cells;

        // 1) Собираем указатели на всё, что есть в этой строке/столбце
        for (int i = 0; i < 4; ++i) {
            int x = (direction == Direction::LEFT  || direction == Direction::RIGHT) ? i    : line;
            int y = (direction == Direction::LEFT  || direction == Direction::RIGHT) ? line : i;
            if (auto* t = findTile(x, y))
                cells.push_back(t);
        }

        // 2) Для Right/Down реверсим порядок
        if (direction == Direction::RIGHT || direction == Direction::DOWN)
            std::reverse(cells.begin(), cells.end());

        // 3) Сливаем пары
        for (std::ptrdiff_t i = 0; i + 1 < static_cast<std::ptrdiff_t>(cells.size()); ++i) {
            Tile* a = cells[i];
            Tile* b = cells[i + 1];
            if (a->value == b->value && !a->merged && !b->merged) {
                a->value *= 2;
                a->merged = true;

                // удаляем b из tiles_
                tiles_.erase(
                    std::remove_if(
                        tiles_.begin(), tiles_.end(),
                        [&](auto& t){ return t.x == b->x && t.y == b->y; }
                    ),
                    tiles_.end()
                );
                cells.erase(cells.begin() + i + 1);
                moved = true;
            }
        }

        // 4) Сдвигаем все в начало/конец линии
        for (std::ptrdiff_t i = 0; i < static_cast<std::ptrdiff_t>(cells.size()); ++i) {
            int nx, ny;
            switch (direction) {
                case Direction::LEFT:
                    nx = static_cast<int>(i);    ny = line; break;
                case Direction::RIGHT:
                    nx = 3 - static_cast<int>(i);ny = line; break;
                case Direction::UP:
                    nx = line;      ny = static_cast<int>(i); break;
                case Direction::DOWN:
                default:
                    nx = line;      ny = 3 - static_cast<int>(i); break;
            }
            Tile* t = cells[i];
            if (t->x != nx || t->y != ny) {
                t->x = nx;
                t->y = ny;
                moved = true;
            }
        }
    }

    return moved;
}


void Board::resetMergedFlags() {
    for (auto& tile : tiles_) {
        tile.merged = false;
    }
}
