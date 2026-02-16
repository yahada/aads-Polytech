#include <cstddef>

template< class T >
T* insert(const T* a, size_t s, size_t i, T v) // конструктор копирования
{
  T * r = new T[s + 1]; //1) T::T()
  try {
  for (size_t k = 0; k < i; ++k)
  {
    r[k] = a[k]; //1) T::operator=(T) 
  }

  r[i] = v; // (2)

  for (size_t k = i + 1; k < s + 1; ++k)
  {
    r[k] = a[k - 1]; //(2)
  }
  } catch (...) {
    delete[] r;
    throw;
  }
  return r;
}