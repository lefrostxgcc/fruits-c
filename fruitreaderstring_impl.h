#ifndef FRUITREADERSTRING_IMPL_H
#define FRUITREADERSTRING_IMPL_H

#include <fruitreader_impl.h>
#include <fruitreaderstring.h>

typedef struct fruitreaderstring_vtable_s
{
  void (**fvoid)();
  arraylist * (**farraylist)();
} fruitreaderstring_vtable;

struct fruitreaderstring_s
{
  fruitreaderstring_vtable *vt;
  FILE *br;
};

void fruitreaderstring_destructor_vf(fruitreaderstring * const this);
arraylist *fruitreaderstring_read_vf(fruitreaderstring * const this);

#endif
