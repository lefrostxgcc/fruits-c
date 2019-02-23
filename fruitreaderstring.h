#ifndef FRUITREADERSTRING_H
#define FRUITREADERSTRING_H

#include <fruitreader.h>

typedef struct fruitreaderstring_s fruitreaderstring;

fruitreaderstring *fruitreaderstring_new(void);
void fruitreaderstring_constructor(fruitreaderstring * const this,
                                   const char *input);
void fruitreaderstring_destructor(fruitreaderstring * const this);

#endif
