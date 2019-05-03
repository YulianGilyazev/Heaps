#include "fibonacci_heap.h"
#include <stdexcept>
using std::logic_error;
using std::out_of_range;


template <class Key>
class fibonacci_heap<Key>::pointer
{
    friend fibonacci_heap;
    fibonacci_node<Key>* ptr;
};


template <class Key>
bool fibonacci_heap<Key>::is_empty()
{
    return (heap_size == 0);
}

template <class Key>
fibonacci_heap<Key>::fibonacci_heap()
{
    heap_size = 0;
    min = nullptr;
}
template <class Key>
typename fibonacci_heap<Key>::pointer* fibonacci_heap<Key>::insert(Key key)
{
    ++heap_size;
    fibonacci_node<Key>* K = new fibonacci_node<Key>;
    K->sibling = K;
    K->value = key;
    K->adoptee = K;
    K->deleted = false;
    K->degree = 0;
    K->mark = true;
    K->parent = nullptr;
    K->child = nullptr;
    pointer* a = new pointer;
    a->ptr = K;
    if (min == nullptr)
    {
        min = K;
    }
    else
    {
        unionList(min, K);
        if (min->value > K->value)
            min = K;
    }

    return a;
}

template <class Key>
fibonacci_node<Key>* fibonacci_heap<Key>::unionList(fibonacci_node<Key>* x, fibonacci_node<Key>* y)
{
    if (x == nullptr)
        return y;
    if (y == nullptr)
        return x;
    fibonacci_node<Key>* L = x->sibling;
    fibonacci_node<Key>* R = y->adoptee;
    R->sibling = L;
    L->adoptee = R;
    x->sibling = y;
    y->adoptee = x;
    if (x->value < y->value)
        return x;
    return y;
}

template<class Key>
Key fibonacci_heap<Key>::get_min()
{
    if (heap_size == 0)
        throw logic_error("heap is empty");
    return min->value;
}
template<class Key>
Key fibonacci_heap<Key>::extract_min()
{
    if (heap_size == 0)
        throw logic_error("heap is empty");
    --heap_size;
    min->deleted = true;
    Key ans = min->value;
    if (heap_size == 0)
    {
        min = nullptr;
        return ans;
    }
    fibonacci_node<Key>* A = min->child;
    fibonacci_node<Key>* B = min->child;
    if (B != nullptr)
    {
        B->parent = nullptr;
        fibonacci_node<Key>* U = B->sibling;
        while (U != B)
        {
            U->parent = nullptr;
            U = U->sibling;
        }
    }
    A = unionList(min, A);
    fibonacci_node<Key>* L = min->adoptee;
    fibonacci_node<Key>* R = min->sibling;

    L->sibling = R;
    R->adoptee = L;
    min->adoptee = min;
    min->sibling = min;
    min = R;
    consolidate();
    return ans;
}

template <class Key>
void fibonacci_heap<Key>::consolidate()
{
    if (min == nullptr)
        return;
    typedef fibonacci_node<Key>* F;
    F A[40];
    for (int i = 0; i < 40; i++)
        A[i] = nullptr;
    A[min->degree] = min;
    fibonacci_node<Key>* current = min->sibling;
    while (A[current->degree] != current)
    {
        current->parent = nullptr;
        if (A[current->degree] == nullptr)
        {
            A[current->degree] = current;
            current = current->sibling;
        }
        else
        {
            fibonacci_node<Key>* tree1 = current;
            fibonacci_node<Key>* tree2 = A[current->degree];
            fibonacci_node<Key>* L = tree2->adoptee;
            fibonacci_node<Key>* R = tree2->sibling;
            A[current->degree] = nullptr;
            L->sibling = R;
            R->adoptee = L;
            tree2->sibling = tree2;
            tree2->adoptee = tree2;
            fibonacci_node<Key>* tmp;
            if (current->sibling == current)
                tmp = nullptr;
            else
            {
                tmp = current->adoptee;
                tmp->sibling = current->sibling;
                (tmp->sibling)->adoptee = tmp;
            }
            current->sibling = current;
            current->adoptee = current;
            tree2->sibling = tree2;
            tree2->adoptee = tree2;
            current = tree_merge(tree2, current);
            A[current->degree] = current;
            unionList(tmp, current);
            current = current->sibling;
        }
    }

    min = current;
    fibonacci_node<Key>* B = current;
    current = current->sibling;
    while (current != B)
    {
        if (min->value > current->value)
            min = current;
        current = current->sibling;
    }
}

template <class Key>
fibonacci_node<Key>* fibonacci_heap<Key>::tree_merge(fibonacci_node<Key>* root1, fibonacci_node<Key>* root2)
{
    if (root1 == nullptr)
    {
        if (root2 != nullptr)
        {
            root2->sibling = root2;
            root2->adoptee = root2;
            root2->parent = nullptr;
        }
        return root2;
    }

    if (root2 == nullptr)
    {
        if (root1 != nullptr)
        {
            root1->sibling = root1;
            root1->adoptee = root1;
            root1->parent = nullptr;
        }
        return root1;
    }

    if (root1->value > root2->value)
    {
        tree_merge(root2, root1);
    }
    else
    {
        root1->parent = nullptr;
        root2->parent = nullptr;
        root1->sibling = root1;
        root2->sibling = root2;
        root1->adoptee = root1;
        root2->adoptee = root2;
        fibonacci_node<Key>* curNode1 = root1->child;
        fibonacci_node<Key>* curNode2 = root2;
        root1->child = root2;
        root2->parent = root1;
        (root1->degree)++;
        unionList(curNode1, curNode2);
        return root1;
    }
}
template <class Key>
void fibonacci_heap<Key>::decrease(pointer* p, Key new_value)
{

    fibonacci_node<Key>* x = p->ptr;
    if (x->deleted == true)
        throw logic_error(" element was deleted");
    x->value = new_value;
    if (x->parent == nullptr)
        return;
    if ((x->parent)->value < new_value)
    {
        return;
    }
    cut(x);
    cascadingCut(x->parent);
}

template<class Key>
void fibonacci_heap<Key>::cut(fibonacci_node<Key>* x)
{
    if (x->parent == nullptr)
        return;
    if (x->sibling == x)
    {
        (x->parent)->child = nullptr;
        x->parent = nullptr;
        unionList(x, min);
        if (x->value < min->value)
            min = x;
        return;
    }
    fibonacci_node<Key>* L = x->adoptee;
    fibonacci_node<Key>* R = x->sibling;
    L->sibling = R;
    R->adoptee = L;
    x->sibling = x;
    x->adoptee = x;
    if ((x->parent)->child == x)
        (x->parent)->child = R;
    x->parent = nullptr;
    unionList(min, x);
    if (x->value < min->value)
        min = x;
}

template <class Key>
void fibonacci_heap<Key>::cascadingCut(fibonacci_node<Key>* x)
{
    while (x != nullptr && x->parent != nullptr && x->mark == false)
    {
        fibonacci_node<Key>* tmp = x->parent;
        cut(x);
        x = tmp;
    }
    if (x != nullptr)
        x->mark = false;
}

template <class Key>
void fibonacci_heap<Key>::merge(fibonacci_heap<Key>* otherHeap)
{
    fibonacci_node<Key>* otherMin = otherHeap->min;
    heap_size += otherHeap->heap_size;
    otherHeap->heap_size = 0;
    unionList(min, otherMin);
    if (otherMin->value < min->value)
        min = otherMin;
}