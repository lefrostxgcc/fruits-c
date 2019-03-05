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

ArrayList *(*fruitreader_arraylist[])() =
  {
   [FRUITREADER_READ] = &fruitreader_read_vf,
  };

fruitreader_vtable fruitreader_vt =
  {
   .fvoid = fruitreader_void,
   .farraylist = fruitreader_arraylist
  };

FruitReader *fruitreader_new(void)
{
  return (FruitReader *) malloc(sizeof(FruitReader));
}

void fruitreader_delete(FruitReader *this)
{
  free((void *) this);
}

void fruitreader_constructor(FruitReader * const this)
{
  this->vt = &fruitreader_vt;
  this->br = NULL;
}

void fruitreader_destructor(FruitReader * const this)
{
  if (this)
    this->vt->fvoid[FRUITREADER_DESTRUCTOR](this);
}

void fruitreader_destructor_vf(FruitReader * const this)
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
ArrayList *fruitreader_read(FruitReader * const this)
{
  return this->vt->farraylist[FRUITREADER_READ](this);
}

ArrayList *fruitreader_read_vf(FruitReader * const this)
{
  char buf[80];
  ArrayList *list = arraylist_new();
  arraylist_constructor(list);
  if (this->br == NULL)
    return list;
  while (1)
    {
      char *line = read_line(buf, sizeof buf, this->br);
      if (line == NULL || strcmp(line, "") == 0)
        break;
      Fruit fruit = fruit_get(line);
      if (fruit == FRUIT_MAX)
        continue;
      object *object_fruit = object_new();
      object_constructor(object_fruit, &fruit, sizeof fruit);
      arraylist_add(list, object_fruit);
      object_destructor(object_fruit);
      object_delete(object_fruit);
    }
  return list;
}
