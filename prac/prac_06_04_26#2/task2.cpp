#include <iostream>

template< class T >
struct TriTree {
  T val1, val2;
  TriTree< T >* lt, * rt, * mid;
};

template< class T, class Cmp >
const std::pair< TriTree< T >*, size_t > find(const T& d, const TriTree< T >* root, Cmp cmp)
{
  while (root)
  {
    if (cmp(d, root->val1))
    {
      root = root->lt;
    } else if (!cmp(root->val1, d))
    {
      return {root, 0};
    } else if (cmp(d, root->val2))
    {
      root = root->mid;
    } else if (!cmp(root->val2, d))
    {
      return {root, 1};
    } else
    {
      root = root->rt;
    }
  }
  return {nullptr, 0};
}