#ifndef FRUITREADERSCAN_H
#define FRUITREADERSCAN_H

#include <fruitreader.h>

/*!
  Считывание с клавиатуры
  \file
  \author Chip
*/

typedef struct fruitreaderscan_s FruitReaderScan;

FruitReaderScan *fruitreaderscan_new(void);
/*!
  Инициализация потока для считывания со стандартного ввода.
*/
void fruitreaderscan_constructor(FruitReaderScan * const this);
void fruitreaderscan_destructor(FruitReaderScan * const this);

#endif
