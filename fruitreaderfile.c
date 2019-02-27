#include <stdio.h>
#include <stdlib.h>
#include <fruitreaderfile_impl.h>

static void (*fruitreaderfile_void[])() =
  {
   [FRUITREADER_DESTRUCTOR] = &fruitreader_destructor_vf,
  };

static arraylist *(*fruitreaderfile_arraylist[])() =
  {
   [FRUITREADER_READ] = &fruitreader_read_vf,
  };

static fruitreaderfile_vtable fruitreaderfile_vt =
  {
   .fvoid = fruitreaderfile_void,
   .farraylist = fruitreaderfile_arraylist
  };

fruitreaderfile *fruitreaderfile_new(void)
{
  return (fruitreaderfile *) malloc(sizeof(fruitreaderfile));
}

void fruitreaderfile_constructor(fruitreaderfile * const this,
                                 const char *filename)
{
  fruitreader_constructor((fruitreader *) this);
  this->vt = &fruitreaderfile_vt;
  this->br = fopen(filename, "r"); 
}
