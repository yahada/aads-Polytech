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
using l_t = int;
template< class T, class C >
List< T > * remove_if(List< T > ** head, C cond)
{
  List< T > * r = nullptr, t = *head;
  if (cond(t.val))
  {
    r = t;
    *head = r->next;
    r->next = nullptr;
    t = *head;
    if (cond(t->val))
    {
      while (t->next && cond(t->next->val))
      {
          t = t->next;
          r->next = *head
          *head = t->next;
          t->next = nullptr;
      }
    }
  } else
  {
    while (t.next && !cond(t->next->val))
    {
      t = t->next;
    }
    if(!t->next)
    {
      return nullptr;
    }
    r = t->next;
    t->next = r->next;
  }
}
