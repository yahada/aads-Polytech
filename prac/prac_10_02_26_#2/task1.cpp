#include <iostream>
void reverse(int * a, int s)
{
  size_t l = 0;
  size_t r = s - 1;
  while (l < r)
  {
    std::swap(a[l++], a[r--]);
  }
}

int * reverse(const int * a, size_t s)
{
  int * new_a = new int[s];
  for (size_t i = 0; i < s; ++i)
  {
    new_a[i] = a[s - i - 1];
  }
  return new_a;
}

int main()
{
  const int * b = new int[5]{1, 2, 3, 4, 5};
  int * a = reverse(b, 5);

  for (size_t i = 0; i < 5; ++i)
  {
    std::cout << a[i] << '\n';
  }
  delete[] b;
  delete[] a;
}

