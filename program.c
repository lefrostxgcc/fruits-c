#include <stdio.h>
#include <arraylist.h>
#include <fruitreader.h>
#include <fruitreaderfile.h>

static void start(fruitreader *fr);

int main(void)
{
  fruitreaderfile *fr = fruitreaderfile_new();
  fruitreaderfile_constructor(fr, "fruits.txt");
  start((fruitreader *) fr);
  fruitreader_destructor((fruitreader *) fr);
  fruitreader_delete((fruitreader *) fr);
}

static void start(fruitreader *fr)
{
  arraylist *list = fruitreader_read(fr);
  int count = arraylist_size(list);
  printf("%d\n", count);
  arraylist_destructor(list);
  arraylist_delete(list);
}
