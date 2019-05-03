#include <gtest/gtest.h>
#include "binary_heap.h"
#include "binomial_heap.h"
#include "fibonacci_heap.h"
#include "my_vector.h"


class ClassDeclaration : public testing::Test {
public:
    ClassDeclaration() {}
};

TEST_F(ClassDeclaration, binary_heap_basics)
{
    binary_heap<int> heap;
    ASSERT_EQ(1, heap.is_empty());
    ASSERT_ANY_THROW(heap.get_min());
    ASSERT_ANY_THROW(heap.extract_min());
    heap.insert(0);
    heap.insert(1);
    ASSERT_EQ(0, heap.get_min());
    ASSERT_EQ(0, heap.extract_min());
    ASSERT_EQ(1, heap.extract_min());
    heap.insert(5);
    ASSERT_EQ(0, heap.is_empty());
    heap.insert(2);
    heap.insert(3);
    heap.insert(4);
    ASSERT_EQ(2, heap.get_min());
    ASSERT_EQ(2, heap.extract_min());
    ASSERT_EQ(0, heap.is_empty());
    ASSERT_EQ(3, heap.extract_min());
    ASSERT_EQ(4, heap.extract_min());
    ASSERT_EQ(5, heap.extract_min());
    ASSERT_ANY_THROW(heap.extract_min());
}

TEST_F(ClassDeclaration, binary_heap_mass_constructor)
{
    int* arr = new int[5]{ 2, 3, 5, 1, 4 };
    binary_heap<int> heap(arr + 0, arr + 5);
    ASSERT_EQ(1, heap.get_min());
    ASSERT_EQ(1, heap.extract_min());
    ASSERT_EQ(0, heap.is_empty());
    ASSERT_EQ(2, heap.extract_min());
    heap.insert(-1);
    ASSERT_EQ(-1, heap.extract_min());
    ASSERT_EQ(3, heap.extract_min());
    ASSERT_EQ(4, heap.extract_min());
    ASSERT_EQ(5, heap.extract_min());
}

TEST_F(ClassDeclaration, binary_heap_pointer)
{
    int* arr = new int[5]{ 8, 3, 6, 1, 5 };
    binary_heap<int> heap(arr + 0, arr + 5);
    int* ptr0 = heap.insert(0);
    int* ptr5 = heap.insert(5);
    int* ptr1 = heap.insert(1);
    int* ptr2 = heap.insert(2);
    ASSERT_EQ(0, heap.extract_min());
    heap.change(ptr5, -1);
    ASSERT_EQ(-1, heap.extract_min());
    ASSERT_EQ(1, heap.extract_min());
    ASSERT_EQ(1, heap.extract_min());
    heap.change(ptr2, 4);
    ASSERT_EQ(3, heap.extract_min());
    ASSERT_EQ(4, heap.get_min());
    heap.change(ptr2, 7);
    ASSERT_EQ(5, heap.extract_min());
    heap.erase(ptr2);
    ASSERT_EQ(6, heap.extract_min());
    ASSERT_EQ(8, heap.extract_min());
}

TEST_F(ClassDeclaration, binary_heap_optimize)
{
    binary_heap<int> heap;
    heap.optimize(16, 4);
    heap.insert(3);
    heap.insert(10);
    heap.insert(-1);
    heap.insert(4);
    heap.insert(-3);
    ASSERT_EQ(-3, heap.extract_min());
    ASSERT_EQ(-1, heap.extract_min());
    heap.insert(8);
    heap.insert(2);
    heap.insert(16);
    heap.insert(1);
    heap.insert(6);
    heap.insert(9);
    heap.insert(11);
    heap.insert(9);
    heap.insert(8);
    heap.insert(3);
    ASSERT_EQ(1, heap.extract_min());
    heap.insert(5);
    heap.insert(3);
    heap.insert(23);
    ASSERT_EQ(2, heap.extract_min());
}

