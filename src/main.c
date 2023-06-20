#include <stdlib.h>
#include <time.h>
#include "tetris.h"

int main()
{
  srand(time(NULL));
  play_tetris();
  return 0;
}
