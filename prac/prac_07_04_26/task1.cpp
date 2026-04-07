template< class T >
struct BiTree {
  T val;
  BiTree< T >* lt, * rt, * parent;
};

// template< class T, class Cmp >
// const BiTree< T >* find(const T& d, const BiTree< T >* root, Cmp cmp)
// {

// }

template< class T >
BiTree< T >* minimum(BiTree< T >* root)
{
  if (!root)
  {
    return root;
  }
  while (!root->lt)
  {
    root = root->lt;
  }
  return root;
}

template< class T, class F >
F traverse(BiTree< T >* root, F f)
{
  if (root)
  {
    return f;
  }

  BiTree< T >* next = minimum(root);
  while (next)
  {
    f(next->val);
    if (next->rt)
    {
      next = next->rt;
      next = minimum(next);
    }
    else
    {
      BiTree< T >* parent = next->parent;
      while (parent && parent->lt == next)
      {
        next = parent;
        parent = next->parent;
      }
      next = parent;
    }
  }
  return f;
}