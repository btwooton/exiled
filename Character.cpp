#include "Character.hpp"
#include "Tile.hpp"
#include <ncurses.h>

Character::Character(Character::CharacterClass cclass, int pos_x, int pos_y) {
    this->cclass = cclass;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->sprite = '@';

    switch(cclass) {
        case Character::CharacterClass::FOOTMAN:
            this->max_hp = 50;
            this->hp = 50;
            this->attack = 5;
            break;
        case Character::CharacterClass::ARCHER:
            this->max_hp = 30;
            this->hp = 30;
            this->attack = 3;
            break;
        case Character::CharacterClass::WIZARD:
            this->max_hp = 20;
            this->hp = 20;
            this->attack = 1;
            break;
    }

    this->level = 1;
    this->exp = 0.0;
}

int Character::get_x() {
    return pos_x;
}

int Character::get_y() {
    return pos_y;
}

void Character::move(Map::Direction dir, const Map& map) {
    switch(dir) {
        case Map::Direction::WEST:
            if (this->pos_x > 0) {
                Tile *next = map.get_tile(this->pos_x - 1, this->pos_y);
                if (next->get_type() == Tile::TileType::FLOOR ||
                    next->get_type() == Tile::TileType::DOWN_STAIRS ||
                    next->get_type() == Tile::TileType::UP_STAIRS) {
                    this->move_west();
                }
            }
            break;
        case Map::Direction::NORTH:
            if (this->pos_y > 0) {
                Tile *next = map.get_tile(this->pos_x, this->pos_y - 1);
                if (next->get_type() == Tile::TileType::FLOOR ||
                    next->get_type() == Tile::TileType::DOWN_STAIRS ||
                    next->get_type() == Tile::TileType::UP_STAIRS) {
                    this->move_north();
                }
            }
            break;
        case Map::Direction::EAST:
            if (this->pos_x < map.get_width() - 1) {
                Tile *next = map.get_tile(this->pos_x + 1, this->pos_y);
                if (next->get_type() == Tile::TileType::FLOOR ||
                    next->get_type() == Tile::TileType::DOWN_STAIRS ||
                    next->get_type() == Tile::TileType::UP_STAIRS) {
                    this->move_east();
                }
            }
            break;
        case Map::Direction::SOUTH:
            if (this->pos_y < map.get_height() - 1) {
                Tile *next = map.get_tile(this->pos_x, this->pos_y + 1);
                if (next->get_type() == Tile::TileType::FLOOR ||
                    next->get_type() == Tile::TileType::DOWN_STAIRS ||
                    next->get_type() == Tile::TileType::UP_STAIRS) {
                    this->move_south();
                }
            }
            break;
    }
}

void Character::move_east() {
    this->pos_x += 1;
}

void Character::move_west() {
    this->pos_x -= 1;
}

void Character::move_south() {
    this->pos_y += 1;
}

void Character::move_north() {
    this->pos_y -= 1;
}

char Character::get_sprite() {
    return sprite;
}

void Character::display() {
    mvaddch(this->pos_y, this->pos_x, this->sprite);
}

void Character::display_stats(int screen_height) {
    mvprintw(screen_height - 4, 2, "Health: %d/%d", this->hp, this->max_hp);
    mvprintw(screen_height - 3, 2, "Attack: %d", this->attack);
    const char *class_string = nullptr;
    switch(this->cclass) {
        case CharacterClass::FOOTMAN:
            class_string = "Footman";
            break;
        case CharacterClass::ARCHER:
            class_string = "Archer";
            break;
        case CharacterClass::WIZARD:
            class_string = "Wizard";
            break;
    }
    mvprintw(screen_height - 2, 2, "Level %d %s Exp: %d%%", this->level, class_string, this->exp * 100);
}