#ifndef FRUITREADERSTRING_H
#define FRUITREADERSTRING_H

#include <fruitreader.h>

/*!
  Считывание данных из строки символов
  \file
  \author Chip
*/

typedef struct fruitreaderstring_s FruitReaderString;

FruitReaderString *fruitreaderstring_new(void);
/*!
  Формирование потока на основе строки данных
  \param input строка символов с исходными данными
*/
void fruitreaderstring_constructor(FruitReaderString * const this,
                                   const char *input);
void fruitreaderstring_destructor(FruitReaderString * const this);

#endif
