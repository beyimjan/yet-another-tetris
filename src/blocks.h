#ifndef TETROMINOES_H_SENTRY
#define TETROMINOES_H_SENTRY

#include <ncurses.h>
#include <sys/time.h>

typedef int (*block_squares_t)[2];
typedef enum {
  block_t_i,
  block_t_o,
  block_t_t,
  block_t_s,
  block_t_z,
  block_t_j,
  block_t_l
} block_type_t;

typedef struct {
  block_type_t type;
  int x, y, angle;
  block_squares_t squares;
  struct timeval moved_down_at;
} block_t;

void block_new(block_t *block);
void block_delete(block_t block);
void block_show(WINDOW *win, block_t block);
void block_hide(WINDOW *win, block_t block);

void block_rotate(WINDOW *win, block_t *block, int clockwise);
void block_move(WINDOW *win, block_t *block, int x, int y);
void block_move_down(WINDOW *win, block_t *block);

#endif
