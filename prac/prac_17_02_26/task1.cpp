#include <iostream>

template< class T > struct List {
  T val;
  List< T >* next;
};

template< class T >
List< T >* clear(List< T >* b, List< T >* e)
{
  while (b != e)
  {
    List< T >* n = b->next;
    delete b;
    b = n;
  }
  return e;
}


template< class T >
List< T >* convert(const T* data, size_t s)
{
  List< T >* h = s ? new List< T >{data[0], nullptr} : nullptr;
  List< T >* tail = h;
  try
  {
    for (size_t i = 0; i < s; ++i)
    {
      List< T >* n = new List< T > {data[i], nullptr};
      tail->next = n;
      tail = n;
    }
  } catch (...)
  {
    clear(h, nullptr);
    throw;
  }

  return h;
}


template< class T >
List< T >* convert(const T* data, size_t s, List< T > ** tail)
{
  List< T >* h = s ? new List< T >{data[0], nullptr} : nullptr;
  List< T >* t = h;
  try
  {
    for (size_t i = 0; i < s; ++i)
    {
      List< T >* n = new List< T > {data[i], nullptr};
      t->next = n;
      t = n;
    }
  } catch (...)
  {
    clear(h, nullptr);
    throw;
  }

  *tail = t;
  return h;
}

/*
НЕЯВНЫЙ ИНТЕРФЕЙС:
  -Конструктор копирования (T::T(const T &))

*/