#include <stdio.h>
#include <stdlib.h>
#include <fruitreaderscan_impl.h>

static void (*fruitreaderscan_void[])() =
  {
   [FRUITREADER_DESTRUCTOR] = &fruitreaderscan_destructor_vf,
  };

static ArrayList *(*fruitreaderscan_arraylist[])() =
  {
   [FRUITREADER_READ] = &fruitreader_read_vf,
  };

static fruitreaderscan_vtable fruitreaderscan_vt =
  {
   .fvoid = fruitreaderscan_void,
   .farraylist = fruitreaderscan_arraylist
  };

FruitReaderScan *fruitreaderscan_new(void)
{
  return (FruitReaderScan *) malloc(sizeof(FruitReaderScan));
}

void fruitreaderscan_constructor(FruitReaderScan * const this)
{
  fruitreader_constructor((FruitReader *) this);
  this->vt = &fruitreaderscan_vt;
  this->br = stdin; 
}

void fruitreaderscan_destructor(FruitReaderScan * const this)
{
}


void fruitreaderscan_destructor_vf(FruitReader * const this)
{
  fruitreaderscan_destructor((FruitReaderScan *) this);
}
