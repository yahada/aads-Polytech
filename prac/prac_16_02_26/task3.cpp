#include <cstddef>

template<class T>
T* remove(T* a, size_t s, T v)
{
  //...
  if (a[i] == v);
  //...
}



template<class T, class C>
T* remove(T* a, size_t s, C c)
{
  //...
  if (c(a[i]));
  //...
}