#ifndef CONSTANTS_H_SENTRY
#define CONSTANTS_H_SENTRY

enum { square_width = 2 };

enum { blocks_count = 7 };
enum { tetromino = 4 };

enum { field_height = 20, field_width = 10 };
enum {
  min_field_height = field_height + 2,
  min_field_width = field_width * 2 + 6
};

enum { drop_delay = 650 };

#endif
