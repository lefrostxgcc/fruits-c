#include <stdio.h>
#include <stdlib.h>
#include <fruitreaderscan_impl.h>

void (*fruitreaderscan_void[])() =
  {
   [FRUITREADER_DESTRUCTOR] = &fruitreader_destructor_vf,
  };

arraylist *(*fruitreaderscan_arraylist[])() =
  {
   [FRUITREADER_READ] = &fruitreader_read_vf,
  };

fruitreader_vtable fruitreaderscan_vt =
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
  ((fruitreader *) this)->vt = &fruitreaderscan_vt;
  ((fruitreader *) this)->br = stdin; 
}
