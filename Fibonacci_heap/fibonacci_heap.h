#pragma once
#include <cmath>

template <class Key>
struct fibonacci_node
{
    Key value;
    int degree;
    fibonacci_node<Key>* parent;
    fibonacci_node<Key>* child;
    fibonacci_node<Key>* sibling;
    fibonacci_node<Key>* adoptee;
    bool mark;
    bool deleted;
};

template <class Key>
class fibonacci_heap
{
private:
    fibonacci_node<Key>* unionList(fibonacci_node<Key>* x, fibonacci_node<Key>* y);
    fibonacci_node<Key>* tree_merge(fibonacci_node<Key>* root1, fibonacci_node<Key>* root2);
    fibonacci_node<Key>* min;
    int heap_size;
    void consolidate();
    void cascadingCut(fibonacci_node<Key>* x);
    void cut(fibonacci_node<Key>* x);
    int max_degree;
public:
    class pointer;
    bool is_empty();
    pointer* insert(Key key);
    Key get_min();
    Key extract_min();
    void decrease(pointer* p, Key new_value);
    void merge(fibonacci_heap<Key>* otherHeap);
    fibonacci_heap();
};