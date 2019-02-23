#ifndef FRUITREADERFILE_H
#define FRUITREADERFILE_H

#include <fruitreader.h>

/*!
 Считывание данных из текстового файла
 \author Chip
 */

typedef struct fruitreaderfile_s fruitreaderfile;

fruitreaderfile *fruitreaderfile_new(void);
/*!
  Подготовка к считыванию из файла.
  \param filename Имя файла
*/
void fruitreaderfile_constructor(fruitreaderfile * const this,
                                 const char *filename);
void fruitreaderfile_destructor(fruitreaderfile * const this);

#endif
