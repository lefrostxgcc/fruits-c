#ifndef CHIP_STRING_H
#define CHIP_STRING_H

typedef struct string_s String;

String *string_new(void);
void string_delete(String *this);
void string_constructor(String * const this);
void string_destructor(String * const this);
String *string_copy(String * const this);
String *string_new_concat(const char *s, ...);
const char *string_data(const String *this);
void string_concat(String * const this, const char *s, ...);
void string_append(String * const this, const char *s);
int string_size(String * const this);
char string_get(String * const this, int index);
void string_set(String * const this, int index, char element);

#endif
