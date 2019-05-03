#pragma once
#include "binomial_heap.h"
#include<stdexcept>

using std::logic_error;
using std::out_of_range;

template <class Key>
binomial_heap<Key>::binomial_heap()
{
    Heap = nullptr;
    heap_size = 0;
}

template <class Key>
bool binomial_heap<Key>::is_empty()
{
    return (heap_size == 0);
}

template<class Key>
node<Key>* binomial_heap<Key>::tree_extract_min(node<Key>* min)
{
    if (min->degree == 0)
        return nullptr;
    if (min->degree == 1)
    {
        (min->child)->parent == nullptr;
        return min->child;
    }
    node<Key>* curH = nullptr;
    node<Key>* R = min->child;
    node<Key>* Q = nullptr;
    curH = R->sibling;
    R->sibling = nullptr;
    R->adoptee = nullptr;
    while (curH != nullptr)
    {
        Q = curH->sibling;
        curH->sibling = nullptr;
        curH->adoptee = nullptr;
        R = heap_merge(R, curH);
        curH = Q;
    }
    return R;
}

template <class Key>
node<Key>* binomial_heap<Key>::tree_merge(node<Key>* root1, node<Key>* root2)
{
    if (root1 == nullptr)
        return root2;
    if (root2 == nullptr)
        return root1;
    root1->parent = nullptr;
    root2->parent = nullptr;
    root1->sibling = nullptr;
    root2->sibling = nullptr;
    root1->adoptee = nullptr;
    root2->adoptee = nullptr;
    if (root1->value > root2->value)
    {
        tree_merge(root2, root1);
    }
    else
    {
        node<Key>* curNode1 = root1->child;
        node<Key>* curNode2 = root2;
        root1->child = root2;
        root2->parent = root1;
        (root1->degree)++;
        if (curNode1 != nullptr)
        {
            curNode2->sibling = curNode1;
            curNode1->adoptee = curNode2;
        }
        return root1;
    }
}

template <class Key>
node<Key>* binomial_heap<Key>::heap_merge(node<Key>* heap1, node<Key>* heap2)
{
    if (heap1 == nullptr)
    {
        return heap2;
    }
    if (heap2 == nullptr)
    {
        return heap1;
    }
    node<Key> *curHeap1;
    node<Key> *curHeap2;
    curHeap1 = heap1;
    curHeap2 = heap2;
    node<Key>* H = nullptr;
    node<Key>* curH = nullptr;
    if (curHeap1->degree < curHeap2->degree)
    {
        curH = curHeap1;
        curHeap1 = curHeap1->sibling;
    }
    else
    {
        curH = curHeap2;
        curHeap2 = curHeap2->sibling;
    }
    H = curH;
    curH->adoptee = nullptr;
    while (curHeap1 != nullptr && curHeap2 != nullptr)
    {
        if (curHeap1->degree < curHeap2->degree)
        {
            curH->sibling = curHeap1;
            (curH->sibling)->adoptee = curH;
            curHeap1 = curHeap1->sibling;
            curH = curH->sibling;
        }
        else
        {
            curH->sibling = curHeap2;
            (curH->sibling)->adoptee = curH;
            curHeap2 = curHeap2->sibling;
            curH = curH->sibling;
        }
    }
    if (curHeap1 == nullptr)
    {
        while (curHeap2 != nullptr)
        {
            curH->sibling = curHeap2;
            curHeap2->adoptee = curH;
            curH = curH->sibling;
            curHeap2 = curHeap2->sibling;
        }
    }
    else
    {
        while (curHeap1 != nullptr)
        {
            curH->sibling = curHeap1;
            curHeap1->adoptee = curH;
            curH = curH->sibling;
            curHeap1 = curHeap1->sibling;
        }
    }
    curH->sibling = nullptr;
    curH = H;
    while (curH->sibling != nullptr)
    {
        if (curH->sibling != nullptr)
        {
            if ((curH->sibling)->sibling != nullptr)
            {
                if (curH->degree == (curH->sibling)->degree && curH->degree == ((curH->sibling)->sibling)->degree)
                    curH = curH->sibling;
            }
        }
        if (curH->degree == (curH->sibling)->degree)
        {
            node<Key>* L = (curH->sibling)->sibling;
            node<Key>* Q = curH->adoptee;
            node<Key>* R = tree_merge(curH, curH->sibling);
            if (Q == nullptr)
            {
                curH = R;
                H = curH;
                curH->adoptee = nullptr;
                curH->sibling = L;
                if (curH->sibling != nullptr)
                {
                    (curH->sibling)->adoptee = curH;
                }
            }
            else
            {
                R->adoptee = Q;
                R->sibling = L;
                curH = R;
                (curH->adoptee)->sibling = curH;
                if (curH->sibling != nullptr)
                {
                    (curH->sibling)->adoptee = curH;
                }
            }
        }
        else
            curH = curH->sibling;
    }
    return H;
}

template <class Key>
Key binomial_heap<Key>::get_min()
{
    if (heap_size == 0)
        throw logic_error("heap_is_empty");
    node<Key>* curH = Heap;
    Key min = Heap->value;
    while (curH->sibling != nullptr)
    {
        curH = curH->sibling;
        if (min > curH->value)
            min = curH->value;
    }
    return min;
}

