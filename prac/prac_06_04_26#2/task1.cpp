#include <iostream>

template< class T >
struct BiTree {
  T val;
  BiTree< T >* lt, * rt;
};

template< class T, class Cmp >
const BiTree< T >* find(const T& d, const BiTree< T >* root, Cmp cmp)
{
  while (root)
  {
    if (cmp(d, root->val))
    {
      root = root->lt;
    } else if (cmp(root->val, d))
    {
      root = root->rt;
    } else
    {
      return root;
    }
  }
  return nullptr;
}