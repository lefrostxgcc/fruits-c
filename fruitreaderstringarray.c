#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fruitreaderstringarray_impl.h>

static void (*fruitreaderstringarray_void[])() =
  {
   [FRUITREADER_DESTRUCTOR] = &fruitreader_destructor_vf,
  };

static ArrayList *(*fruitreaderstringarray_arraylist[])() =
  {
   [FRUITREADER_READ] = &fruitreader_read_vf,
  };

static fruitreaderstringarray_vtable fruitreaderstringarray_vt =
  {
   .fvoid = fruitreaderstringarray_void,
   .farraylist = fruitreaderstringarray_arraylist
  };

FruitReaderStringArray *fruitreaderstringarray_new(void)
{
  return (FruitReaderStringArray *) malloc(sizeof(FruitReaderStringArray));
}

void fruitreaderstringarray_constructor(FruitReaderStringArray * const this,
                                        char *array[], int size)
{
  char *s = array_to_string(array, size);
  fruitreaderstring_constructor((FruitReaderString *) this, s);
  this->vt = &fruitreaderstringarray_vt;
  free(s);
}

void fruitreaderstringarray_constructor_list(FruitReaderStringArray * const this,
                                             ArrayList *list)
{
  char **array = NULL;
  int size = arraylist_size(list);
  if (size > 0)
    {
      array = (char **) malloc(size * sizeof (char *));
      for (int i = 0; i < size; i++)
        array[i] = (char *) object_data(arraylist_get(list, i));
    }
  fruitreaderstringarray_constructor(this, array, size);
  free(array);
}

char *array_to_string(char *array[], int size)
{
  char *items = NULL;
  size_t items_len = 0;
  for (int i = 0; i < size; i++)
    items_len += strlen(array[i]) + 1;
  items_len += 1;
  items = (char *) malloc(items_len + 2);
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