template <class Key>
node<Key>* binomial_heap<Key>::insert(Key key)
{
    ++heap_size;
    node<Key>* K = new node<Key>;
    K->value = key;
    K->sibling = nullptr;
    K->adoptee = nullptr;
    K->degree = 0;
    K->parent = nullptr;
    K->child = nullptr;
    K->mark = 0;
    node<Key>* a = new node<Key>;
    a->point = K;
    K->point = a;
    Heap = heap_merge(Heap, K);
    return a;
}

template <class Key>
Key binomial_heap<Key>::extract_min()
{
    if (heap_size == 0)
        throw logic_error("heap_is_empty");
    node<Key>* min;
    Key ans;
    node<Key>* curH = Heap;
    heap_size--;
    ans = Heap->value;
    min = Heap;
    while (curH->sibling != nullptr)
    {
        curH = curH->sibling;
        if (curH->value < ans)
        {
            min = curH;
            ans = curH->value;
        }
    } //поиск минимума
    min->mark = 1;
    if (min->adoptee == nullptr && min->sibling == nullptr)
    {
        Heap = tree_extract_min(min);
    }
    else
    {
        if (min->adoptee == nullptr)
        {

            node<Key>* Q = min->sibling;
            Q->adoptee = nullptr;
            min->sibling = nullptr;
            min->adoptee = nullptr;
            node<Key>* R = tree_extract_min(min);
            Heap = heap_merge(R, Q);
        }// если слева от min нет деревьев
        else
        {
            if (min->sibling == nullptr)
            {
                node<Key>* Q = min->adoptee;
                Q->sibling = nullptr;
                min->sibling = nullptr;
                min->adoptee = nullptr;
                node<Key>* R = tree_extract_min(min);
                Heap = heap_merge(R, Heap);
            }
            else //если есть соседи и слева и справа от min
            {
                node<Key>* A = min->adoptee;
                node<Key>* B = min->sibling;
                min->sibling = nullptr;
                min->adoptee = nullptr;
                A->sibling = nullptr;
                B->adoptee = nullptr;
                node<Key>* R = tree_extract_min(min);
                Heap = heap_merge(Heap, R);
                Heap = heap_merge(Heap, B);
            }
        }

    }
    return ans;
}

template <class Key>
void binomial_heap<Key>::change(node<Key>* ptr, Key new_value)
{
    if ((ptr->point)->mark == 1)
        throw logic_error("element was deleted earlier");
    ptr = ptr->point;
    Key old_value = ptr->value;
    ptr->value = new_value;
    if (old_value > new_value)
        siftUp(ptr);
    else siftDown(ptr);
}

template <class Key>
void binomial_heap<Key>::erase(node<Key>* ptr)
{
    if ((ptr->point)->mark == 1)
        throw logic_error("element was deleted earlier");
    Key min = get_min() - 1;
    change(ptr, min);
    extract_min();
}

template <class Key>
void binomial_heap<Key>::siftUp(node<Key>* ptr)
{
    //std::cout << "r ";
    if (ptr->parent != nullptr)
    {
        if (ptr->value < (ptr->parent)->value)
        {
            _swap(ptr, ptr->parent);
            siftUp(ptr->parent);
        }
    }
}

template <class Key>
void binomial_heap<Key>::siftDown(node<Key>* ptr)
{
    //std::cout << "r ";
    if (ptr->child != nullptr)
    {
        node<Key>* ptrLeftSon = ptr->child;
        if (ptrLeftSon->sibling == nullptr)
        {
            if (ptr->value > ptrLeftSon->value)
                _swap(ptr, ptrLeftSon);
        }
        else
        {
            node<Key>* ptrRightSon = ptrLeftSon->sibling;
            node<Key>* curMin = ptrLeftSon;
            Key min = ptrLeftSon->value;
            while (ptrRightSon != nullptr)
            {
                if (ptrRightSon->value < min)
                {
                    min = ptrRightSon->value;
                    curMin = ptrRightSon;
                }
                ptrRightSon = ptrRightSon->sibling;
            }
            if (curMin->value < ptr->value)
            {
                _swap(curMin, ptr);
                siftDown(curMin);
            }
        }
    }
}

template <class Key>
void binomial_heap<Key>::merge(binomial_heap<Key>* otherHeap)
{
    node<Key>* node1 = otherHeap->Heap;
    Heap = heap_merge(Heap, node1);
    heap_size = heap_size + otherHeap->heap_size;
    otherHeap->heap_size = 0;
}

template <class Key>
void binomial_heap<Key>::_swap(node<Key>* ptr1, node<Key>* ptr2)
{
    Key tmp;
    tmp = ptr1->value;
    ptr1->value = ptr2->value;
    ptr2->value = tmp;
    node<Key>* ptrTmp;
    ptrTmp = ptr1->point;
    ptr2->point = ptrTmp;
    (ptr1->point)->point = ptr1;
    (ptr2->point)->point = ptr1;
}