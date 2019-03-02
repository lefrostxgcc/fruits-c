#ifndef CONVERTRAW_H
#define CONVERTRAW_H

#include <convertable.h>
#include <chip_string.h>
#include <hashmap.h>

typedef struct ConvertRAW_s ConvertRAW;

ConvertRAW *convertraw_new();
void convertraw_constructor(ConvertRAW * const this);
void convertraw_destructor(ConvertRAW * const this);
String *convertraw_convert(ConvertRAW * const this, const HashMap *map);

#endif
