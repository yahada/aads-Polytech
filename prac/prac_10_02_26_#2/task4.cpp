#include <iostream>
int * merge(const int * a, size_t sa, const int * b, size_t sb, int * c)
{
  int * new_c = new int[sa + sb];
  size_t pa = 0, pb = 0;
  size_t i = 0;
  while (pa != sa - 1  && pb != sb - 1)
  {
    if (pa == sa - 1)
    {
      new_c[i++] = b[pb++];
    } else if (pb == sb - 1)
    {
      new_c[i++] = a[pa++];
    } else if (a[pa] < b[pb])
    {
      new_c[i++] = a[pa++];
    } else 
    {
      new_c[i++] = b[pb++];
    }
  }
  c = new_c;
  return c + sa + sb;
}