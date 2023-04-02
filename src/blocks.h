#ifndef TETROMINOES_H_SENTRY
#define TETROMINOES_H_SENTRY

enum { blocks_count = 7 };
enum { block_height = 2, block_width = 4 };

typedef int (*block_t)[block_width];

void block_new(block_t *block);
void block_delete(block_t block);
void block_show(block_t block);
void block_hide(block_t block);

#endif
