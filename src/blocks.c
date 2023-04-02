#include <stdlib.h>
#include <ncurses.h>
#include "blocks.h"

static const int blocks[blocks_count][block_height][block_width] = {
    {
        {1, 1, 1, 1},
        {0, 0, 0, 0}
    }, // I-Tetrimino

    {
        {0, 1, 1, 0},
        {0, 1, 1, 0}
    }, // O-Tetrimino

    {
        {0, 1, 0, 0},
        {1, 1, 1, 0}
    }, // T-Tetrimino

    {
        {0, 0, 1, 1},
        {0, 1, 1, 0}
    }, // S-Tetrimino

    {
        {1, 1, 0, 0},
        {0, 1, 1, 0}
    }, // Z-Tetrimino

    {
        {0, 0, 1, 0},
        {1, 1, 1, 0}
    }, // J-Tetrimino

    {
        {1, 0, 0, 0},
        {1, 1, 1, 0}
    } // L-Tetrimino
};

void block_new(block_t *block)
{
    int x, i, j;
    x = rand() % blocks_count;

    *block = malloc(block_height * sizeof(**block));
    for(i = 0; i < block_height; i++)
        for(j = 0; j < block_width; j++)
            (*block)[i][j] = blocks[x][i][j];
}

void block_delete(block_t block)
{
    free(block);
}

static void block_print(block_t block, chtype ch)
{
    int i, j;
    for(i = 0; i < block_height; i++)
        for(j = 0; j < block_width; j++)
            if(block[i][j])
                mvaddch(i, j, ch);
}

void block_show(block_t block)
{
    block_print(block, '*');
}

void block_hide(block_t block)
{
    block_print(block, ' ');
}
