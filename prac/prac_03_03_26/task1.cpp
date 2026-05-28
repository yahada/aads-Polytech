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
void clear(List< Vec< T > >* h)
{
  while (h->next)
  {
    delete[] h->val.data;
    List< Vec< T > >* tmp = h;
    h = h->next;
    delete tmp;
  }
}

template< class T >
Vec< T > copy(Vec< T >& v)
{
  Vec< T > new_v;
  new_v.data = nullptr;
  try
  {
    new_v.data = new T[v.s];
    for (size_t i = 0; i < v.s; ++i)
    {
      new_v.data[i] = v.data[i];
    }
    new_v.s = v.s;
  }
  catch (...)
  {
    delete[] new_v.data;
    throw;
  }
  return new_v;
}

template< class T >
List< Vec< T > >* copy(const List< Vec< T > >* h)
{
  if (!h)
  {
    return nullptr;
  }
  List< Vec< T > >* head = new List< Vec< T > >{copy(h->val), nullptr};
  try
  {
    List< Vec< T > >* node = head;
    while (h->next)
    {
      node->next =  new List< Vec< T > >{copy(h->next->val), nullptr};
      h = h->next;
      node = node->next;
    }
  }
  catch (const std::bad_alloc&)
  {
    clear();
    throw;
  }
  return head;
}


template< class T >
List< Vec< T > > * safe_copy(List< Vec< T > > * h)
{
  if (!h)
  {
    return nullptr;
  }

  List< Vec< T > > * head = nullptr;
  Vec< T > temp{nullptr, 0};
  try
  {
    temp = copy(h->val);
//         ^^^^
//      (1)any exc
    head = new List< Vec< T > >{temp, nullptr};
//         ^^^                  ^^^^
// (1) std::bad_alloc       перемещение
    temp = {nullptr, 0};
// затираем чтоб предотвратить неверную очистку
    List< Vec< T > > * curr = head;
    while (h->next)
    {
      temp = copy(h->next->val);
      curr->next = new List< Vec< T > >{temp, nullptr};
      temp = {nullptr, 0};
      h = h->next;
      curr = curr->next;
    }
  }
  catch (...)
  {
    clear(head);
    delete[] temp.data;
    throw;
  }
  return head;
}