TEST_F(ClassDeclaration, binary_heap_load)
{
    binary_heap<int> heap;
    for (int i = 0; i <= 1000000; i++)
    heap.insert(1000000 - i);
    for (int i = 0; i <= 1000000; i++)
    {
        ASSERT_EQ(i, heap.extract_min());
    }
}

TEST_F(ClassDeclaration, binary_heap_random)
{
    binary_heap<int> heap;
    int arr[100000];
    for (int i = 0; i < 100000; ++i)
    {
        arr[i] = rand() % 1000000;
        heap.insert(arr[i]);
    }
    std::sort(arr, arr + 100000);
    for (int i = 0; i < 100000; ++i)
    {
        ASSERT_EQ(arr[i], heap.extract_min());
    }
}

TEST_F(ClassDeclaration, binary_heapheap_mass_constructor_load)
{
    int arr[100000];
    for (int i = 0; i < 100000; ++i)
    arr[i] = rand() % 100000;
    binary_heap<int> heap(arr + 0, arr + 100000);
    std::sort(arr + 0, arr + 100000);
    for (int i = 0; i < 100000; i++)
    ASSERT_EQ(arr[i], heap.extract_min());
}

TEST_F(ClassDeclaration, binary_heap_optimize)
{
    binary_heap<int> heap;
    heap.optimize(100000, 50);
    int arr[100000];
    for (int i = 0; i < 100000; ++i)
    {
        arr[i] = rand() % 1000000;
        heap.insert(arr[i]);
    }
    std::sort(arr, arr + 100000);

    for (int i = 0; i < 50; ++i)
    {
        ASSERT_EQ(arr[i], heap.extract_min());
    }
}

TEST_F(ClassDeclaration, bianry_heap_pointer_load)
{
    binary_heap<int> heap;
    int* T1 = heap.insert(331);
    for (int i = 0; i < 10000; ++i)
    heap.insert(i);
    for (int i = 0; i < 331; ++i)
    ASSERT_EQ(i, heap.extract_min());
    heap.change(T1, 200);
    ASSERT_EQ(200, heap.extract_min());
    ASSERT_EQ(331, heap.extract_min());
    ASSERT_EQ(332, heap.extract_min());
    int* T2 = heap.insert(400);
    for (int i = 333; i < 400; ++i)
    ASSERT_EQ(i, heap.extract_min());
    ASSERT_EQ(400, heap.get_min());
    heap.erase(T2);
    ASSERT_EQ(400, heap.extract_min());
    ASSERT_EQ(401, heap.extract_min());
}


TEST_F(ClassDeclaration, binary_heap_vector)
{
    my_vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    ASSERT_EQ(4, vec.size());
    ASSERT_EQ(3, vec[2]);
    vec.pop_back();
    vec.push_back(-1);
    ASSERT_EQ(-1, vec[vec.size()-1]);
    vec.pop_back();
    ASSERT_EQ(3, vec[2]);
    vec.pop_back();
    ASSERT_EQ(2, vec[1]);
    ASSERT_EQ(1, vec[0]);
}


TEST_F(ClassDeclaration, binomial_heap_basics)
{
    binomial_heap<int> heap;
    ASSERT_EQ(1, heap.is_empty());
    ASSERT_ANY_THROW(heap.get_min());
    ASSERT_ANY_THROW(heap.extract_min());
    heap.insert(0);
    heap.insert(1);
    ASSERT_EQ(0, heap.get_min());
    ASSERT_EQ(0, heap.extract_min());
    ASSERT_EQ(0, heap.is_empty());
    ASSERT_EQ(1, heap.extract_min());
    ASSERT_ANY_THROW(heap.get_min());
    ASSERT_ANY_THROW(heap.extract_min());
    heap.insert(5);
    ASSERT_EQ(5, heap.get_min());
    ASSERT_EQ(0, heap.is_empty());
    heap.insert(4);
    heap.insert(3);
    ASSERT_EQ(3, heap.get_min());
    heap.insert(2);
    ASSERT_EQ(2, heap.get_min());
    ASSERT_EQ(2, heap.extract_min());
    ASSERT_EQ(0, heap.is_empty());
    ASSERT_EQ(3, heap.extract_min());
    ASSERT_EQ(4, heap.get_min());
    ASSERT_EQ(4, heap.extract_min());
    ASSERT_EQ(5, heap.extract_min());
    ASSERT_ANY_THROW(heap.extract_min());
    ASSERT_ANY_THROW(heap.get_min());
    ASSERT_EQ(1, heap.is_empty());
}

