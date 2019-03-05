#include <convertable_impl.h>
#include <stdlib.h>

void convertable_delete(Convertable *p)
{
  free((void *) p);
}

String *convertable_convert(Convertable * const this, const HashMap *map)
{
  return this->vptr->fstringp[CONVERTABLE_CONVERT](this, map);
}

void convertable_destructor(Convertable * const this)
{
  if (this)
    this->vptr->fvoid[CONVERTABLE_DESTRUCTOR](this);
}

