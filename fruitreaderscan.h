#ifndef FRUITREADERSCAN_H
#define FRUITREADERSCAN_H

#include <fruitreader.h>

/*!
  Считывание с клавиатуры
  \file
  \author Chip
*/

typedef struct fruitreaderscan_s fruitreaderscan;

fruitreaderscan *fruitreaderscan_new(void);
/*!
  Инициализация потока для считывания со стандартного ввода.
*/
void fruitreaderscan_constructor(fruitreaderscan * const this);
void fruitreaderscan_destructor(fruitreaderscan * const this);

#endif
