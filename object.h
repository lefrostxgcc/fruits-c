#ifndef OBJECT_H
#define OBJECT_H

typedef struct object_s object;

object *object_new(void);
void object_free(object **this);
void object_constructor(object * const this, void *data, int size);
object *object_copy_constructor(object *element);
void object_copy(object * const this, object *element);
void object_destructor(object * const this);

#endif
