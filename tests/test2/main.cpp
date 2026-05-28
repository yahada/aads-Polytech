#include <cstddef>
#include <utility>

// Вектор
template< class T >
struct Vec {
  T* data;
  size_t size, cap;
};
// Список
template< class T >
struct List {
  List< T >* next;
  T val;
};

// Хеш-таблица с закрытой адресацией
// Разрешение коллизий методом цепочек
// Хешируемый ключ - K, хранимое значение - V
template< class K, class V >
struct Table {
  Vec< List< std::pair< K, V > >* > tb;
};

template< class K, class V >
class TableIt {
  Table< K, V >* node_;
  size_t pos_;
  List< std::pair< K, V > >* listNode_;

  bool hasNext() const
  {
    if (pos_ == node_.tb.size - 1 && node_.tb.data[pos_] == nullptr)
    {
      return false;
    }
    else
    {
      return true;
    }
  }

  TableIt< K, V >& next()
  {
    if (listNode_ == nullptr)
    {
      ++pos_;
      while (pos_ < node_->tb.size && !node_->tb.data[pos_])
      {
        ++pos_;
      }
      if (pos_ < node_->tb.size)
      {
        listNode_ = node_->tb.data[pos_];
      }
      else
      {
        listNode_ = nullptr;
      }
    }
    else
    {
      listNode_ = listNode_->next;
    }
    return *this;
  }

  std::pair< K, V >& value()
  {
    return listNode_->val;
  }


};

// Бинарное дерево
// Параметр K - ключ дерева, V - значение
template< class K, class V >
struct Tree {
  Tree< K, V >* minimum()
  {
    Tree< K, V >* root = this;

    while (root->lhs)
    {
      root = root->lhs;
    }
    return root;
  }

  Tree< K, V >* lhs, * rhs;
  Tree< K, V >* parent;
  std::pair< K, V > val;
};

template< class K, class V >
struct TreeIt {
  Tree< K, V >* node_;

  bool hasNext() const
  {
    return node_ != nullptr;
  }

  TreeIt< K, V >& next()
  {
    if (node_->rhs)
    {
      node_ = node_->rhs;
      node_ = node_->minimum();
    }
    else
    {
      Tree< K, V >* parent = node_->parent;
      while (parent && parent->rhs == node_)
      {
        node_ = parent;
        parent = parent->parent;
      }
      node_ = parent;
    }
    return *this;
  }

  std::pair< K, V >& value()
  {
    return node_->val;
  }
};

template< class T, class U, class W >
using ds_t = Tree< T, Table< U, W > >;


template< class T, class U, class W >
struct DsIter {
  TreeIt< T, Table< U, W > > treeIter_;
  TableIt< U, W > tableIt_;


  bool hasNext() const
  {
    return treeIter_.hasNext() && tableIt_.hasNext();
  }

  DsIter< T, U, W>* next()
  {
    if (tableIt_.hasNext())
    {
      tableIt_.next();
    } else
    {
      treeIter_.next();
      tableIt_ = {treeIter_.value().second};
    }
    return *this;
  }

  std::pair< Table< U, W >, std::pair< U, W > > value()
  {
    return {treeIter_.value().second, tableIt_.value()};
  }
};

// Полагая, что бинарное дерево организовано как дерево поиска,
// а все данные располагаются во Free Store
// решите ниже описанные задачи
// Считайте, что функциональные объекты (типа CMP, HASH, EQ)
// предоставляют строгую гарантию безопасности и не меняют передаваемых
// параметров

//1.
// Освободить память, занимаемую структурой
template< class T, class U, class W >
void clear(ds_t< T, U, W > * root) noexcept
{
  if (root == nullptr)
  {
    return;
  }
  clear(root->rhs);
  clear(root->lhs);
  for (size_t i = 0; i < root->val.second.tb.size; ++i)
  {
    List< std::pair< U, W > >* l = root->val.second.tb.data[i];
    while (l)
    {
      List< std::pair< U, W > >* next = l->next;
      delete l;
      l = next;
    }
  }
  delete[] root->val.second.tb.data;
  delete root;
}

//2.
// Освободить память, занимаемую структурой ИТЕРАТИВНО
// Подсказка: с помощью поворотов превратите дерево в список
template< class T, class U, class W >
void clearit(ds_t< T, U, W > * root) noexcept
{
  DsIter< T, U, W > it{{root}, {&root->val.second, 0, {root->val.second.tb.data[0]}}};

  while (it.hasNext())
  {
    Table< U, W >& t = it.value().first;
    for (size_t i = 0; i < t.tb.size; ++i)
    {
      List< std::pair< U, W > >* l = t.tb.data[i];
      while (l)
      {
        List< std::pair< U, W > >* next = l->next;
        delete l;
        l = next;
      }
    }
    delete[] t.tb.data;
    it.next();
  }
  delete root;
}


template< class T, class U, class W, class CMP >
std::pair< bool, ds_t< T, U, W >* > make_or_find_node(ds_t< T, U, W >* root, T key, CMP cmp)
{
  ds_t< T, U, W >* next = root;
  while (next->lhs != nullptr && next->rhs != nullptr)
  {
    if (!cmp(next->val.first, key) && !cmp(key, next->val.first))
    {
      return {false, next};
    }
    if (cmp(next->val.first, key))
    {
      next = next->rhs;
    }
    else
    {
      next = next->lhs;
    }
  }
  if (cmp(key, next->val.first))
  {
    next->rhs = {T, Table{}};
    ds_t< T, U, W >* ans = next->rhs;
    ans->parent = next;
    ans->rhs = nullptr;
    ans->lhs = nullptr;
    return {true, ans};
  }
  else
  {
    next->lhs = {T, Table{}};
    ds_t< T, U, W >* ans = next->lhs;
    ans->parent = next;
    ans->rhs = nullptr;
    ans->lhs = nullptr;
    return {true, ans};
  }
}


