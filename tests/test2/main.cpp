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
public:
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
    if (node_.tb.data[pos_] == nullptr)
    {
      ++pos_;
      while (!node_.tb.data[pos_])
      {
        ++pos_;
      }
      listNode_ = node_.tb.data[pos_];
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

private:
  Table< K, V > node_;
  size_t pos_;
  List< std::pair< K, V > >* listNode_;

};

// Бинарное дерево
// Параметр K - ключ дерева, V - значение
template< class K, class V >
struct Tree {
  Tree< K, V >* minimum()
  {
    Tree< K, V >* root = this;
    if (!root)
    {
      return root;
    }

    while (root->lhs)
    {
      root = root->lhs;
    }
    return root;
  }

  Tree< K, V >* maximum()
  {
    Tree< K, V >* root = this;
    if (!root)
    {
      return root;
    }

    while (root->rhs)
    {
      root = root->rhs;
    }
    return root;
  }
  Tree< K, V >* lhs, * rhs;
  Tree< K, V >* parent;
  std::pair< K, V > val;
};

template< class K, class V >
class TreeIt {
public:
  bool hasNext() const
  {

  }

  TreeIt< K, V >* next()
  {
    if (node_->rhs)
    {
      node_ = node_->rhs;
      node_ = node_->minimum();
    }
    else
    {
      TreeIt< K, V >* parent = node_->parent_;
      while (parent && parent->right_ == node_)
      {
        node_ = parent;
        parent = parent->parent_;
      }
      node_ = parent;
    }
  }

  std::pair< K, V >& value()
  {
    
  }

private:
  Tree< K, V >* node_;
};

template< class T, class U, class W >
using ds_t = Tree< T, Table< U, W > >;


template< class T, class U, class W >
class DsIter {
public:
  bool hasNext() const
  {

  }

  DsIter< T, U, W>& next()
  {

  }

  std::pair< U, W >& value()
  {
    
  }

private:
  Tree< T, Table< U, W > > node_;
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

}

//2.
// Освободить память, занимаемую структурой ИТЕРАТИВНО
// Подсказка: с помощью поворотов превратите дерево в список
template< class T, class U, class W >
void clearit(ds_t< T, U, W > * root) noexcept;

//3.
// Добавить узел дерева с пустой хеш-таблицей
// Вернуть указатель на этот узел
// Параметры пустой хеш-таблицы определяются реализацией
// Поддержите строгую гарантию
template< class T, class U, class W, class CMP >
ds_t< T, U, W >* make_node(ds_t< T, U, W >* root, T key, CMP cmp);

//4.
// Вставить элемент в хеш-таблицу соответствующего узла дерева (создать узел при необходимости)
// Вернуть указатель на узел и номер слота
// Хеш-таблица не расширяется, новые элементы вставляются в конец цепочки
// Поддержите строгую гарантию
template< class T, class U, class W, class CMP, class HASH, class EQ >
std::pair< ds_t< T, U, W >*, size_t > insert(ds_t< T, U, W >* root, T key, CMP cmp, U tkey, HASH h, EQ eq, W val);

//5.
// Подсчитать значения в хеш-таблицах, равные заданному
// Поддержите строгую гарантию
template< class T, class U, class W, class EQ >
size_t count(ds_t< T, U, W >* root, W val, EQ eq);

//6.
// Подсчитать значения в хеш-таблицах, удовлетворяющих условию
// Поддержите строгую гарантию
template< class T, class U, class W, class COND >
size_t count_if(ds_t< T, U, W >* root, COND cond);

//7.
// Переместить элементы хеш-таблицы из указанного узла в другой
// Элементы цепочек хеш-таблицы не должны пересоздаваться
// Хеш-таблица не расширяется, новые элементы вставляются в конец цепочки
// Поддержите базовую гарантию: данные не должны теряться
// В параметр запишите количество перенесенных элементов
template< class T, class U, class W, class CMP, class HASH, class EQ >
void move(size_t& moved, ds_t< T, U, W >* root, T from, T to, CMP cmp, HASH h, EQ eq);

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
void move(size_t& moved, ds_t< T, U, W >** dest, ds_t< T, U, W >** src, ds_t< T, U, W >* root, T from, T to, CMP cmp, HASH h, EQ eq, size_t load);


//9.
// Преобразовать дерево хеш-таблиц в одну хеш-таблицу
// Данные должны быть скопированы
// Поддержите строгую гарантию
template< class T, class U, class W, class HASH, class EQ >
Table< U, W > convert(const ds_t< T, U, W >* root, HASH h, EQ eq);
