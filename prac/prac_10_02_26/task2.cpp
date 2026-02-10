#include <iostream>

int * remove(int * a, size_t s, size_t i)
{
  int toRm = a[i];
  for (size_t k = i; i < s - 1; ++k)
  {
    a[k] = std::move(a[k + 1]);
  }
  a[s - 1] = std::move(toRm);// c int не стоит использовать. Слишком много времени требуется

  return a + s - 1; //последний элемент
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

void erase(int ** a, size_t s, size_t i)
{
  //...
}


int * remove(int * a, size_t s, int v)
{
  for (size_t k = 0; k < s; ++k)
  {
    if (a[k] == v)
    {
      remove(a, s, k);
      --k;
      --s;
    }
  }
  return a + s;
}



size_t erase(int ** a, size_t s, int v)
{
  size_t upd = remove((*a), s, v) - (*a); // remove(*a, s, v) - *a == последний элемент - первый;
  int * t = cut(*a, upd); 
  delete[] (*a);
  (*a) =t;
  return upd;
}