TEST_F(ClassDeclaration, binomial_heap_load)
{
    binomial_heap<int> heap;
    int arr [100000];
    for (int i = 0; i < 100000; ++i)
    {
    arr[i] = rand() % 1000000;
    heap.insert(arr[i]);
    }
    std::sort(arr, arr + 100000);
    for (int i = 0; i < 100000; ++i)
    {
    ASSERT_EQ(arr[i], heap.extract_min());
    }
}

TEST_F(ClassDeclaration, binomial_heap_pointer)
{
    binomial_heap<int> heap;
    heap.insert(10);
    heap.insert(8);
    heap.insert(-1);
    ASSERT_EQ(-1, heap.get_min());
    node<int>* T1 = heap.insert(3);
    heap.insert(2);
    ASSERT_EQ(-1, heap.extract_min());
    ASSERT_EQ(2, heap.extract_min());
    heap.insert(4);
    heap.change(T1, 5);
    ASSERT_EQ(4, heap.extract_min());
    node<int>* T2 = heap.insert(-3);
    heap.insert(-5);
    ASSERT_EQ(-5, heap.extract_min());
    heap.change(T2, 6);
    ASSERT_EQ(5, heap.extract_min());
    ASSERT_EQ(6, heap.extract_min());
    heap.insert(2);
    node<int>* T3 = heap.insert(3);
    ASSERT_EQ(2, heap.extract_min());
    heap.erase(T3);
    ASSERT_ANY_THROW(heap.erase(T3));
    ASSERT_ANY_THROW(heap.change(T3, 0));
    ASSERT_EQ(8, heap.extract_min());
    node<int>* T4 = heap.insert(1);
    heap.insert(0);
    heap.insert(-3);
    heap.change(T4, -2);
    ASSERT_EQ(-3, heap.extract_min());
    ASSERT_EQ(-2, heap.extract_min());
    ASSERT_ANY_THROW(heap.erase(T4));
    ASSERT_ANY_THROW(heap.change(T4, 0));
    node<int>* T5 = heap.insert(2);
    heap.insert(1);
    heap.insert(-1);
    heap.erase(T5);
    ASSERT_EQ(-1, heap.extract_min());
    ASSERT_EQ(0, heap.extract_min());
    ASSERT_ANY_THROW(heap.change(T5, 0));
    ASSERT_ANY_THROW(heap.erase(T5));
    ASSERT_EQ(1, heap.extract_min());
    heap.insert(10);
    ASSERT_EQ(10, heap.get_min());
    node<int>* T6 = heap.insert(19);
    heap.insert(2);
    ASSERT_EQ(2, heap.get_min());
    heap.change(T6, 9);
    ASSERT_EQ(2, heap.extract_min());
    ASSERT_EQ(9, heap.get_min());
    heap.erase(T6);
    ASSERT_EQ(10, heap.extract_min());
    ASSERT_EQ(10, heap.extract_min());
    ASSERT_ANY_THROW(heap.get_min());
    ASSERT_ANY_THROW(heap.extract_min());
    node<int>* T7 = heap.insert(1);
    heap.insert(4);
    heap.insert(8);
    ASSERT_EQ(1, heap.get_min());
    heap.change(T7, 6);
    ASSERT_EQ(4, heap.extract_min());
    ASSERT_EQ(6, heap.extract_min());
    ASSERT_EQ(8, heap.extract_min());
    ASSERT_ANY_THROW(heap.get_min());
    ASSERT_ANY_THROW(heap.extract_min());
}

