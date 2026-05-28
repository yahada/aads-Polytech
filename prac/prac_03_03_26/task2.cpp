#include <iostream>

template< class T > struct List
{
  T val;
  List< T >* next;
};

template< class T > struct Vec
{
  T* data;
  size_t s;
};

template< class T >
List< T >* next(List< T >* node)
{
  return node->next;
}

template< class T >
bool hasNext(List< T >* node)
{
  return node->next != nullptr;
}

