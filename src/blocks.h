#ifndef TETROMINOES_H_SENTRY
#define TETROMINOES_H_SENTRY

enum { blocks_count = 7 };
enum { tetromino = 4 };

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
  int angle;
  block_squares_t squares;
} block_t;

void block_new(block_t *block);
void block_delete(block_t block);
void block_show(block_t block);
void block_hide(block_t block);

void block_rotate(block_t *block, int clockwise);

#endif
