#ifndef PARAMFABRIC_H
#define PARAMFABRIC_H

#include <convertable.h>
#include <fruitreader.h>
#include <stdbool.h>

typedef struct
{
  FruitReader *fruitReader;
  Convertable *convertable;
  bool showHelp;
} ParamFabric;

void paramfabric_constructor(ParamFabric * const this, int argc, char *argv[]);
void paramfabric_destructor(ParamFabric * const this);

#endif
