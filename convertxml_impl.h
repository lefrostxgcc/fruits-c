#ifndef CONVERTXML_IMPL_H
#define CONVERTXML_IMPL_H

#include <convertxml.h>
#include <convertable_impl.h>
#include <chip_string.h>
#include <hashmap.h>

enum { CONVERTXML_DESTRUCTOR };
enum { CONVERTXML_CONVERT };

typedef struct convertxml_vtbl_s
{
  void (**fvoid)();
  String * (**fstringp)();
} convertxml_vtbl;

struct ConvertXml_s
{
  convertxml_vtbl *vptr;
};

String *convertxml_convert_vf(Convertable * const this, const HashMap *map);
void convertxml_destructor_vf(Convertable * const this);

#endif
