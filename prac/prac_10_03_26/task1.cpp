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
}
