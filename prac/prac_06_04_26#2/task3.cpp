template< class T >
struct BiTree {
  T val;
  BiTree< T >* lt, * rt;
};

template< class T, class Cmp >
void clear(BiTree< T >* root)
{
  if (!root)
  {
    return;
  }
  clear(root->lt);
  clear(root->rt);
  delete root;
}