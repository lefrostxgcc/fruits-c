#ifndef CONVERTABLE_H
#define CONVERTABLE_H

#include <chip_string.h>
#include <hashmap.h>

/**
 * @file
 * Интерфейс для конвертации результата
 * в любой подходящий формат
 * @author Chip
 */
typedef struct convertable_s Convertable;

/**
 Конвертация результатов из словаря в строку
 по определённому в реализации формату.
 @param map словарь с результатами
 @return строка в определённом формате.
*/
String *convertable_convert(Convertable * const this, const HashMap *map);
void convertable_destructor(Convertable * const this);
void convertable_delete(Convertable *this);

#endif
