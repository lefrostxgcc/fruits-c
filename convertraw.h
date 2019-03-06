#ifndef CONVERTRAW_H
#define CONVERTRAW_H

#include <convertable.h>
#include <chip_string.h>
#include <hashmap.h>

typedef struct ConvertRaw_s ConvertRaw;

ConvertRaw *convertraw_new();
void convertraw_constructor(ConvertRaw * const this);
void convertraw_destructor(ConvertRaw * const this);
String *convertraw_convert(ConvertRaw * const this, const HashMap *map);

#endif
