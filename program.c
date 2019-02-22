#include <stdio.h>
#include <arraylist.h>
#include <fruitreader.h>

int main(void)
{
  fruitreader *fr = fruitreader_new();
  fruitreader_constructor(fr);
  const char *s = "LEMON\nORANGE\nMANDARIN\n\n";
  arraylist *list = fruitreader_read_from_string(fr, s);
  int count = arraylist_size(list);
  printf("%d\n", count);
  arraylist_destructor(list);
  arraylist_delete(list);
  fruitreader_destructor(fr);
  fruitreader_delete(fr);
}