//3.
// Добавить узел дерева с пустой хеш-таблицей
// Вернуть указатель на этот узел
// Параметры пустой хеш-таблицы определяются реализацией
// Поддержите строгую гарантию

template< class T, class U, class W, class CMP >
ds_t< T, U, W >* make_node(ds_t< T, U, W >* root, T key, CMP cmp)
{
  std::pair< bool, ds_t< T, U, W >* > res = make_or_find_node(root, key, cmp);
  if (!res.first)
  {
    res.second = Table{};
  }
  return res.second;
}

//4.
// Вставить элемент в хеш-таблицу соответствующего узла дерева (создать узел при необходимости)
// Вернуть указатель на узел и номер слота
// Хеш-таблица не расширяется, новые элементы вставляются в конец цепочки
// Поддержите строгую гарантию
template< class T, class U, class W, class CMP, class HASH, class EQ >
std::pair< ds_t< T, U, W >*, size_t > insert(ds_t< T, U, W >* root, T key, CMP cmp, U tkey, HASH h, EQ eq, W val)
{
  std::pair< bool, ds_t< T, U, W >* > res = make_or_find_node(root, key, cmp);
  ds_t< T, U, W >* node = res.second;
  Table< U, W >& table = node->val.second;
  size_t pos = table.tb.cap / h(tkey);
  List< std::pair < U, W > >* list = table.tb.data[pos];
  if (!list)
  {
    try
    {
      list = new List< std::pair< U, W > >{nullptr, {tkey, val}};
    }
    catch(const std::exception& e)
    {
      clear(root);
      throw e;
    }

  }
  else
  {
    while (list->next)
    {
      if (tkey, list->val.first)
      {
        list->val.second = val;
        break;
      }
      list = list->next;
    }
    try
    {
      list->next = new List< std::pair< U, W > >{nullptr, {tkey, val}};
    }
    catch(const std::exception& e)
    {
      clear(root);
      throw e;
    }
  }
  return {node, pos};
}
//5.
// Подсчитать значения в хеш-таблицах, равные заданному
// Поддержите строгую гарантию
template< class T, class U, class W, class EQ >
size_t count(ds_t< T, U, W >* root, W val, EQ eq)
{
  DsIter< T, U, W > iter{{root}, {&root->val.second, 0, {root->val.second.tb.data[0]}}};
  size_t res = 0;
  while (iter.hasNext())
  {
    if (eq(iter.value().second.value().second, val))
    {
      ++res;
    }
    iter = iter.next;
  }
  return res;
}

//6.
// Подсчитать значения в хеш-таблицах, удовлетворяющих условию
// Поддержите строгую гарантию
template< class T, class U, class W, class COND >
size_t count_if(ds_t< T, U, W >* root, COND cond)
{
  DsIter< T, U, W > iter{{root}, {&root->val.second, 0, {root->val.second.tb.data[0]}}};
  size_t res = 0;
  while (iter.hasNext())
  {
    if (cond(iter.value().second.value().second))
    {
      ++res;
    }
    iter = iter.next;
  }
  return res;
}

//7.
// Переместить элементы хеш-таблицы из указанного узла в другой
// Элементы цепочек хеш-таблицы не должны пересоздаваться
// Хеш-таблица не расширяется, новые элементы вставляются в конец цепочки
// Поддержите базовую гарантию: данные не должны теряться
// В параметр запишите количество перенесенных элементов
template< class T, class U, class W, class CMP, class HASH, class EQ >
void move(size_t& moved, ds_t< T, U, W >* root, T from, T to, CMP cmp, HASH h, EQ eq)
{
  ds_t< T, U, W >* res = make_or_find_node(root, from, cmp).second;
  Table< U, W > table& = res->val.second;
  TableIt< U, W > iter{&table, 0, table.td.data[0]};
  while (iter.hasNext())
  {
    insert(root, to, cmp, iter.value().first, h, eq, iter.value().second);
    ++moved;
    iter.next();
  }
}

//8.
// Переместить элементы хеш-таблицы из указанного узла в другой
// Элементы цепочек хеш-таблицы не должны пересоздаваться
// Новые элементы вставляются в конец цепочки в хещ-таблице
// Таблица должна быть перестроена, если размер цепочки превышает заданный порог
// Количество слотов в новой хеш-таблице определяется реализацией
// Поддержите базовую гарантию: данные не должны теряться
// В параметр запишите количество перенесенных элементов, узел в который выполнялся перенос
// ...и узел из которого выполнялся перенос
template< class T, class U, class W, class CMP, class HASH, class EQ >
void move(size_t& moved, ds_t< T, U, W >** dest, ds_t< T, U, W >** src, ds_t< T, U, W >* root, T from, T to, CMP cmp, HASH h, EQ eq, size_t load)
{
  ds_t< T, U, W >* res = make_or_find_node(root, from, cmp).second;
  Table< U, W > table& = res->val.second;
  TableIt< U, W > iter{&table, 0, table.td.data[0]};
  while (iter.hasNext())
  {
    insert(root, to, cmp, iter.value().first, h, eq, iter.value().second);
    ++moved;
    iter.next();
  }
}
//9.
// Преобразовать дерево хеш-таблиц в одну хеш-таблицу
// Данные должны быть скопированы
// Поддержите строгую гарантию
template< class T, class U, class W, class HASH, class EQ >
Table< U, W > convert(const ds_t< T, U, W >* root, HASH h, EQ eq);

int main()
{

}
