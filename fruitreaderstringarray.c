#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fruitreaderstringarray_impl.h>

void (*fruitreaderstringarray_void[])() =
  {
   [FRUITREADER_DESTRUCTOR] = &fruitreader_destructor_vf,
  };

arraylist *(*fruitreaderstringarray_arraylist[])() =
  {
   [FRUITREADER_READ] = &fruitreader_read_vf,
  };

fruitreader_vtable fruitreaderstringarray_vt =
  {
   .fvoid = fruitreaderstringarray_void,
   .farraylist = fruitreaderstringarray_arraylist
  };

fruitreaderstringarray *fruitreaderstringarray_new(void)
{
  return (fruitreaderstringarray *) malloc(sizeof(fruitreaderstringarray));
}

void fruitreaderstringarray_constructor(fruitreaderstringarray * const this,
                                        char *array[], int size)
{
  char *s = array_to_string(array, size);
  fruitreaderstring_constructor((fruitreaderstring *) this, s);
  free(s);
}

char *array_to_string(char *array[], int size)
{
  char *items = NULL;
  size_t items_len = 0;
  for (int i = 0; i < size; i++)
    items_len += strlen(array[i]) + 1;
  items_len += 1;
  items = (char *) malloc(items_len + 1);
  if (items == NULL)
    return NULL;
  *items = '\0';
  for (int i = 0; i < size; i++)
    {
      strcat(items, array[i]);
      strcat(items, "\n");
    }
  strcat(items, "\n");
  return items;
}
