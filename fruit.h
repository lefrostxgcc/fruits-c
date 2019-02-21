#ifndef FRUIT_H
#define FRUIT_H

typedef enum
  {
   LEMON,
   ORANGE,
   MANDARIN,
   FRUIT_MAX
  } Fruit;

Fruit fruit_get(const char *line);

#endif
