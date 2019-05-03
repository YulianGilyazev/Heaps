#include <gtest/gtest.h>
#include <Binomial_heap>


class ClassDeclaration : public testing::Test {
public:
    ClassDeclaration() {}
};

TEST_F(ClassDeclaration, heap_basics)
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

TEST_F(ClassDeclaration, heap_time)
{
    binomial_heap<int> heap;
    for (int i = 0; i <= 1000000; i++)
    heap.insert(1000000 - i);
    for (int i = 0; i <= 1000000; i++)
    {
        ASSERT_EQ(i, heap.extract_min());
    }
}

TEST_F(ClassDeclaration, heap_random)
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


TEST_F(ClassDeclaration, heap_pointer)
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

TEST_F(ClassDeclaration, heap_merge)
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

TEST_F(ClassDeclaration, heap_qwert)
{
    for (int i = 0; i < 30000000; ++i)
    ASSERT_EQ(i, i);
}
