#include "blocks.h"
#include <ncurses.h>
#include <stdlib.h>
#include "clock.h"
#include "constants.h"

static const char square[] = "[]";

static int blocks[blocks_count][tetromino][tetromino][2] = {
    {/* I */
     {{-2, -1}, {-1, -1}, {0, -1}, {1, -1}},
     {{0, -2}, {0, -1}, {0, 0}, {0, 1}},
     {{-2, -1}, {-1, -1}, {0, -1}, {1, -1}},
     {{0, -2}, {0, -1}, {0, 0}, {0, 1}}},
    {/* O */
     {{-1, -1}, {0, -1}, {-1, 0}, {0, 0}},
     {{-1, -1}, {0, -1}, {-1, 0}, {0, 0}},
     {{-1, -1}, {0, -1}, {-1, 0}, {0, 0}},
     {{-1, -1}, {0, -1}, {-1, 0}, {0, 0}}},
    {/* T */
     {{0, -1}, {-1, 0}, {0, 0}, {1, 0}},
     {{1, 0}, {0, -1}, {0, 0}, {0, 1}},
     {{0, 1}, {1, 0}, {0, 0}, {-1, 0}},
     {{-1, 0}, {0, 1}, {0, 0}, {0, -1}}},
    {/* S */
     {{0, -1}, {1, -1}, {-1, 0}, {0, 0}},
     {{1, 0}, {1, 1}, {0, -1}, {0, 0}},
     {{0, -1}, {1, -1}, {-1, 0}, {0, 0}},
     {{1, 0}, {1, 1}, {0, -1}, {0, 0}}},
    {/* Z */
     {{-1, -1}, {0, -1}, {0, 0}, {1, 0}},
     {{1, -1}, {1, 0}, {0, 0}, {0, 1}},
     {{-1, -1}, {0, -1}, {0, 0}, {1, 0}},
     {{1, -1}, {1, 0}, {0, 0}, {0, 1}}},
    {/* J */
     {{-1, -1}, {-1, 0}, {0, 0}, {1, 0}},
     {{1, -1}, {0, -1}, {0, 0}, {0, 1}},
     {{1, 0}, {1, -1}, {0, -1}, {-1, -1}},
     {{-1, 1}, {0, 1}, {0, 0}, {0, -1}}},
    {/* L */
     {{1, -1}, {-1, 0}, {0, 0}, {1, 0}},
     {{1, 1}, {0, -1}, {0, 0}, {0, 1}},
     {{-1, 0}, {1, -1}, {0, -1}, {-1, -1}},
     {{-1, -1}, {0, 1}, {0, 0}, {0, -1}}}};

static void block_squares_copy(block_squares_t dest, block_squares_t src)
{
  int i;
  for (i = 0; i < tetromino; i++) {
    dest[i][0] = src[i][0];
    dest[i][1] = src[i][1];
  }
}

void block_new(block_t *block)
{
  block->type = rand() % blocks_count;
  block->x = field_width / 2;
  block->y = 0;
  block->angle = 0;
  block->squares = malloc(tetromino * sizeof(*block->squares));
  gettimeofday(&block->moved_down_at, NULL);
  block_squares_copy(block->squares, blocks[block->type][block->angle]);
}

void block_delete(block_t block)
{
  free(block.squares);
}

static void block_print(WINDOW *win, block_t block, const char *str)
{
  int i, y;
  for (i = 0; i < tetromino; i++) {
    y = block.y + block.squares[i][1];
    if (y < 0)
      continue;
    wmove(win, y, (block.x + block.squares[i][0]) * square_width + 1);
    waddstr(win, str);
  }
  wrefresh(win);
}

void block_show(WINDOW *win, block_t block)
{
  block_print(win, block, square);
}

void block_hide(WINDOW *win, block_t block)
{
  block_print(win, block, "  ");
}

void block_rotate(WINDOW *win, block_t *block, int clockwise)
{
  int i, old_angle = block->angle;

  block_hide(win, *block);

  if (clockwise) {
    block->angle++;
    if (block->angle == tetromino)
      block->angle = 0;
  }
  else {
    block->angle--;
    if (block->angle == -1)
      block->angle = tetromino - 1;
  }

  block_squares_copy(block->squares, blocks[block->type][block->angle]);
  for (i = 0; i < tetromino; i++) {
    if (block->y + block->squares[i][1] >= field_height ||
        block->x + block->squares[i][0] < 0 ||
        block->x + block->squares[i][0] >= field_width) {
      block->angle = old_angle;
      block_squares_copy(block->squares, blocks[block->type][block->angle]);
      break;
    }
  }

  block_show(win, *block);
}

void block_move(WINDOW *win, block_t *block, int x, int y)
{
  int i, old_x = block->x, old_y = block->y;

  block_hide(win, *block);

  block->x += x;
  block->y += y;
  for (i = 0; i < tetromino; i++) {
    if (block->y + block->squares[i][1] >= field_height ||
        block->x + block->squares[i][0] < 0 ||
        block->x + block->squares[i][0] >= field_width) {
      block->x = old_x;
      block->y = old_y;
      break;
    }
  }

  block_show(win, *block);
}

int block_move_down(WINDOW *win, block_t *block)
{
  int i, elapsed_time, landed = 0;

  block_move(win, block, 0, 1);

  for (i = 0; i < tetromino; i++) {
    if (block->y + block->squares[i][1] == field_height - 1) {
      landed = 1;
      break;
    }
  }

  elapsed_time = milliseconds_elapsed(&block->moved_down_at);
  if (!landed) {
    gettimeofday(&block->moved_down_at, NULL);
  }

  return landed && elapsed_time >= drop_delay;
}
