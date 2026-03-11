#include <cstddef>

template< class T >
T* reverse_1(const T* a, size_t s)
{
  T* r = new T[s]; // T::T()
  try {

  
    for (size_t i = 0; i < s; ++i)
    {
      r[i] = a[s - i - 1]; // T::operator=(T)
    }
  } catch (...) {
    delete[] r;
    throw;
  }
  return r;
}

template<class T> 
void reverse(T* a, size_t s, size_t z)
{
  z = 0;
  for (size_t i = 0; i < s / 2; ++i)
  {
    std::swap(a[i], a[s - (i + 1)]) 
    ++z;
  }

  /*
  I. ЕСЛИ ТИП Т КОПИРУЕТСЯ И НЕ ПЕРЕМЕЩАЕТСЯ
  T temp = a;
  a = b;
  b = a;

  II. ЕСЛИ ТИП Т ПЕРЕМЕЩАЕМЫЙ
  T tmp = std::move(a);
  a = std::move(b);
  b = std::move(tmp);
  */

}