#ifndef FRUITREADERFILE_IMPL_H
#define FRUITREADERFILE_IMPL_H

#include <fruitreader_impl.h>
#include <fruitreaderfile.h>

typedef struct fruitreaderfile_vtable_s
{
  void (**fvoid)();
  ArrayList * (**farraylist)();
} fruitreaderfile_vtable;

struct fruitreaderfile_s
{
  fruitreaderfile_vtable *vt;
  FILE *br;
};

void fruitreaderfile_destructor_vf(fruitreaderfile * const this);
ArrayList *fruitreaderfile_read_vf(fruitreaderfile * const this);

#endif