TEST_F(ClassDeclaration, binomial_heap_merge)
{
    binomial_heap<int> heap1;
    heap1.insert(1);
    heap1.insert(2);
    heap1.insert(5);
    heap1.insert(3);
    heap1.insert(13);
    heap1.insert(11);
    heap1.insert(11);
    binomial_heap<int> heap2;
    heap2.insert(7);
    heap2.insert(6);
    heap2.insert(3);
    heap2.insert(8);
    heap1.merge(&heap2);
    ASSERT_ANY_THROW(heap2.get_min());
    ASSERT_ANY_THROW(heap2.extract_min());
    ASSERT_EQ(1, heap1.extract_min());
    ASSERT_EQ(2, heap1.extract_min());
    ASSERT_EQ(3, heap1.extract_min());
    ASSERT_EQ(3, heap1.extract_min());
    ASSERT_EQ(5, heap1.extract_min());
    ASSERT_EQ(6, heap1.extract_min());
    ASSERT_EQ(7, heap1.extract_min());
    ASSERT_EQ(8, heap1.extract_min());
    ASSERT_EQ(11, heap1.extract_min());
    ASSERT_EQ(11, heap1.extract_min());
    ASSERT_EQ(13, heap1.extract_min());
    ASSERT_ANY_THROW(heap1.get_min());
    ASSERT_ANY_THROW(heap1.extract_min());
}

TEST_F(ClassDeclaration, fibonacci_heap_basics)
{
    fibonacci_heap<int> heap;
    ASSERT_ANY_THROW(heap.get_min());
    heap.insert(0);
    heap.insert(1);
    ASSERT_EQ(0, heap.get_min());
    ASSERT_EQ(0, heap.extract_min());
    ASSERT_EQ(1, heap.extract_min());
    ASSERT_ANY_THROW(heap.extract_min());
    heap.insert(5);
    ASSERT_EQ(5, heap.get_min());
    heap.insert(4);
    heap.insert(3);
    ASSERT_EQ(3, heap.get_min());
    heap.insert(2);
    ASSERT_EQ(2, heap.get_min());
    ASSERT_EQ(2, heap.extract_min());
    ASSERT_EQ(3, heap.extract_min());
    ASSERT_EQ(4, heap.get_min());
    ASSERT_EQ(4, heap.extract_min());
    ASSERT_EQ(5, heap.extract_min());
}

TEST_F(ClassDeclaration, fibonacci_heap_load)
{
    fibonacci_heap<int> heap;
    int arr[100000];
    for (int i = 0; i < 100000; ++i)
    {
        arr[i] = rand() % 10000000;
        heap.insert(arr[i]);
    }
    std::sort(arr, arr + 100000);
    for (int i = 0; i < 100000; ++i)
    {
        ASSERT_EQ(arr[i], heap.extract_min());
    }
}


TEST_F(ClassDeclaration, fibonacci_heap_pointer_load)
{
    fibonacci_heap<int> heap;
    fibonacci_heap<int>::pointer* T1 = heap.insert(331);
    for (int i = 0; i < 10000; ++i)
    heap.insert(i);
    for (int i = 0; i < 331; ++i)
    ASSERT_EQ(i, heap.extract_min());
    heap.decrease(T1, 200);
    ASSERT_EQ(200, heap.extract_min());
    ASSERT_EQ(331, heap.extract_min());
    ASSERT_EQ(332, heap.extract_min());
    fibonacci_heap<int>::pointer* T2 = heap.insert(400);
    for (int i = 333; i < 400; ++i)
    ASSERT_EQ(i, heap.extract_min());
    ASSERT_EQ(400, heap.get_min());
    heap.decrease(T2, 300);
    ASSERT_EQ(300, heap.extract_min());
    ASSERT_EQ(400, heap.extract_min());
    ASSERT_EQ(401, heap.extract_min());
    ASSERT_ANY_THROW(heap.decrease(T2, 0));
}

