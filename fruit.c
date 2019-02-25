#include <string.h>
#include <fruit.h>

#define FRUIT_STR(FRUIT) #FRUIT

static const char *fruit_str[] =
  {
   FRUIT_STR(LEMON),
   FRUIT_STR(ORANGE),
   FRUIT_STR(MANDARIN),
   FRUIT_STR(FERRARI),
   FRUIT_STR(TESLA),
   FRUIT_STR(RENAULT),
   FRUIT_STR(MERCEDES),
   FRUIT_STR(BMW)
  };

Fruit fruit_get(const char *line)
{
  for (int i = 0; i < FRUIT_MAX; i++)
    if (strcmp(fruit_str[i], line) == 0)
      return (Fruit) i;
  return (Fruit) FRUIT_MAX;
}
