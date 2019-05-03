#include <gtest/gtest.h>
#include <Binary_heap>


class ClassDeclaration : public testing::Test {
public:
    ClassDeclaration() {}
};

TEST_F(ClassDeclaration, heap_basics)
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

TEST_F(ClassDeclaration, heap_mass_constructor)
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

TEST_F(ClassDeclaration, pointer)
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

TEST_F(ClassDeclaration, optimize)
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

TEST_F(ClassDeclaration, heap_time)
{
    binary_heap<int> heap;
    for (int i = 0; i <= 1000000; i++)
    heap.insert(1000000 - i);
    for (int i = 0; i <= 1000000; i++)
    {
        ASSERT_EQ(i, heap.extract_min());
    }
}

TEST_F(ClassDeclaration, heap_random)
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

TEST_F(ClassDeclaration, heap_mass_constructor_time)
{
    int arr[100000];
    for (int i = 0; i < 100000; ++i)
    arr[i] = i;
    binary_heap<int> heap(arr + 0, arr + 100000);
    for (int i = 0; i < 100000; ++i)
    {
        ASSERT_EQ(i, heap.extract_min());
    }
}

TEST_F(ClassDeclaration, heap_mass_constructor_time_random)
{
    int arr[100000];
    for (int i = 0; i < 100000; ++i)
    arr[i] = rand() % 100000;
    binary_heap<int> heap(arr + 0, arr + 100000);
    std::sort(arr + 0, arr + 100000);
    for (int i = 0; i < 100000; i++)
    ASSERT_EQ(arr[i], heap.extract_min());
}

TEST_F(ClassDeclaration, heap_optimize_time)
{
    binary_heap<int> heap;
    heap.optimize(1000000, 100);
    for (int i = 0; i < 1000000; i++)
    heap.insert(1000000 - i);
    for (int i = 1; i <= 100; i++)
    ASSERT_EQ(i, heap.extract_min());
}

TEST_F(ClassDeclaration, heap_optimize_random)
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

TEST_F(ClassDeclaration, heap_pointer_10000)
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

TEST_F(ClassDeclaration, heap_exceptions)
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
    ASSERT_ANY_THROW(heap.optimize(1000, 3));
    ASSERT_EQ(4, heap.extract_min());
    ASSERT_EQ(5, heap.extract_min());
    ASSERT_ANY_THROW(heap.extract_min());
    ASSERT_ANY_THROW(heap.get_min());
    heap.insert(1);
    ASSERT_EQ(1, heap.extract_min());
    ASSERT_ANY_THROW(heap.extract_min());
    int * t = heap.insert(1);
    ASSERT_EQ(1, heap.extract_min());
}

TEST_F(ClassDeclaration, heap_vector)
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