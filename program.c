#include <stdio.h>
#include <string.h>
#include <object_cstr.h>
#include <arraylist.h>

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
      object_cstr *object_line = object_cstr_new();
      object_cstr_constructor(object_line, line);
      arraylist_add(list, (object *) object_line);
      object_destructor((object * const) object_line);
      object_free((object **) &object_line);
    }
  int count = arraylist_size(list);
  printf("%d\n", count);
  arraylist_destructor(list);
  arraylist_free(&list);
}
