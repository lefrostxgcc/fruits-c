#include <stdlib.h>
#include <string.h>
#include <object_impl.h>

void object_destructor_vf(object * const this)
{
  free(this->data);
  this->data = NULL;
  this->size = 0;
  this->object_size = 0;
}

void object_copy_vf(object * const this, object *element)
{
  memcpy(this->data, element->data, element->size);
  this->size = element->size;
  this->object_size = element->object_size;
}

void (*fvoidfunc[])() =
  {
   [OBJECT_DESTRUCTOR] = &object_destructor_vf,
   [OBJECT_COPY] = &object_copy_vf
  };

vtable object_vt = { .fvoid = fvoidfunc };

object *object_new(void)
{
  return (object *) malloc(sizeof(object));
}

void object_delete(object *this)
{
  free(this);
}

void object_constructor(object * const this, void *data, int size)
{
  this->data = malloc(size);
  memcpy(this->data, data, size);
  this->vt = &object_vt;
  this->size = size;
  this->object_size = sizeof(object);
}

object *object_copy_constructor(object *element)
{
  object *p = (object *) malloc(element->object_size);
  object_constructor(p, element->data, element->size);
  return p;
}

void *object_data(object * const this)
{
  if (!this)
    return NULL;
  return this->data;
}

int object_size(object * const this)
{
  if (!this)
    return 0;
  return this->size;
}

int object_equal(const object * const a, const object * const b)
{
  if (a == b)
    return 1;
  if (!a || !b)
    return 0;
  if (a->size != b->size)
    return 0;
  return memcmp(a->data, b->data, a->size) == 0;
}

void object_copy(object * const this, object *element)
{
  this->vt->fvoid[OBJECT_COPY](this, element);
}

void object_destructor(object * const this)
{
  this->vt->fvoid[OBJECT_DESTRUCTOR](this);
}
