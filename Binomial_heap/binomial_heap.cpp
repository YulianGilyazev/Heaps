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
binomial_node<Key>* binomial_heap<Key>::tree_extract_min(binomial_node<Key>* min)
{
    if (min->degree == 0)
        return nullptr;
    if (min->degree == 1)
    {
        (min->child)->parent == nullptr;
        return min->child;
    }
    binomial_node<Key>* curH = nullptr;
    binomial_node<Key>* R = min->child;
    binomial_node<Key>* Q = nullptr;
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
binomial_node<Key>* binomial_heap<Key>::tree_merge(binomial_node<Key>* root1, binomial_node<Key>* root2)
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
        binomial_node<Key>* curNode1 = root1->child;
        binomial_node<Key>* curNode2 = root2;
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
binomial_node<Key>* binomial_heap<Key>::heap_merge(binomial_node<Key>* heap1, binomial_node<Key>* heap2)
{
    if (heap1 == nullptr)
    {
        return heap2;
    }
    if (heap2 == nullptr)
    {
        return heap1;
    }
    binomial_node<Key> *curHeap1;
    binomial_node<Key> *curHeap2;
    curHeap1 = heap1;
    curHeap2 = heap2;
    binomial_node<Key>* H = nullptr;
    binomial_node<Key>* curH = nullptr;
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
            binomial_node<Key>* L = (curH->sibling)->sibling;
            binomial_node<Key>* Q = curH->adoptee;
            binomial_node<Key>* R = tree_merge(curH, curH->sibling);
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
    binomial_node<Key>* curH = Heap;
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
binomial_node<Key>* binomial_heap<Key>::insert(Key key)
{
    ++heap_size;
    binomial_node<Key>* K = new binomial_node<Key>;
    K->value = key;
    K->sibling = nullptr;
    K->adoptee = nullptr;
    K->degree = 0;
    K->parent = nullptr;
    K->child = nullptr;
    K->mark = 0;
    binomial_node<Key>* a = new binomial_node<Key>;
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
    binomial_node<Key>* min;
    Key ans;
    binomial_node<Key>* curH = Heap;
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

            binomial_node<Key>* Q = min->sibling;
            Q->adoptee = nullptr;
            min->sibling = nullptr;
            min->adoptee = nullptr;
            binomial_node<Key>* R = tree_extract_min(min);
            Heap = heap_merge(R, Q);
        }// если слева от min нет деревьев
        else
        {
            if (min->sibling == nullptr)
            {
                binomial_node<Key>* Q = min->adoptee;
                Q->sibling = nullptr;
                min->sibling = nullptr;
                min->adoptee = nullptr;
                binomial_node<Key>* R = tree_extract_min(min);
                Heap = heap_merge(R, Heap);
            }
            else //если есть соседи и слева и справа от min
            {
                binomial_node<Key>* A = min->adoptee;
                binomial_node<Key>* B = min->sibling;
                min->sibling = nullptr;
                min->adoptee = nullptr;
                A->sibling = nullptr;
                B->adoptee = nullptr;
                binomial_node<Key>* R = tree_extract_min(min);
                Heap = heap_merge(Heap, R);
                Heap = heap_merge(Heap, B);
            }
        }

    }
    return ans;
}

template <class Key>
void binomial_heap<Key>::change(binomial_node<Key>* ptr, Key new_value)
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
void binomial_heap<Key>::erase(binomial_node<Key>* ptr)
{
    if ((ptr->point)->mark == 1)
        throw logic_error("element was deleted earlier");
    Key min = get_min() - 1;
    change(ptr, min);
    extract_min();
}

template <class Key>
void binomial_heap<Key>::siftUp(binomial_node<Key>* ptr)
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
void binomial_heap<Key>::siftDown(binomial_node<Key>* ptr)
{
    //std::cout << "r ";
    if (ptr->child != nullptr)
    {
        binomial_node<Key>* ptrLeftSon = ptr->child;
        if (ptrLeftSon->sibling == nullptr)
        {
            if (ptr->value > ptrLeftSon->value)
                _swap(ptr, ptrLeftSon);
        }
        else
        {
            binomial_node<Key>* ptrRightSon = ptrLeftSon->sibling;
            binomial_node<Key>* curMin = ptrLeftSon;
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
    binomial_node<Key>* node1 = otherHeap->Heap;
    Heap = heap_merge(Heap, node1);
    heap_size = heap_size + otherHeap->heap_size;
    otherHeap->heap_size = 0;
}

template <class Key>
void binomial_heap<Key>::_swap(binomial_node<Key>* ptr1, binomial_node<Key>* ptr2)
{
    Key tmp;
    tmp = ptr1->value;
    ptr1->value = ptr2->value;
    ptr2->value = tmp;
    binomial_node<Key>* ptrTmp;
    ptrTmp = ptr1->point;
    ptr2->point = ptrTmp;
    (ptr1->point)->point = ptr1;
    (ptr2->point)->point = ptr1;
}
