#ifndef FRUITREADERSTRING_IMPL_H
#define FRUITREADERSTRING_IMPL_H

#include <fruitreader_impl.h>
#include <fruitreaderstring.h>

struct fruitreaderstring_s
{
  fruitreader base;
};

void fruitreaderstring_destructor_vf(fruitreaderstring * const this);
arraylist *fruitreaderstring_read_vf(fruitreaderstring * const this);
extern fruitreader_vtable fruitreaderstring_vt;

#endif
