#include "tetris.h"
#include <ncurses.h>
#include "blocks.h"
#include "clock.h"
#include "constants.h"

static void field_window_initialize(WINDOW **field_window)
{
  int x, y;

  clear();

  x = (COLS - field_width * 2) / 2 - 1;
  y = (LINES - field_height) / 2;

  mvvline(y, x - 1, '<', field_height + 1);
  mvvline(y, x + field_width * 2 + 2, '>', field_height + 1);
  refresh();

  *field_window = newwin(field_height + 1, field_width * 2 + 2, y, x);
  wborder(*field_window, '!', '!', ' ', '=', '!', '!', '!', '!');
  wrefresh(*field_window);
}

void play_tetris()
{
  WINDOW *field_window;

  int field[field_height][field_width] = {0};
  int ch, move_down_due_to_delay, did_block_land = 0, create_new_block = 1;
  block_t block;

  initscr();
  cbreak();
  curs_set(0);
  noecho();

  field_window_initialize(&field_window);

  keypad(field_window, TRUE);
  wtimeout(field_window, drop_delay);
  for (;;) {
    if (did_block_land)
      create_new_block = 1;

    if (create_new_block) {
      block_new(&block);
      block_show(field_window, block);
      create_new_block = 0;
    }

    ch = wgetch(field_window);
    if (milliseconds_elapsed(&block.moved_down_at) >= drop_delay &&
        ch != ERR && ch != KEY_DOWN) {
      move_down_due_to_delay = 1;
    }
    else {
      move_down_due_to_delay = 0;
    }

    switch (ch) {
      case ERR:
      case KEY_DOWN:
        did_block_land = block_move_down(field_window, &block);
        break;
      case KEY_UP:
        block_rotate(field_window, &block, 0);
        break;
      case ' ':
        block_rotate(field_window, &block, 1);
        break;
      case KEY_LEFT:
        block_move(field_window, &block, -1, 0);
        break;
      case KEY_RIGHT:
        block_move(field_window, &block, 1, 0);
        break;
    }

    if (move_down_due_to_delay)
      did_block_land = block_move_down(field_window, &block);
  }

  endwin();
}
