#include "binary_heap.h"
#include<stdexcept>

using std::logic_error;
using std::out_of_range;

template <class Key>
binary_heap<Key>::binary_heap()
{

}

template <class Key>
bool binary_heap<Key>::is_empty() const
{
    return (T.size() == 0);
}

template <class Key>
int* binary_heap<Key>::insert(Key key)
{
    node<Key> x;
    int* a = new int;
    *a = T.size();
    x.value = key;
    x.ptr = nullptr;
    T.push_back(x);
    (T[T.size() - 1]).ptr = a;
    (T[T.size() - 1]).value = key;
    siftUp(T.size() - 1);
    return a;
}
template <class Key>
Key binary_heap<Key>::get_min() const
{
    if (is_empty())
        throw logic_error("Heap is Empty");
    return(T[0].value);
}

template <class Key>
template<typename iterator>
binary_heap<Key>::binary_heap(iterator begin, iterator end)
{
    for (; begin != end; ++begin)
    {
        node<Key> x;
        x.value = *begin;
        x.ptr = nullptr;
        T.push_back(x);
    }
    for (int i = T.size() - 1; i >= 0; i--)
    {
        siftDown(i);
    }
}
template <class Key>
void binary_heap<Key>::siftUp(int i)
{
    if (i > 0)
    {
        if (T[i].value < T[(i - 1) / K].value)
        {
            _swap((i - 1) / K, i);
            siftUp((i - 1) / K);
        }
    }
}

template <class Key>
void binary_heap<Key>::siftDown(int i)
{
    if (i * K + 1 < T.size() - 1)
    {
        int min = i * K + 1;
        for (int j = i * K + 1; j <= (i + 1) * K; ++j)
        {
            if (j <= T.size() - 1 && T[j].value < T[min].value)
                min = j;
        }
        if (T[min].value < T[i].value)
        {
            _swap(min, i);
            siftDown(min);
        }
    }
    if (i * K + 1 == T.size() - 1)
    {
        if (T[i * K + 1].value < T[i].value)
        {
            _swap(i * K + 1, i);
        }
    }
}
template <class Key>
void binary_heap<Key>::_swap(int x, int y)
{
    ans++;
    Key a;
    a = T[x].value;
    T[x].value = T[y].value;
    T[y].value = a;
    int* b = T[x].ptr;
    int* c = T[y].ptr;
    T[x].ptr = c;
    T[y].ptr = b;
    if (T[x].ptr != nullptr)
        *(T[x].ptr) = x;
    if (T[y].ptr != nullptr)
        *(T[y].ptr) = y;
}
template <class Key>
void binary_heap<Key>::optimize(int insertCount, int extractCount)
{
    if (!is_empty())
        throw logic_error("heap is not empty");
    if (extractCount == 0)
    {
        extractCount = 1;
    }
    if (insertCount / extractCount > 2)
    {
        K = insertCount / extractCount;
    }
    else K = 2;
}
template <class Key>
void binary_heap<Key>::erase(int *ptr)
{
    if (ptr == nullptr)
        throw logic_error("element was deleted");
    change(ptr, T[0].value - 1);
    extract_min();

}

template <class Key>
void binary_heap<Key>::change(int *ptr, Key new_value)
{
    Key x = T[*ptr].value;
    if (ptr == nullptr)
        throw logic_error("element was deleted");
    T[*ptr].value = new_value;
    if (new_value > x)
    {
        siftDown(*ptr);
    }
    else
    {
        siftUp(*ptr);
    }
}
template <class Key>
Key binary_heap<Key>::extract_min()
{
    T[0].ptr = nullptr;
    if (is_empty())
        throw logic_error("Heap is Empty!!!");
    Key a = T[0].value;
    _swap(0, T.size() - 1);
    T.pop_back();
    siftDown(0);
    return a;
}
