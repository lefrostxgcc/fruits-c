#ifndef FRUITREADER_IMPL_H
#define FRUITREADER_IMPL_H

#include <stdio.h>
#include <fruitreader.h>

enum {FRUITREADER_DESTRUCTOR, FRUITREADER_READ};

typedef struct fruitreader_vtable_s
{
  void (**fvoid)();
  ArrayList * (**farraylist)();
} fruitreader_vtable;

struct fruitreader_s
{
  fruitreader_vtable *vt;
  FILE *br;
};

void fruitreader_destructor_vf(FruitReader * const this);
ArrayList *fruitreader_read_vf(FruitReader * const this);

#endif
