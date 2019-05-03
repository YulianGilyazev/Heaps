#include "my_vector.h"

template <class Key>
struct node
{
    Key value;
    bool mark;
    int* ptr;
};

template <class Key>
class binary_heap
{
public:
    int* insert(Key key);
    bool is_empty() const;
    Key get_min() const;
    Key extract_min();
    void erase(int *ptr);
    void change(int *ptr, Key key);
    binary_heap();
    template <typename iterator>
    binary_heap(iterator begin, iterator end);
    void optimize(int insertCount, int extractCount);


private:
    int K = 2;
    void _swap(int x, int y);
    void siftUp(int i);
    void siftDown(int i);
    my_vector <node<Key>> T;
    my_vector <int> R;
    int ans;


};