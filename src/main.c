#include <ncurses.h>
#include "blocks.h"

int main()
{
    initscr();
    cbreak();
    curs_set(0);
    noecho();

    for(;;) {
        block_t block;
        block_new(&block);
        block_show(block);
        refresh();
        napms(1000);
        block_hide(block);
        block_delete(block);
    }

    endwin();
    return 0;
}
