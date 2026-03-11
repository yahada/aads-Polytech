#include <iostream>

int * unique(int * a, size_t s)
{
  size_t j = 0;
  for (size_t i = 0; i < s; ++i)
  {
    if (a[j] == a[i])
    {
      a[++j] = a[i];
    }
  }
  return a + j + 1;
}

int * cut(const int * a, size_t s)
{
  int * new_a = new int[s];
  for (size_t i = 0; i < s; ++i)
  {
    new_a[i] = a[i];
  }
  return new_a;
}

void erase(int ** a, size_t s, size_t i);

