#ifndef FRUITREADERSTRINGARRAY_H
#define FRUITREADERSTRINGARRAY_H

#include <fruitreader.h>

/*!
  Создание начальных данных из массива строк
  \file
  \author Chip
*/

typedef struct fruitreaderstringarray_s fruitreaderstringarray;

fruitreaderstringarray *fruitreaderstringarray_new(void);
/*!
  Конструктор
  \param array массив из строк
*/
void fruitreaderstringarray_constructor(fruitreaderstringarray * const this,
                                        char *array[], int size);
void fruitreaderstringarray_destructor(fruitreaderstringarray * const this);

#endif
