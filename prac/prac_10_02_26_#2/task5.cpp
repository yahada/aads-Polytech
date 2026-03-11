#include <iostream>

int* merge_two(const int* a, size_t sa, const int* b, size_t sb, int* out) {
  size_t i = 0, j = 0, k = 0;

  while (i < sa && j < sb) {
    if (a[i] <= b[j])
    {
      out[k++] = a[i++];
    } else
    {
      out[k++] = b[j++];
    }
  }

  while (i < sa) out[k++] = a[i++];
  while (j < sb) out[k++] = b[j++];

  return out; 
}

int * merge(const int * const * a, size_t sa, const size_t * sai, int * c)
{
  size_t s = sai[0];
  for (size_t i = 0; i < s; ++i)
  {
    c[i] = a[0][i];
  }

  for (size_t i = 1; i < sa; ++i)
  {
    int* temp = new int[s];
    for (size_t i = 0; i < s; ++i) {
      temp[i] = c[i];
    }
    merge_two(temp, s, a[i], sai[i], c);
    delete [] temp;
    s += sai[i];
  }
  return c;
}

int main()
{
  int * aa = new int[2]{1, 5};
  int * bb = new int[2]{2, 4};
  int * cc = new int[2]{3, 6};


  const int * const * aaa = new int *[3]{aa, bb, cc};
  const size_t * sai = new size_t[3]{2, 2, 2};
  int * c = new int[6];
  // int * m = merge_two(aa, 3, bb, 2, c);
  int * m = merge(aaa, 3, sai, c);
  for (size_t i = 0; i < 6; ++i)
  {
    std::cout << c[i] << '\n';
  }
}