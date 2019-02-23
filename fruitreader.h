#ifndef FRUITREADER_H
#define FRUITREADER_H

#include <arraylist.h>

/*!
  \file
  \author Chip
  Базовый класс для считывания списка фруктов.
  Содержит основной метод для получения списка из BufferedReader потока.
*/

typedef struct fruitreader_s fruitreader;

fruitreader *fruitreader_new(void);
void fruitreader_delete(fruitreader *this);
void fruitreader_constructor(fruitreader * const this);
void fruitreader_destructor(fruitreader * const this);
/**
 Считывает данные из потока
 \return сформированный список фруктов
 */
arraylist *fruitreader_read(fruitreader * const this);

#endif
