#include "Tile.hpp"
#include <ncurses.h>

Tile::Tile(Tile::TileType type, int pos_x, int pos_y) {
    this->type = type;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}

Tile::TileType Tile::get_type() {
    return type;
}

int Tile::get_x() {
    return pos_x;
}

int Tile::get_y() {
    return pos_y;
}

void Tile::set_type(Tile::TileType new_type) {
    this->type = new_type;
}

void Tile::display_tile() {
    char sprite;
    switch(this->type) {
        case Tile::TileType::EARTH:
            sprite = ' ';
            break;
        case Tile::TileType::FLOOR:
            sprite = '.';
            break;
        case Tile::TileType::WALL:
            sprite = '#';
            break;
        case Tile::TileType::DOWN_STAIRS:
            sprite = '>';
            break;
        case Tile::TileType::UP_STAIRS:
            sprite = '<';
            break;
    }

    mvaddch(this->pos_y, this->pos_x, sprite);

}