template< class T >
struct List
{
  T val;
  List< T >* next;
  List< T >* prev;
};

template< class T >
struct MList
{
  T val;
  MList< T >* next;
  MList< T >* tail;
  MList< T >* ref;
};

template< class T >
bool has_ref(MList< T >* list, MList< T >* node)
{
  while (list)
  {
    if (list->ref == node)
    {
      return true;
    }
    list = list->next;
  }
  return false
}

template< class T >
List< const MList< T >* >* no_refs( const MList< T >* h)
{
  List< const MList< T >* > dummy_head{ nullptr, nullptr, nullptr};
  List< const MList< T >* >* tail = &dummy_head;
  List< const MList< T >* >* prev = nullptr;
  MList< T >* inner = h;
  while (inner)
  {
    if (!has_ref(h, has_ref))
    {
      try
      {
        tail->next = new List< const MList< T >* >{inner, nullptr, prev};
        tail = tail->next;
        prev = tail;
      }
      catch(...)
      {
        while (tail)
        {
          List< const MList< T >* >* tmp = tail->prev;
          delete tail;
          tail = tmp;
        }
        throw;
      }
      inner = inner->next;
    }
  }
  return dummy_head.next;
}

