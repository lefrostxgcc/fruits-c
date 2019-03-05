#include <stdio.h>
#include <stdlib.h>
#include <fruitreaderfile_impl.h>

static void (*fruitreaderfile_void[])() =
  {
   [FRUITREADER_DESTRUCTOR] = &fruitreader_destructor_vf,
  };

static ArrayList *(*fruitreaderfile_arraylist[])() =
  {
   [FRUITREADER_READ] = &fruitreader_read_vf,
  };

static fruitreaderfile_vtable fruitreaderfile_vt =
  {
   .fvoid = fruitreaderfile_void,
   .farraylist = fruitreaderfile_arraylist
  };

FruitReaderFile *fruitreaderfile_new(void)
{
  return (FruitReaderFile *) malloc(sizeof(FruitReaderFile));
}

void fruitreaderfile_constructor(FruitReaderFile * const this,
                                 const char *filename)
{
  fruitreader_constructor((FruitReader *) this);
  this->vt = &fruitreaderfile_vt;
  this->br = fopen(filename, "r"); 
}
