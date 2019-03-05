#ifndef FRUITREADERSTRING_IMPL_H
#define FRUITREADERSTRING_IMPL_H

#include <fruitreader_impl.h>
#include <fruitreaderstring.h>

typedef struct fruitreaderstring_vtable_s
{
  void (**fvoid)();
  ArrayList * (**farraylist)();
} fruitreaderstring_vtable;

struct fruitreaderstring_s
{
  fruitreaderstring_vtable *vt;
  FILE *br;
};

#endif
