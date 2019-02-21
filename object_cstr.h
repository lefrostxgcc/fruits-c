#ifndef OBJECT_CSTR_H
#define OBJECT_CSTR_H

#include <object.h>

typedef struct object_cstr_s object_cstr;

object_cstr *object_cstr_new(void);
void object_cstr_constructor(object_cstr * const this, const char *str);

#endif
