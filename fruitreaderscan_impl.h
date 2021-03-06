#ifndef FRUITREADERSCAN_IMPL_H
#define FRUITREADERSCAN_IMPL_H

#include <fruitreader_impl.h>
#include <fruitreaderscan.h>

typedef struct fruitreaderscan_vtable_s
{
  void (**fvoid)();
  ArrayList * (**farraylist)();
} fruitreaderscan_vtable;

struct fruitreaderscan_s
{
  fruitreaderscan_vtable *vt;
  FILE *br;
};

void fruitreaderscan_destructor(FruitReaderScan * const this);
void fruitreaderscan_destructor_vf(FruitReader * const this);
ArrayList *fruitreaderscan_read_vf(FruitReader * const this);

#endif
