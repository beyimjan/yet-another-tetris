#include <stdlib.h>
#include <time.h>
#include "tetris.h"

static const char *logo[] = {"  _____ ___ _____ ___ ___ _    _    ___ ___ ",
                             " |_   _| __|_   _| _ \\_ _| |  | |  | __| _ \\",
                             "   | | | _|  | | |   /| || |__| |__| _||   /",
                             "   |_| |___| |_| |_|_\\___|____|____|___|_|_\\"};

int main()
{
  srand(time(NULL));
  play_tetris();
  return 0;
}
