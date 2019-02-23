#ifndef FRUITREADERFILE_H
#define FRUITREADERFILE_H

#include <fruitreader.h>

typedef struct fruitreaderfile_s fruitreaderfile;

fruitreaderfile *fruitreaderfile_new(void);
void fruitreaderfile_constructor(fruitreaderfile * const this,
                                 const char *filename);
void fruitreaderfile_destructor(fruitreaderfile * const this);

#endif
