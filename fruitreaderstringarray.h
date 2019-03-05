#ifndef FRUITREADERSTRINGARRAY_H
#define FRUITREADERSTRINGARRAY_H

#include <fruitreader.h>
#include <arraylist.h>

/*!
  Создание начальных данных из массива строк
  \file
  \author Chip
*/

typedef struct fruitreaderstringarray_s FruitReaderStringArray;

FruitReaderStringArray *fruitreaderstringarray_new(void);
/*!
  Конструктор
  \param array массив из строк
*/
void fruitreaderstringarray_constructor(FruitReaderStringArray * const this,
                                        char *array[], int size);
void fruitreaderstringarray_constructor_list(FruitReaderStringArray * const this,
                                             ArrayList *list);
void fruitreaderstringarray_destructor(FruitReaderStringArray * const this);

#endif
