#ifndef CONVERTXML_H
#define CONVERTXML_H

#include <convertable.h>
#include <chip_string.h>
#include <hashmap.h>

typedef struct ConvertXml_s ConvertXml;

ConvertXml *convertxml_new();
void convertxml_constructor(ConvertXml * const this);
void convertxml_destructor(ConvertXml * const this);
String *convertxml_convert(ConvertXml * const this, const HashMap *map);

#endif
