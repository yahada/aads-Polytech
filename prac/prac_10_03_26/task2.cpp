template< class T >
struct List
{
  T val;
  List< T >* next;
  List< T >* prev;
};

template< class T >
bool has_common(const List< T >* h1, const List< T >* h2)
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
bool no_comon(const List< const List< T >* >* h)
{
  auto head = h;
  const List< T >* curr = nullptr;
  while (head)
  {
    curr = head->next;
    while (curr)
    {
      if (has_common(head->val, curr->val))
      {
        return false
      }
      curr = curr->next;
    }
    head = head->next;
    
  }
  return true;
}