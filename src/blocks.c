#include <stdlib.h>
#include <ncurses.h>
#include "blocks.h"

static int blocks[blocks_count][block_height][block_width] = {
    {
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }, // I-Tetromino

    {
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }, // O-Tetromino

    {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }, // T-Tetromino

    {
        {0, 0, 1, 1},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }, // S-Tetromino

    {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }, // Z-Tetromino

    {
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }, // J-Tetromino

    {
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    } // L-Tetromino
};

static void block_copy(block_t dest, block_t src)
{
    int i, j;
    for(i = 0; i < block_height; i++)
        for(j = 0; j < block_width; j++)
            dest[i][j] = src[i][j];
}

void block_new(block_t *block)
{
    *block = malloc(block_height * sizeof(**block));
    block_copy(*block, blocks[rand() % blocks_count]);
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

void block_rotate(block_t block, int clockwise)
{
    int i, j;
    block_t copy;
    copy = malloc(block_height * sizeof(*copy));
    block_copy(copy, block);
    for (i = 0; i < block_height; i++)
        for (j = 0; j < block_width; j++)
            if(clockwise)
                block[i][j] = copy[3 - j][i];
            else
                block[3 - i][j] = copy[j][i];
    block_delete(copy);
}
