#include <stdio.h>
#include <string.h>
#include <object.h>
#include <arraylist.h>
#include <fruit.h>

static char *read_line(char *buf, int size, FILE *stream)
{
  if (!fgets(buf, size, stream))
    return NULL;
  char *nl = strchr(buf, '\n');
  if (nl)
    *nl = '\0';
  return buf;
}

int main(void)
{
  char line[80];
  arraylist *list = arraylist_new();
  arraylist_constructor(list);
  while (strcmp(read_line(line, sizeof line, stdin), "") != 0)
    {
      Fruit fruit = fruit_get(line);
      if (fruit == FRUIT_MAX)
        continue;
      object *object_fruit = object_new();
      object_constructor(object_fruit, &fruit, sizeof fruit);
      arraylist_add(list, object_fruit);
      object_destructor(object_fruit);
      object_free(&object_fruit);
    }
  int count = arraylist_size(list);
  printf("%d\n", count);
  arraylist_destructor(list);
  arraylist_free(&list);
}

