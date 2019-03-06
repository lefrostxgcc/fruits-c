#ifndef PARAMFACTORY_H
#define PARAMFACTORY_H

#include <convertable.h>
#include <fruitreader.h>
#include <stdbool.h>

typedef struct
{
  FruitReader *fruitReader;
  Convertable *convertable;
  bool isHelp;
} ParamFactory;

void paramfactory_constructor(ParamFactory * const this, int argc, char *argv[]);
void paramfactory_destructor(ParamFactory * const this);
FruitReader *paramfactory_fruitReader(ParamFactory * const this);
Convertable *paramfactory_convertable(ParamFactory * const this);
bool paramfactory_isHelp(ParamFactory * const this);


#endif
