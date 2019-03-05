#ifndef FRUITREADER_H
#define FRUITREADER_H

#include <arraylist.h>

/*!
  \file
  \author Chip
  Базовый класс для считывания списка фруктов.
  Содержит основной метод для получения списка из BufferedReader потока.
*/

typedef struct fruitreader_s FruitReader;

FruitReader *fruitreader_new(void);
void fruitreader_delete(FruitReader *this);
void fruitreader_constructor(FruitReader * const this);
void fruitreader_destructor(FruitReader * const this);
/**
 Считывает данные из потока
 \return сформированный список фруктов
 */
ArrayList *fruitreader_read(FruitReader * const this);

#endif
