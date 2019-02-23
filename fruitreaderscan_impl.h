#ifndef FRUITREADERSCAN_IMPL_H
#define FRUITREADERSCAN_IMPL_H

#include <fruitreader_impl.h>
#include <fruitreaderscan.h>

struct fruitreaderscan_s
{
  fruitreader base;
};

void fruitreaderscan_destructor_vf(fruitreaderscan * const this);
arraylist *fruitreaderscan_read_vf(fruitreaderscan * const this);
extern fruitreader_vtable fruitreaderscan_vt;

#endif
