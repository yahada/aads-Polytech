#include <cstddef>
#include <exception>
template< class T >
struct BiTree {
  T val;
  BiTree< T >* lt, * rt, * parent;
};

template< class T >
BiTree< T >* next(BiTree< T > it);

template< class T >
BiTree< T >* prev(BiTree< T > it);

template< class T >
bool hasNext(BiTree< T > it);

template< class T >
bool hasPrev(BiTree< T > it);

template< class T >
BiTree< T >* fallLeft(BiTree< T >* r)
{
  assert(r);
  while (r->lt)
  {
    r = r->lt;
  }
  return r;
}

template< class T, class Cmp >
bool equal(Cmp cmp, T lhs, T rhs)
{
  return !(cmp(lhs, rhs)) && !(cmp(rhs, lhs));
}

// без использования isEqualRange
// template< class T, class Cmp >
// bool isEqual(BiTree< T >* lhs, BiTree< T >* rhs, Cmp cmp)
// {
//   if (!rhs && !lhs) return true;
//   if (!rhs || !lhs) return false;
//   assert(rhs && lhs);
//   BiTree< T >* blhs = fallLeft(lhs);
//   BiTree< T >* brhs = fallLeft(rhs);
//   while(hasNext(blhs) && hasNext(brhs))
//   {
//     if (!equal(cmp, blhs->val, brhs->val))
//     {
//       return false;
//     }
//     blhs = next(blhs);
//     brhs = next(brhs);
//   }
//   return !hasNext(blhs) && !hasNext(blhs);
// }


template< class T, class Cmp >
bool included(BiTree< T >* origin, BiTree< T >* rhs, Cmp cmp)
{
  if (!rhs) return true;
  if (!origin) return false;
  BiTree< T > brhs = fallLeft(rhs);
  BiTree< T >* b = find(origin, brhs->val, cmp);
  return isEqualRange(brhs, nullptr, b, cmp);
}

template< class T, class Cmp >
bool isEqualRange(BiTree< T >* b1, BiTree< T >* e1, BiTree< T >* b2, Cmp cmp)
{
  while (b1 != e1 && hasNext(b2))
  {
    if (!equal(b1->val, b2->val, cmp))
    {
      return false;
    }
    b1 = next(b1);
    b2 = next(b2);
  }
  return b1 == e1
}

template< class T, class Cmp >
BiTree< T >* find(BiTree< T >* root, T val, Cmp cmp)
{

}

template< class T, class Cmp >
bool isEqual(BiTree< T >* lhs, BiTree< T >* rhs, Cmp cmp) // c использованием isEqualRange
{
  BiTree< T >* b1 = fallLeft(lhs);
  BiTree< T >* b2 = fallLeft(rhs);
  return isEqualRange(b1, nullptr, b2, cmp); // проблема то что isEqualRange останавливается когда b1 == null
}