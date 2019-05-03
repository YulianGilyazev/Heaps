#pragma once
#include <cmath>
template <class Key>
struct node
{
    Key value;
    int degree;
    node<Key>* parent;
    node<Key>* child;
    node<Key>* sibling;
    node<Key>* adoptee;
    bool mark;
    bool deleted;

};

template <class Key>
class fibonacci_heap
{
public:


    bool is_empty();
    pointer* insert(Key key);
    Key get_min();
    Key extract_min();
    void decrease(pointer* p, Key new_value);
    void merge(fibonacci_heap<Key>* otherHeap);
    fibonacci_heap();
private:
    class pointer;
    node<Key>* unionList(node<Key>* x, node<Key>* y);
    node<Key>* tree_merge(node<Key>* root1, node<Key>* root2);
    node<Key>* min;
    int heap_size;
    void consolidate();
    void cascadingCut(node<Key>* x);
    void cut(node<Key>* x);
    int max_degree;
};