TEST_F(ClassDeclaration, fibonacci_heap_pointer)
{
    fibonacci_heap<int> heap;
    heap.insert(10);
    heap.insert(8);
    heap.insert(-1);
    ASSERT_EQ(-1, heap.get_min());
    fibonacci_heap<int>::pointer* T1 = heap.insert(3);
    heap.insert(2);
    ASSERT_EQ(-1, heap.extract_min());
    heap.decrease(T1, 1);
    ASSERT_EQ(1, heap.extract_min());
    fibonacci_heap<int>::pointer* T2 = heap.insert(5);
    heap.insert(3);
    heap.insert(5);
    heap.insert(4);
    heap.insert(1);
    ASSERT_EQ(1, heap.extract_min());
    ASSERT_EQ(2, heap.extract_min());
    heap.decrease(T2, 4);
    ASSERT_EQ(3, heap.extract_min());
    ASSERT_EQ(4, heap.extract_min());
    ASSERT_EQ(4, heap.extract_min());
    fibonacci_heap<int>::pointer* T3 = heap.insert(11);
    ASSERT_EQ(5, heap.extract_min());
    heap.decrease(T3, 9);
    ASSERT_EQ(8, heap.extract_min());
    ASSERT_EQ(9, heap.extract_min());
    ASSERT_EQ(10, heap.extract_min());
    ASSERT_ANY_THROW(heap.extract_min());
    heap.insert(6);
    T1 = heap.insert(8);
    T2 = heap.insert(2);
    T3 = heap.insert(4);
    heap.decrease(T1, 5);
    heap.decrease(T3, 2);
    ASSERT_EQ(2, heap.get_min());
    heap.decrease(T2, -1);
    ASSERT_EQ(-1, heap.extract_min());
    ASSERT_EQ(2, heap.extract_min());
    ASSERT_EQ(5, heap.extract_min());
    ASSERT_ANY_THROW(heap.decrease(T3, 1));
    ASSERT_EQ(6, heap.extract_min());
    ASSERT_ANY_THROW(heap.get_min());
}

TEST_F(ClassDeclaration, fibonacci_heap_merge)
{
    fibonacci_heap<int> heap1;
    fibonacci_heap<int> heap2;
    heap1.insert(1);
    heap1.insert(3);
    heap1.insert(0);
    heap1.insert(4);
    heap1.insert(6);
    heap2.insert(1);
    heap2.insert(2);
    heap2.insert(5);
    heap2.insert(7);
    ASSERT_EQ(0, heap1.extract_min());
    ASSERT_EQ(1, heap2.extract_min());
    heap1.merge(&heap2);
    ASSERT_EQ(1, heap1.extract_min());
    ASSERT_EQ(2, heap1.extract_min());
    ASSERT_EQ(3, heap1.extract_min());
    ASSERT_EQ(4, heap1.extract_min());
    ASSERT_EQ(5, heap1.extract_min());
    ASSERT_EQ(6, heap1.extract_min());
    ASSERT_EQ(7, heap1.extract_min());
    ASSERT_ANY_THROW(heap2.extract_min());
}

TEST_F(ClassDeclaration, heap_merge_load)
{
    fibonacci_heap<int> heap1;
    fibonacci_heap<int> heap2;
    int arr1[10000];
    for (int i = 0; i < 10000; ++i)
    {
        arr1[i] = rand() % 10000000;
        heap1.insert(arr1[i]);
    }
    std::sort(arr1, arr1 + 10000);

    int arr2[10000];
    for (int i = 0; i < 10000; ++i)
    {
        arr2[i] = rand() % 10000000;
        heap2.insert(arr2[i]);
    }
    std::sort(arr2, arr2 + 10000);
    int arr[20000];
    for (int i = 0; i < 10000; ++i)
    {
        arr[i] = arr1[i];
    }
    for (int i = 0; i < 10000; ++i)
    {
        arr[i + 10000] = arr2[i];
    }
    std::sort(arr, arr + 20000);
    heap1.merge(&heap2);
    for (int i = 0; i < 20000; ++i)
    {
        ASSERT_EQ(arr[i], heap1.extract_min());
    }
}
