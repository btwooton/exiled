#include "Tile.hpp"
#include "Item.hpp"
#include <ncurses.h>

short Tile::TILE_COLOR_INDEX = 123;

Tile::Tile(Tile::TileType type, int pos_x, int pos_y) {
    this->type = type;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}

Tile::~Tile() {
    if (has_item()) {
        for (int i = 0; i < (int)items.size(); i++) {
            delete items[i];
        }
    }
}

Tile::TileType Tile::get_type() const {
    return type;
}

int Tile::get_x() const {
    return pos_x;
}

int Tile::get_y() const {
    return pos_y;
}

void Tile::set_type(Tile::TileType new_type) {
    this->type = new_type;
}

void Tile::display_tile() const {
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
    attron(COLOR_PAIR(TILE_COLOR_INDEX));
    mvaddch(this->pos_y, this->pos_x, sprite);
    attroff(COLOR_PAIR(TILE_COLOR_INDEX));

    if (has_item()) {
        for (int i = 0; i < (int)items.size(); i++) {
            items[i]->display();
        }
    }

}

bool Tile::has_item() const {
    return items.size() > 0;
}

void Tile::add_item(Item *i) {
    this->items.push_back(i);
}

Item *Tile::get_item() const {
    return items[items.size() - 1];
}
