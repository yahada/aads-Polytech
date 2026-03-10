template< class T >
struct MList
{
  T val;
  MList< T >* next;
  MList< T >* tail;
  MList< T >* ref;
};

template< class T >
struct List
{
  T val;
  List< T >* next;
  List< T >* prev;
};

template< class T >
bool has_common(const MList< T >* h1, const MList< T >* h2)
{
  const List< T >* head = h1;
  while (head->prev != nullptr)
  {
    head = head->prev;
  }
  while (head)
  {
    if (head == h2)
    {
      return true;
    }
    head = head->next;
  }
  return false;
}

template< class T >
bool self_refed(MList< T >* h)
{
  auto head = h;
  while (head)
  {
    if (head->val || !has_common(head, head->nex))
    {
      return false;
    }
    head = head->next;
  }
  return true;
  
}
