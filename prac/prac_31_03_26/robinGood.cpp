#include <cstddef>
#include <utility>

template< class Key, class T, class Hash, class Equal >
struct HashTable
{
  using Value = std::pair< Key, T >;
  size_t size;
  size_t capacity;
  Value** slots;
};

template< class K, class T, class Hash, class Equal >
typename HashTable< K, T, Hash, Equal >::Value** find(const HashTable< K, T, Hash, Equal >& table, const K& k)
{

}

template< class K, class T, class Hash, class Equal >
size_t psl(const HashTable< K, T, Hash, Equal >& table, typename HashTable< K, T, Hash, Equal >::Value** value)
{
  Hash hasher;
  size_t home = hasher(*value->first) % table.capacity; //домашний индекс
  size_t ind = value - table.size; //индекс где он стоит
  if (ind >= home)
  {
    return ind - home;
  } else
  {
    return table.capacity - (home - ind);
  }
}