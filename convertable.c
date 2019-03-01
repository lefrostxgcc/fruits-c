#include <convertable_impl.h>
#include <stdlib.h>

void convertable_delete(Convertable *p)
{
  free((void *) p);
}

char *convertable_convert(Convertable * const this, const HashMap *map)
{
  return this->vptr->fcharp[CONVERTABLE_CONVERT](this, map);
}

void convertable_destructor(Convertable * const this)
{
  this->vptr->fvoid[CONVERTABLE_DESTRUCTOR](this);
}
