#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fruit.h>
#include <fruitreader_impl.h>
#include <arraylist.h>

/*!
 \file
 \author Chip
 Базовый класс для считывания списка фруктов.
 Содержит основной метод для получения списка из BufferedReader потока.
 */

void (*fruitreader_void[])() =
  {
   [FRUITREADER_DESTRUCTOR] = &fruitreader_destructor_vf,
  };

arraylist *(*fruitreader_arraylist[])() =
  {
   [FRUITREADER_READ] = &fruitreader_read_vf,
  };

fruitreader_vtable fruitreader_vt =
  {
   .fvoid = fruitreader_void,
   .farraylist = fruitreader_arraylist
  };

fruitreader *fruitreader_new(void)
{
  return (fruitreader *) malloc(sizeof(fruitreader));
}

void fruitreader_delete(fruitreader *this)
{
  free((void *) this);
}

void fruitreader_constructor(fruitreader * const this)
{
  this->vt = &fruitreader_vt;
  this->br = NULL;
}

void fruitreader_destructor(fruitreader * const this)
{
  this->vt->fvoid[FRUITREADER_DESTRUCTOR](this);
}

void fruitreader_destructor_vf(fruitreader * const this)
{
  if (this->br)
    fclose(this->br);
}

static char *read_line(char *buf, int size, FILE *stream)
{
  if (!fgets(buf, size, stream))
    return NULL;
  char *nl = strchr(buf, '\n');
  if (nl)
    *nl = '\0';
  return buf;
}

/**
 Считывает данные из потока
 \return сформированный список фруктов
 */
arraylist *fruitreader_read(fruitreader * const this)
{
  return this->vt->farraylist[FRUITREADER_READ](this);
}

arraylist *fruitreader_read_vf(fruitreader * const this)
{
  char line[80];
  arraylist *list = arraylist_new();
  arraylist_constructor(list);
  if (this->br == NULL)
    return list;
  while (strcmp(read_line(line, sizeof line, this->br), "") != 0)
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
  return list;
}
