#include <iostream>

int * partition(int * a, size_t s, bool(*c)(int));

void quad_partition(int * a, size_t s, bool(*c1)(int), bool(*c2)(int), int ** pts)
{
  int * y1 = partition(a, s, c1); //Разделяем на две части
  int * y2 = partition(a, y1 - a, c2); //y1 - a - размер; проверяем первую часть по второму условию
  int * y3 = partition(y1, a + s - y1, c2); // проверяем вторую часть по второму условию
  pts[0] = y2;
  pts[1] = y1;
  pts[2] = y3;
}

