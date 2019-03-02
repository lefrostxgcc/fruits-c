#include <chip_string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

enum { CAPACITY_MIN = 16, CAPACITY_COEFF = 2 };

struct string_s
{
  char *data;
  int size;
  int capacity;
};

static void string_reallocate(String * const this, int new_size)
{
  int new_capacity = CAPACITY_MIN;
  while (new_capacity <= new_size)
    new_capacity *= CAPACITY_COEFF;
  this->data = realloc(this->data, new_capacity * sizeof (char));
  this->capacity = new_capacity;
}

String *string_new(void)
{
  return (String *) malloc(sizeof(String));
}

void string_delete(String *this)
{
  free(this);
}

void string_constructor(String * const this)
{
  this->data = NULL;
  this->size = this->capacity = 0;
  string_append(this, "");
}

void string_destructor(String * const this)
{
  free(this->data);
  this->data = NULL;
  this->size = this->capacity = 0;
}

String *string_copy(String * const this)
{
  if (!this)
    return NULL;
  String *copy = string_new();
  copy->data = (char *) malloc(this->capacity);
  memcpy(copy->data, this->data, this->size);
  copy->data[this->size] = '\0';
  copy->size = this->size;
  copy->capacity = this->capacity;
  return copy;
}

void string_concat(String * const this, const char *s, ...)
{
  if (!this)
    return;
  va_list ap;
  va_start(ap, s);
  const char *p = NULL;
  while ((p = va_arg(ap, const char *)) != NULL)
    string_append(this, p);
  va_end(ap);
}

String *string_new_concat(const char *s, ...)
{
  String *new_s = string_new();
  va_list ap;
  va_start(ap, s);
  const char *p = NULL;
  while ((p = va_arg(ap, const char *)) != NULL)
    string_append(new_s, p);
  va_end(ap);
  return new_s;
}

void string_append(String * const this, const char *s)
{
  if (!this || !s)
    return;
  size_t old_len = this->size;
  size_t s_len = strlen(s);
  size_t new_len = old_len + s_len;
  if (new_len >= this->capacity)
    string_reallocate(this, new_len);
  memcpy(this->data + old_len, s, s_len);
  this->data[new_len] = '\0';
}

int string_size(String * const this)
{
  return this ? this->size : 0;
}

char string_get(String * const this, int index)
{
  if (!this || index < 0 || index >= this->size)
    return '\0';
  return this->data[index];
}

void string_set(String * const this, int index, char element)
{
  if (!this || index < 0 || index >= this->size)
    return;
  this->data[index] = element;
}

