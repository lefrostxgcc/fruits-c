#ifndef OBJECT_IMPL_H
#define OBJECT_IMPL_H

#include <object.h>

enum {OBJECT_DESTRUCTOR, OBJECT_FREE, OBJECT_COPY};

typedef struct vtable_s
{
  void (**fvoid)();
} vtable;

struct object_s
{
  vtable *vt;
  void *data;
  int size;
  int object_size;
};

void object_destructor_vf(object * const this);
void object_free_vf(object ** const this);
void object_copy_vf(object * const this, object *element);
extern vtable object_vt;

#endif
