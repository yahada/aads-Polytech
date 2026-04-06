#include <iostream>

template< class T >
struct List
{
  T data;
  List< T >* next;
};
template< class T, class Hash, class Eq >
struct HTable {
  size_t k;
  List< T >* slots[];
};

template< class T, class Hash, class Eq >
void insert(const T& val, HTable< T, Hash, Eq > t, Hash hs, Eq eq)
{
  size_t home_num = hs(val) % t.k;
  List< T >* l = t.slots[home_num];
  while (l)
  {
    if (eq(val, l->data))
    {
      return;
    }
    l = l->next;
  }
  t.slots[home_num] = new List< T >{val, t.slots[home_num]};
}

template< class T, class Hash, class Eq >
List< T >* find(const T& val, HTable< T, Hash, Eq > t, Hash hs, Eq eq)
{
  size_t home_num = hs(val) % t.k;
  List< T >* l = t.slots[home_num];
  while (l)
  {
    if (eq(val, l->data))
    {
      return l;
    }
    l = l->next;
  }
  return 0;
}

int main()
{

}
