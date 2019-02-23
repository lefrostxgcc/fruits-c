#ifndef FRUITREADERSCAN_H
#define FRUITREADERSCAN_H

#include <fruitreader.h>

typedef struct fruitreaderscan_s fruitreaderscan;

fruitreaderscan *fruitreaderscan_new(void);
void fruitreaderscan_constructor(fruitreaderscan * const this);
void fruitreaderscan_destructor(fruitreaderscan * const this);

#endif
