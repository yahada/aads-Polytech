#include <iostream>

template< class T >
struct List
{
  T val;
  List< T >* next;
};

template< class T >
struct Vec
{
  T* data;
  size_t size;
};


template< class T >
size_t size(const List< T >* h)
{
  size_t counter = 0;
  while (h)
  {
    ++counter;
    h = h->next;
  }
  return counter;
  
}

template< class T >
void clear(List< T >* h)
{
  while (h)
  {
   List< T > * n = h->next;
   delete h;
   h = n; 
  }
}

template< class T >
size_t size(Vec< const List< T >* > v)
{
  size_t counter = 0;
  for (size_t i = 0; i < v.size; ++i)
  {
    counter += size< T >(v.data[i]);
  }
  return counter;
}

template< class T >
void size(Vec< List< T >* > v)
{
  for (size_t i = 0; i < v.size; ++i)
  {
    clear< T >(v.data[i]);
  }
  delete[] v.data;
}