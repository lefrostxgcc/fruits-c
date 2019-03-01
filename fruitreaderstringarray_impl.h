#ifndef FRUITREADERSTRINGARRAY_IMPL_H
#define FRUITREADERSTRINGARRAY_IMPL_H

#include <fruitreaderstring_impl.h>
#include <fruitreaderstringarray.h>

typedef struct fruitreaderstringarray_vtable_s
{
  void (**fvoid)();
  ArrayList * (**farraylist)();
} fruitreaderstringarray_vtable;

struct fruitreaderstringarray_s
{
  fruitreaderstringarray_vtable *vt;
  FILE *br;
};

void fruitreaderstringarray_destructor_vf(fruitreaderstringarray * const this);
ArrayList *fruitreaderstringarray_read_vf(fruitreaderstringarray * const this);
/*!
  Конвертация массива в строку
  \param array Массив из строк
  \return Строка из элементов массива, разделённых \n
*/
char *array_to_string(char *array[], int size);

#endif
