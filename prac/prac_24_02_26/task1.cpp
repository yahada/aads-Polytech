#include <iostream>

template< class T >
struct List
{
  T val;
  List< T >* next;
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