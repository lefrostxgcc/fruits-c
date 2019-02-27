#ifndef FRUITREADERSCAN_IMPL_H
#define FRUITREADERSCAN_IMPL_H

#include <fruitreader_impl.h>
#include <fruitreaderscan.h>

typedef struct fruitreaderscan_vtable_s
{
  void (**fvoid)();
  arraylist * (**farraylist)();
} fruitreaderscan_vtable;

struct fruitreaderscan_s
{
  fruitreaderscan_vtable *vt;
  FILE *br;
};

void fruitreaderscan_destructor_vf(fruitreaderscan * const this);
arraylist *fruitreaderscan_read_vf(fruitreaderscan * const this);

#endif
