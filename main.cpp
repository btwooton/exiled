#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include "Character.hpp"
#include "Map.hpp"
#include "Tile.hpp"

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int h, w;
    int char_x, char_y;

    char input;
    bool playing = true;

    initscr();
    
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
            refresh();
        }
    }
    endwin();

    return 0;
}