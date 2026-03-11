#include <iostream>
int * insert(const int * a, size_t s, size_t i, int v)
{
  int * new_a = new int[s + 1];
  size_t j = 0;
  for (; j < i; ++j)
  {
    new_a[j] = a[j];
  }
  new_a[j++] = v;
  for (; j < s + 1; ++j)
  {
    new_a[j] = a[j - 1];
  }
  return new_a;
}

void insert(int ** a, size_t s, size_t i, int v)
{
  int * new_a = insert(*a, s, i, v);
  delete [] *a;
  *a = new_a;
}

int main()
{
  int * a = new int[5]{1, 2, 3, 4, 5};
  insert(&a, 5, 2, 10);

  for (size_t i = 0; i < 6; ++i)
  {
    std::cout << a[i] << ' ';
  }
  std::cout << '\n';
}
