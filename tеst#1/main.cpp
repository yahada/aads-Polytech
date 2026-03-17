#include <iostream>

template< class T >
struct BiList {
  T val;
  BiList< T >* next, * prev;
};
template< class T >
struct Vector {
  T* data;
  size_t size, cap;
};

// 1. Посчитать количество элементов данных
template< class T >
size_t size(const Vector< const BiList< T > * > v)
{
  size_t counter = 0;
  for (size_t i = 0; i < v.size; ++i)
  {
    const BiList< T >* head = v.data[i];
    while (head)
    {
      ++counter;
      head = head->next;
    }
  }
  return counter;
}

// 2. Посчитать количество элементов,
// ...удовлетворяющих заданному условию
// ...и сохранить количество таких элементов
template< class T, class P >
size_t count_if(const Vector< const BiList< T > * > v, P p)
{
  size_t counter = 0;
  for (size_t i = 0; i < v.size; ++i)
  {
    const BiList< T >* head = v.data[i];
    while (head)
    {
      if (p(head->val))
      {
        ++counter;
      }
      head = head->next;
    }
  }
  return counter;
}

// 3. Посчитать количество элементов данных
// ...и сохранить размеры каждого списка
template< class T >
size_t size(const Vector< const BiList< T > * > v, BiList< size_t > ** sizes)
{
  size_t counter = 0;
  BiList< size_t > * tail = nullptr;
  for (size_t i = 0; i < v.size; ++i)
  {
    size_t tmpSize = 0;
    const BiList< T >* head = v.data[i];
    while (head)
    {
      ++tmpSize;
      head = head->next;
    }
    BiList< size_t >* newNode = new BiList< size_t >{tmpSize, nullptr, tail};
    if(!(*sizes))
    {
      *sizes = newNode;
    } else
    {
      tail->next = newNode;
    }
    tail = newNode;
    counter += tmpSize;
  }
  return counter;
}

// 4. Посчитать количество элементов,
// ...удовлетворяющих заданному условию
// ...и сохранить количество таких элементов
// ...в каждом списке
template< class T, class P >
size_t count_if(const Vector< const BiList< T > * > v, BiList< size_t > ** sizes, P p)
{
  size_t counter = 0;
  BiList< size_t > * tail = nullptr;
  for (size_t i = 0; i < v.size; ++i)
  {
    size_t tmpSize = 0;
    const BiList< T >* head = v.data[i];
    while(head)
    {
      if (p(head->val))
      {
        ++tmpSize;
      }
      head = head->next;
    }
    BiList< size_t >* newNode = new BiList< size_t >{tmpSize, nullptr, tail};
    if (!(*sizes))
    {
      *sizes = newNode;
    } else
    {
      tail->next = newNode;
    }

    tail = newNode;
    counter += tmpSize;
  }
  return counter;
}

// 5. Посчитать количество элементов,
// ...которые удовлетворяют всем условиям
// ...и сохранить количество таких элементов
// ...в каждом списке
template< class T, class ... P_S >
size_t count_if_all(const Vector< const BiList< T > * > v, BiList< size_t > ** sizes, P_S ... pi)
{
  size_t counter = 0;
  BiList< size_t > * tail = nullptr;
  for (size_t i = 0; i < v.size; ++i)
  {
    size_t tmpSize = 0;
    const BiList< T >* head = v[i];
    while (head)
    {
      if (pi(head->val) && ...)
      {
        ++tmpSize;
      }
      head = head->next;
    }

    BiList< size_t > * newNode = new BiList< size_t > {tmpSize, nullptr, tail};
    if (!(*sizes))
    {
      *sizes = newNode;
    } else
    {
      tail->next = newNode;
    }

    tail = newNode;
    counter += tmpSize;
  }
  return counter;
}

// 6. Найти элементы, удовлетворяющие заданному условию
// ...и сформировать список из указателей на такие элементы
template< class T, class P >
BiList< const BiList< T > * > * find_if(const Vector< const BiList< T > * > v, P p)
{

}


// 7. Освободить память, занимаемую структурой
template< class T >
void clear(Vector< BiList< T > * > v)
{
  for (size_t i = 0; i < v.size; ++i)
  {
    BiList< T > * h = v[i];
    while (h)
    {
      BiList< T >* next = h->next;
      delete h;
      h = next;
    }
  }
  delete[] v.data;
}

