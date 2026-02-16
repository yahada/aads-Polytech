#include <cstddef>

template<class T>
T* erase(size_t & valid, const T* a, size_t s, const size_t* eids, size_t toerase)
{
  T* res = new T[s - toerase];
  valid = 0;
  if (!res)
  {
    return nullptr
  }
  size_t j = 0;
  size_t k = 0;
  try
  {
    for (size_t i = 0; i < s; ++i)
    {
      if (eids[j] != i)
      {
        res[k++] = a[i];
        valid++;
      } else
      {
        j++;
      }
    }
  } catch (...)
  {
    return res
  }
  return res;
}

int main()
{

}