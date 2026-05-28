#include <tuple>

template< class T >
struct BiTree {
  T val;
  BiTree< T >* lt, * rt, * parent;
};

template< class T >
struct BiTreeIt {
  BiTree< T >* curr;
};

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

template< class T >
BiTree< T >* maximum(BiTree< T >* root)
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
BiTreeIt< T >* nextAscending(BiTreeIt< T > it)
{
  BiTree< T >* next = it.curr; //Переиспользование кода из traverse
  if (next->lt)
  {
    next = next->lt;
    next = maximum(next);
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
  return {next};
}

enum Dir {
  fall_left,
  parent
};

template< class T >
std::pair< size_t, BiTree< T >* > fallLeft(BiTree< T >* root)
{
  size_t path = 0;
  while (root->lt)
  {
    root = root->lt;
    path++;
  }
  return {path, root};
}

template< class T >
std::pair< size_t, BiTree< T >* > parent_func(BiTree< T >* root)
{
  if (!root)
  {
    return {0, nullptr};
  }
  size_t path = 0;
  BiTree< T >* parent_var = root->parent;
  while (parent_var && parent_var->lt != root)
  {
    root = parent_var;
    parent_var = root->parent;
    path++;
  }
  return {path, parent_var};
}


template< class T >
std::tuple< Dir, size_t, BiTree< T >* >nextStruct(BiTree< T >* root)
{
  if (root->rt)
  {
    auto result = fall_left(root->rt);
    return {Dir::fall_left, result.first, result.second};
  }
  auto result = parent_func(root);
  return (Dir::parent, result.first, result.second);
}
template< class T >
bool isEqualStruct(BiTree< T >* lhs, BiTree< T >* rhs)
{
  auto lhs_b = fall_left(lhs);
  auto rhs_b = fall_left(rhs);
  if (lhs_b.first != rhs_b.first)
  {
    return false;
  }
  auto ln = nextStruct(lhs_b.second);
  auto rn = nextStruct(rhs_b.second);
  while (std::get< 0 >(ln) == std::get< 0 >(rn) &&
        std::get< 1 >(ln) == std::get< 1 >(rn) &&
        std::get< 2 >(ln) && std::get< 2 >(rn))
  {
    ln = nextStruct(std::get< 2 >(ln));
    rn = nextStruct(std::get< 2 >(rn));
  }
  return ln == rn;
}

template< class T >
bool includedStructRoot(BiTree< T >* lhs_root, BiTree< T >* pattern)
{
  auto next_pattern = nextStruct(pattern);
  std::pair< size_t, BiTree< T > * > next_lhs = {0, lhs_root};
  if (std::get< 0 >(next_pattern) == Dir::fall_left)
  {
    if (next_lhs.second->rt)
    {
      next_lhs = fallLeft(next_lhs.second->rt);
    }
    else
    {
      return false;
    }
  }
  else
  {
    next_lhs = Parent(lhs_root);
  }
  std::cout << next_lhs.second->val << "\n";
  std::cout << std::get< 2 >(next_pattern)->val << "\n";
  while (std::get< 1 >(next_pattern) == next_lhs.first && next_lhs.second && std::get< 2 >(next_pattern))
  {

    next_pattern = nextStruct(std::get< 2 >(next_pattern));
    std::cout << (std::get< 0 >(next_pattern) == Dir::fall_left) << "\n";
    if (std::get< 0 >(next_pattern) == Dir::fall_left)
    {
      if (next_lhs.second->rt)
      {
        next_lhs = fallLeft(next_lhs.second->rt);
      }
      else
      {
        return false;
      }
    }
    else
    {
      next_lhs = Parent(lhs_root);
    }
  }
  std::cout << std::get< 1 >(next_pattern) << "\n";
  std::cout << (std::get< 2 >(next_pattern) == nullptr) << "\n";
  return std::get< 1 >(next_pattern) == next_lhs.first && std::get< 2 >(next_pattern) == nullptr;
}

template< class T >
std::tuple< BiTree< T >*, BiTree< T >*, bool> isEqualStructStart(BiTree< T >* lhs_start, BiTree< T >* rhs_start)
{
  auto ln = nextStruct(lhs_start);
  auto rn = nextStruct(rhs_start);
  while (std::get< 0 >(ln) == std::get< 0 >(rn) &&
      std::get< 1 >(ln) == std::get< 1 >(rn) &&
      std::get< 2 >(ln) && std::get< 2 >(rn)) {
    ln = nextStruct(std::get< 2 >(ln));
    rn = nextStruct(std::get< 2 >(rn));
  }
  bool dir = std::get< 0 >(ln) == std::get< 0 >(rn);
  return {std::get< 2 >(ln), std::get< 2 >(rn), dir};
}


template< class T >
bool includedStruct(BiTree<T>* lhs, BiTree<T>* pattern)
{
  BiTree< T >* lhs = fallLeft(lhs).second;
  while (lhs) {
    auto result = isEqualStructStart(lhs, fallLeft(pattern).second);
    if (!std::get< 1 >(result) && std::get< 2 >(result)) {
      return true;
    }
    lhs = nextStruct(lhs).second;
  }
  return false;
}

template< class T >
bool isEqualStruct(BiTree< T >* lhs, BiTree< T >* rhs)
{
  auto lhs_begin = fallLeft(lhs);
  auto rhs_begin = fallLeft(rhs);
  if (lhs_begin.first != rhs_begin.first) {
    return false;
  }
  auto result = isEqualStructStart(lhs_begin.second, rhs_begin.second);
  return !std::get< 0 >(result) && !std::get< 1 >(result);
}

template< class T >
std::pair< BiTree<T>*, BiTree<T>* > // <- диапазон из lhs
 inclusion(
  BiTree<T>* lhs, // здесь ищем вхождения
  BiTree<T>* pattern // образец структуры
)
{
  BiTree< T >* lhs_curr = fall_left(lhs).second;
  while (lhs_curr) {
    auto result = isEqualStructStart(lhs_curr, fallLeft(pattern).second);
    if (!std::get< 1 >(result) && std::get< 2 >(result)) {
      BiTree< T >* last_lhs_next = std::get< 0 >(result);
      if (!last_lhs_next) {
        // lhs тоже закончился, нам нужен последний элемент
        BiTree< T >* lhs_end = lhs;
        while (lhs_end->rt) {
          lhs_end = lhs_end->rt;
        }
        return {lhs_curr, lhs_end};
      }
      BiTree< T >* lhs_end = prev(last_lhs_next);
      return {lhs_curr, lhs_end};
    }
    lhs_curr = nextStruct(lhs_curr).second;
  }
  return false; 
}

template< class T >
BiTree< T >* prev(BiTree< T >* curr)
{
  BiTree< T >* next = curr;
  if (next->lt) {
    next = next->lt;
    while (next->rt) {
      next = next->tr;
    }
  } else {
    BiTree< T >* parent = next->parent;
    while (parent && parent->rt != next) {
      next = parent;
      parent = next->parent;
    }
    next = parent;
  }
  return next;
}