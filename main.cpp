#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include "Character.hpp"
#include "Map.hpp"
#include "Tile.hpp"
#include "Money.hpp"

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int h, w;
    int char_x, char_y;

    char input;
    bool playing = true;

    initscr();

    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();
    init_pair(Money::Denomination::COPPER, COLOR_YELLOW, COLOR_BLACK);
    init_pair(Money::Denomination::SILVER, COLOR_CYAN, COLOR_WHITE);
    init_pair(Money::Denomination::GOLD, COLOR_YELLOW, COLOR_WHITE);
    init_pair(Tile::TILE_COLOR_INDEX, COLOR_WHITE, COLOR_BLACK);
    noecho();
    cbreak();
    curs_set(0);

    getmaxyx(stdscr, h, w);
    Map m(w, h - 4);
    m.fill_map(10);
    m.place_character(&char_x, &char_y);
    Character c(Character::CharacterClass::FOOTMAN, char_x, char_y);
    m.display_map();
    c.display();
    c.display_stats(h);
    

    refresh();

    while (playing) {
        if ((input = getch()) != ERR) {
            switch(input) {
                case 'a':
                    c.move(Map::Direction::WEST, m);
                    break;
                case 'w':
                    c.move(Map::Direction::NORTH, m);
                    break;
                case 'd':
                    c.move(Map::Direction::EAST, m);
                    break;
                case 's':
                    c.move(Map::Direction::SOUTH, m);
                    break;
                case 'q':
                    playing = false;
                    break;
            }
            clear();
            m.display_map();
            c.display();
            c.display_stats(h);
            Tile *current_tile = m.get_tile(c.get_x(), c.get_y());
            if (current_tile->has_item()) {
                Item *it = current_tile->get_item();
                mvprintw(h - 4, 50, "You see: %s",
                        it->get_description().c_str());
            }
            refresh();
        }
    }
    endwin();

    return 0;
}