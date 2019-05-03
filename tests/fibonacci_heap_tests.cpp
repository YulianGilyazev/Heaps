#include <gtest/gtest.h>
#include <Fibonacci_heap>


class ClassDeclaration : public testing::Test {
public:
    ClassDeclaration() {}
};

TEST_F(ClassDeclaration, heap_basics)
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

TEST_F(ClassDeclaration, heap_time)
{
    fibonacci_heap<int> heap;
    for (int i = 0; i <= 1000000; i++)
    heap.insert(1000000 - i);
    for (int i = 0; i <= 1000000; i++)
    {
        ASSERT_EQ(i, heap.extract_min());
    }
}

TEST_F(ClassDeclaration, heap_random_time)
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


TEST_F(ClassDeclaration, heap_pointer_10000)
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

TEST_F(ClassDeclaration, heap_pointer)
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

TEST_F(ClassDeclaration, heap_merge)
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

TEST_F(ClassDeclaration, heap_merge_random)
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
