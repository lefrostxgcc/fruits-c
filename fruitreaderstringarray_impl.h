#ifndef FRUITREADERSTRINGARRAY_IMPL_H
#define FRUITREADERSTRINGARRAY_IMPL_H

#include <fruitreaderstring_impl.h>
#include <fruitreaderstringarray.h>

struct fruitreaderstringarray_s
{
  fruitreaderstring base;
};

void fruitreaderstringarray_destructor_vf(fruitreaderstringarray * const this);
arraylist *fruitreaderstringarray_read_vf(fruitreaderstringarray * const this);
/*!
  Конвертация массива в строку
  \param array Массив из строк
  \return Строка из элементов массива, разделённых \n
*/
char *array_to_string(char *array[], int size);
extern fruitreader_vtable fruitreaderstringarray_vt;

#endif
