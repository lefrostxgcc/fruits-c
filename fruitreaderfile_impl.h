#ifndef FRUITREADERFILE_IMPL_H
#define FRUITREADERFILE_IMPL_H

#include <fruitreader_impl.h>
#include <fruitreaderfile.h>

struct fruitreaderfile_s
{
  fruitreader base;
};

void fruitreaderfile_destructor_vf(fruitreaderfile * const this);
arraylist *fruitreaderfile_read_vf(fruitreaderfile * const this);
extern fruitreader_vtable fruitreaderfile_vt;

#endif
