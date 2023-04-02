#include <ncurses.h>
#include "blocks.h"
#include "tetris.h"

enum { delay_duration = 500 };

void play_tetris()
{
    int ch, create_new_block = 1;
    block_t block;

    initscr();
    cbreak();
    curs_set(0);
    noecho();

    keypad(stdscr, TRUE);
    timeout(delay_duration);
    for(;;) {
        if(create_new_block) {
            block_new(&block);
            block_show(block);
            refresh();
            create_new_block = 0;
        }

        ch = getch();
        switch (ch)
        {
        case ' ':
            create_new_block = 1;
            break;
        case KEY_UP:
            block_hide(block);
            block_rotate(&block, 1);
            block_show(block);
            break;
        case KEY_DOWN:
            block_hide(block);
            block_rotate(&block, 0);
            block_show(block);
            break;
        }

        if(create_new_block) {
            block_hide(block);
            refresh();
            block_delete(block);
        }
    }

    endwin();
}
