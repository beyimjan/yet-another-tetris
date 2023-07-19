#include "tetris.h"
#include <ncurses.h>
#include "blocks.h"
#include "clock.h"
#include "constants.h"
#include "field.h"

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

static void field_land_block(field_t field, const block_t block)
{
  int i;
  for (i = 0; i < tetromino; i++)
    if (block.y + block.squares[i][1] >= 0)
      field[block.y + block.squares[i][1]][block.x + block.squares[i][0]] = 1;
}

static void remove_completed_lines(WINDOW *win, field_t field, block_t block)
{
  int i, j, k, completed_lines = 0;

  for (i = 0; i < field_height; i++) {
    for (j = 0; j < field_width; j++) {
      if (!field[i][j])
        break;
    }
    if (j == field_width) {
      completed_lines++;
      if (i == 0) {
        for (j = 0; j < field_width; j++)
          field[i][j] = 0;
      }
      else {
        for (k = i; k > 0; k--)
          for (j = 0; j < field_width; j++)
            field[k][j] = field[k - 1][j];
      }
    }
  }

  if (completed_lines) {
    wclear(win);
    wborder(win, '!', '!', ' ', '=', '!', '!', '!', '!');
    block_show(win, block);
    for (i = 0; i < field_height; i++) {
      for (j = 0; j < field_width; j++) {
        if (field[i][j])
          mvwprintw(win, i, j * 2 + 1, "[]");
      }
    }
  }
}

void play_tetris()
{
  WINDOW *field_window;

  int field[field_height][field_width] = {0};
  int ch, move_down_due_to_delay, did_block_land = 0, create_new_block = 1;
  int i, game_over = 0;
  block_t block;

  initscr();
  cbreak();
  curs_set(0);
  noecho();

  field_window_initialize(&field_window);

  keypad(field_window, TRUE);
  wtimeout(field_window, drop_delay);
  for (;;) {
    if (game_over) {
      mvprintw(0, (COLS - 10) / 2, "Game Over!");
      refresh();
      napms(2000);
      break;
    }

    if (did_block_land) {
      field_land_block(field, block);
      block_delete(block);
      did_block_land = 0;
      create_new_block = 1;
    }

    if (create_new_block) {
      block_new(&block);
      for (i = 0; i < tetromino; i++)
        if (block.y + block.squares[i][1] >= 0 &&
            field[block.y + block.squares[i][1]]
                 [block.x + block.squares[i][0]]) {
          game_over = 1;
        }
      if (game_over)
        continue;
      block_show(field_window, block);
      create_new_block = 0;
    }

    ch = wgetch(field_window);
    if (milliseconds_elapsed(&block.moved_down_at) >= drop_delay)
      move_down_due_to_delay = 1;
    else
      move_down_due_to_delay = 0;

    switch (ch) {
      case KEY_UP:
        block_rotate(field_window, field, &block, 0);
        break;
      case ' ':
        block_rotate(field_window, field, &block, 1);
        break;
      case KEY_LEFT:
        block_move(field_window, field, &block, -1, 0);
        break;
      case KEY_RIGHT:
        block_move(field_window, field, &block, 1, 0);
        break;
    }

    if (move_down_due_to_delay || ch == KEY_DOWN || ch == ERR)
      did_block_land = block_move_down(field_window, field, &block);

    remove_completed_lines(field_window, field, block);
  }

  endwin();
}
