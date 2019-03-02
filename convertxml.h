#ifndef CONVERTXML_H
#define CONVERTXML_H

#include <convertable.h>
#include <chip_string.h>
#include <hashmap.h>

typedef struct ConvertXML_s ConvertXML;

ConvertXML *convertxml_new();
void convertxml_constructor(ConvertXML * const this);
void convertxml_destructor(ConvertXML * const this);
String *convertxml_convert(ConvertXML * const this, const HashMap *map);

#endif