// 8. Удалить из структуры списки,
// ...в которых хотя бы один элемент списка
// ...удовлетворяет заданному условию
// Вернуть количество удаленных элементов данных (!)
template< class T, class P >
size_t remove_if_any_in_list(Vector< BiList< T > * > v, P p)
{
  size_t res = 0;
  for (size_t i = 0; i < v.size(); ++i)
  {
    BiList< T >* t = v[i];
    size_t tmpCounter = 0;
    while (t)
    {
      if (p(t.val))
      {
        tmpCounter++;
      }
      t = t->next;
    }

    if (!tmpCounter)
    {
      continue;
    }

    t = t->prev;

    while (t)
    {
      BiList< T >* prev = t->prev;
      delete t;
      t = prev;
      res++;
    }
  }
  return res;
}

// 9. Удалить из структуры элементы,
// ...которые удовлетворяют заданному условию
// Вернуть количество этих элементов
template< class T, class P >
size_t remove_if(Vector< BiList< T > * > v, P p)
{
  size_t res = 0;
  for (size_t i = 0; i < v.size; ++i)
  {
    BiList< T >* head = v[i];
    while (head)
    {
      if (p(head->val))
      {
        BiList< T >* next = head->next;
        next->prev = head->prev;
        delete head;
        head = next;
        res++;
        continue;
      }
      head = head->next;
    }
  }
  return res;
}

template< class T >
void extend(Vector< T >& old, const T& newT)
{
  if (old.cap == 0)
  {
    T* newData = new T[8];
    old.size = 0;
    old.cap = 8;
  }

  if (old.cap >= old.size)
  {
    T* newData = nullptr;
    try
    {
      newData = new T[old.cap * 2];

      for (size_t i = 0; i < old.size; ++i)
      {
        newData[i] = old.data[i];
      }
    }
    catch(const std::exception& e)
    {
      delete[] newData;

    }

    delete[] old.data;
    old.data = newData;
  }

  newData[old.size] = newT;
  old.size++;
}

template <class T>
bool hasNext(const BiList< T > * list)
{
  return list->next!=nullptr;
}

template <class T>
const BiList< T > * next(const BiList< T > * list)
{
  return list->next;
}

template< class T >
BiList< T > * copyList(const BiList< T > * l)
{
  BiList< T >* head = nullptr;
  BiList< T >* tail = nullptr;

  BiList< T >* curr = l;
  while (hasNext(curr))
  {
    try
    {
      BiList< T >* newNode = new BiList< T >{curr->val, nullptr};
      if (!tail)
      {
        head = newNode;
      } else
      {
        tail->next = newNode;
      }
      tail = newNode;
      curr = next(curr);
    }
    catch(...)
    {
      
    }
    

    if ()
    
  }
  

  
}

// 10. Выполнить глубокое копирование структуры данных
template< class T >
Vector< BiList< T > * > copy(const Vector< const BiList< T > * > v)
{
  Vector< BiList< T > * > res;

  
}

// 11. Выполнить глубокое копирования структуры данных,
// ...оставляя только элементы, удовлетворяющие заданному условию
template< class T, class P >
Vector< BiList< T > * > copy_if(const Vector< const BiList< T > * > v, P p);

// 12. Преобразовать структуру данных в вектор
template< class T >
Vector< T > convert_to_vector(const Vector< const BiList< T > * > v)
{
  Vector< T > res;
  res.data = {nullptr, 0, 0};
  for (size_t i = 0; i < v.size; ++i)
  {
    const BiList< T > * head = v[i];
    
  }
}

// 13. Преобразовать структуру данных в список
template< class T >
BiList< T > * convert_to_list(const Vector< const BiList< T > * > v);

// 14. Преобразовать структуру даннных в список,
// ...перенеся узлы из оригинальной структуры
template< class T >
BiList< T > * moved_convert_to_list(Vector< BiList< T > * > v);

// 15. Проверить структуру данных:
// ...убедиться, что в векторе нет списков с общими элементами
template< class T >
bool is_different_lists(const Vector< const BiList< T > * > v);

// 16. Исправить структуру данных:
// ...убрать пустые списки из вектора
// Вернуть количество таких списков
template< class T >
size_t remove_empty(Vector< const BiList< T > * > & v);
