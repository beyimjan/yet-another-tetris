#include <stdlib.h>
#include <ncurses.h>
#include "blocks.h"

static int blocks[blocks_count][tetromino][tetromino][2] = {
    { /* I */
        {{-2, -1}, {-1, -1}, {0, -1}, {1, -1}},
        {{0, -2}, {0, -1}, {0, 0}, {0, 1}},
        {{-2, -1}, {-1, -1}, {0, -1}, {1, -1}},
        {{0, -2}, {0, -1}, {0, 0}, {0, 1}}
    },
    { /* O */
        {{-1, -1}, {0, -1}, {-1, 0}, {0, 0}},
        {{-1, -1}, {0, -1}, {-1, 0}, {0, 0}},
        {{-1, -1}, {0, -1}, {-1, 0}, {0, 0}},
        {{-1, -1}, {0, -1}, {-1, 0}, {0, 0}}
    },
    { /* T */
        {{0, -1}, {-1, 0}, {0, 0}, {1, 0}},
        {{1, 0}, {0, -1}, {0, 0}, {0, 1}},
        {{0, 1}, {1, 0}, {0, 0}, {-1, 0}},
        {{-1, 0}, {0, 1}, {0, 0}, {0, -1}}
    },
    { /* S */
        {{0, -1}, {1, -1}, {-1, 0}, {0, 0}},
        {{1, 0}, {1, 1}, {0, -1}, {0, 0}},
        {{0, -1}, {1, -1}, {-1, 0}, {0, 0}},
        {{1, 0}, {1, 1}, {0, -1}, {0, 0}}
    },
    { /* Z */
        {{-1, -1}, {0, -1}, {0, 0}, {1, 0}},
        {{1, -1}, {1, 0}, {0, 0}, {0, 1}},
        {{-1, -1}, {0, -1}, {0, 0}, {1, 0}},
        {{1, -1}, {1, 0}, {0, 0}, {0, 1}}
    },
    { /* J */
        {{-1, -1}, {-1, 0}, {0, 0}, {1, 0}},
        {{1, -1}, {0, -1}, {0, 0}, {0, 1}},
        {{1, 0}, {1, -1}, {0, -1}, {-1, -1}},
        {{-1, 1}, {0, 1}, {0, 0}, {0, -1}}
    },
    { /* L */
        {{1, -1}, {-1, 0}, {0, 0}, {1, 0}},
        {{1, 1}, {0, -1}, {0, 0}, {0, 1}},
        {{-1, 0}, {1, -1}, {0, -1}, {-1, -1}},
        {{-1, -1}, {0, 1}, {0, 0}, {0, -1}}
    }
};

static void block_squares_copy(block_squares_t dest, block_squares_t src)
{
    int i;
    for(i = 0; i < tetromino; i++) {
        dest[i][0] = src[i][0];
        dest[i][1] = src[i][1];
    }
}

void block_new(block_t *block)
{
    block->type = rand() % blocks_count;
    block->angle = 0;
    block->squares = malloc(tetromino * sizeof(*block->squares));
    block_squares_copy(block->squares, blocks[block->type][block->angle]);
}

void block_delete(block_t block)
{
    free(block.squares);
}

static void block_print(block_t block, chtype ch)
{
    int i;
    for(i = 0; i < tetromino; i++)
        mvaddch(block.squares[i][1] + 2, block.squares[i][0] + 2, ch);
}

void block_show(block_t block)
{
    block_print(block, '*');
}

void block_hide(block_t block)
{
    block_print(block, ' ');
}

void block_rotate(block_t *block, int clockwise)
{
    if(clockwise) {
        block->angle++;
        if(block->angle == tetromino)
            block->angle = 0;
    } else {
        block->angle--;
        if(block->angle == -1)
            block->angle = tetromino - 1;
    }
    block_squares_copy(block->squares, blocks[block->type][block->angle]);
}
