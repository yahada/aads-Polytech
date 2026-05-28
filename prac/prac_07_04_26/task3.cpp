#include <iostream>

template< class T >
struct TriTree {
  T val0, val1;
  TriTree< T >* lt, * mid, * rt, * parent;
};

template< class T >
struct TriTreeIt
{
  size_t s; //на каком элементе мы стоим val0 или val1;
  TriTree< T >* curr;
};

template< class T >
TriTree< T >* minimum(TriTree< T >* root)
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

template< class T >
TriTree< T >* maximum(TriTree< T >* root)
{
  if (!root)
  {
    return root;
  }
  while (!root->rt)
  {
    root = root->rt;
  }
  return root;
}


template< class T >
T& value(TriTreeIt< T > it)
{
  if (s == 0)
  {
    return it.curr->val0;
  } else
  {
    return it.curr->val1;
  }
}

template< class T >
TriTreeIt< T > next(TriTreeIt< T > it)
{
  TriTree< T >* next = it.curr;
  size_t ind = it.s;
  if (!next)
  {
    return {0, nullptr};
  }

  if (ind == 0)
  {
    if (next->mid)
    {
      next = next->mid;
      next = minimum(next);
      ind = 0;
    }
    else
    {
      ind = 1;
    }
  } else
  {
    if (next->rt)
    {
      next = next->rt;
      next = minimum(next);
      ind = 0;
    } else
    {
      TriTree< T >* parent = next->parent;
      while (parent)
      {
        if (parent->lt = next)
        {
          ind = 0;
          break;
        }
        if (parent->mid == next)
        {
          ind = 1;
          break;
        }
        next = parent;
        parent = next->parent;
      }
    }
  }
  return {next, ind};
}


template< class T >
TriTreeIt< T > prev(TriTreeIt< T > it)
{
  TriTree< T >* next = it.curr;
  size_t ind = it.s;
  if (!next)
  {
    return {0, nullptr};
  }

  if (ind == 1)
  {
    if (next->mid)
    {
      next = next->mid;
      next = maximum(next);
      ind = 1;
    }
    else
    {
      ind = 0;
    }
  } else
  {
    if (next->lt)
    {
      next = next->lt;
      next = maximum(next);
      ind = 1;
    } else
    {
      TriTree< T >* parent = next->parent;
      while (parent)
      {
        if (parent->rt = next)
        {
          ind = 1;
          break;
        }
        if (parent->mid == next)
        {
          ind = 0;
          break;
        }
        next = parent;
        parent = next->parent;
      }
    }
  }
  return {next, ind};
}



