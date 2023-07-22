#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constants.h"
#include "tetris.h"

int main()
{
  initscr();
  if (LINES < min_field_height || COLS < min_field_width) {
    endwin();
    fprintf(stderr, "Please resize your terminal to at least %dx%d to play.\n",
            min_field_width, min_field_height);
    return 1;
  }

  srand(time(NULL));

  initscr();
  cbreak();
  curs_set(0);
  noecho();

  play_tetris();

  endwin();

  return 0;
}
