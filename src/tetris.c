#include "tetris.h"
#include <ncurses.h>
#include "blocks.h"

enum { delay_duration = 500 };

enum { field_height = 20, field_width = 10 };

void field_window_initialize(WINDOW **field_window)
{
  int x, y;
  clear();

  x = (COLS - field_width * 2) / 2 - 1;
  y = (LINES - field_height) / 2;

  mvvline(y, x - 1, '<', field_height + 1);
  mvvline(y, x + field_width * 2, '>', field_height + 1);
  refresh();

  *field_window = newwin(field_height + 1, field_width * 2, y, x);
  wborder(*field_window, '!', '!', ' ', '=', '!', '!', '!', '!');
  wrefresh(*field_window);
}

void play_tetris()
{
  WINDOW *field_window;

  initscr();
  cbreak();
  curs_set(0);
  noecho();

  field_window_initialize(&field_window);

  keypad(field_window, TRUE);
  wgetch(field_window);

  endwin();
}
