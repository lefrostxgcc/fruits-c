#ifndef OBJECT_H
#define OBJECT_H

typedef struct object_s object;

object *object_new(void);
void object_delete(object *this);
void object_constructor(object * const this, void *data, int size);
void *object_data(object * const this);
int object_size(object * const this);
int object_equal(const object * const a, const object * const b);
object *object_copy_constructor(object *element);
void object_copy(object * const this, object *element);
void object_destructor(object * const this);

#endif
