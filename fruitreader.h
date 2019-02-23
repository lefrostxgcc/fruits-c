#ifndef FRUITREADER_H
#define FRUITREADER_H

#include <arraylist.h>

typedef struct fruitreader_s fruitreader;

fruitreader *fruitreader_new(void);
void fruitreader_delete(fruitreader *this);
void fruitreader_constructor(fruitreader * const this);
void fruitreader_destructor(fruitreader * const this);
arraylist *fruitreader_read(fruitreader * const this);

#endif
