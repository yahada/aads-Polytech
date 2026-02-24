#include <iostream>
//--PREV CODE--
template< class T >
struct List
{
  T val;
  List< T* >* next;
};

template< class T >
size_t size(const List< T* >* h)
{
  size_t counter = 0;
  while (h)
  counter += h->val ? 1 : 0;
  return counter;
}

template< class T >
void clear(List< T* >* h)
{
  while (h)
  {
   List< T* > * n = h->next;
   delete h->val;
   delete h;
   h = n; 
  }
}
//--PREV CODE--




template< class T >
struct List
{
  T val;
  List< T >* next;
};

template< class T >
size_t size(const List< const List< T >* >* h)
{
  size_t counter = 0;
  while (h)
  {
    counter += size< T >(h->val);
    h = h->next;
  }
  return counter;
}

template< class T >
void clear(List< List< T >* >* h)
{
  while (h)
  {
    clear< T >(h->val);
    List< List< T >* >* n = h->next;
    delete h;
    h = n;
  }
}