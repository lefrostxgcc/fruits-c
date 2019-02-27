#include <stdio.h>
#include <stdlib.h>
#include <fruitreaderscan_impl.h>

static void (*fruitreaderscan_void[])() =
  {
   [FRUITREADER_DESTRUCTOR] = &fruitreader_destructor_vf,
  };

static arraylist *(*fruitreaderscan_arraylist[])() =
  {
   [FRUITREADER_READ] = &fruitreader_read_vf,
  };

static fruitreaderscan_vtable fruitreaderscan_vt =
  {
   .fvoid = fruitreaderscan_void,
   .farraylist = fruitreaderscan_arraylist
  };

fruitreaderscan *fruitreaderscan_new(void)
{
  return (fruitreaderscan *) malloc(sizeof(fruitreaderscan));
}

void fruitreaderscan_constructor(fruitreaderscan * const this)
{
  fruitreader_constructor((fruitreader *) this);
  this->vt = &fruitreaderscan_vt;
  this->br = stdin; 
}
