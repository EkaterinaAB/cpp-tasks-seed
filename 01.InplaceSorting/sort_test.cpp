#include <gtest/gtest.h>

// А вот тут collvalue.h не надо, берите просто инты
#include "sorting.h"
#include <vector>      
#include <algorithm> 

// Но проверьте, что сортировки таки работают...

TEST(FooSuite, FooTest)
{
    EXPECT_EQ(0, 0);
}

TEST(SortingTest, EmptyArray) {
    std::vector<int> v;
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v.size(), 0);
}

// Тест для пузырьковой сортировки
TEST(SortingTest, BubbleSortBasic) {
    std::vector<int> v = {5, 1, 4, 2, 8};
    bubble_sort(v.begin(), v.end());
    
    std::vector<int> expected = {1, 2, 4, 5, 8};
    EXPECT_EQ(v, expected);
}





TEST(QuickSortTest, EmptyVector) {
    std::vector<int> vec = {};
    quick_sort(vec.begin(), vec.end());
    EXPECT_TRUE(vec.empty());
}

TEST(QuickSortTest, SingleElement) {
    std::vector<int> vec = {42};
    quick_sort(vec.begin(), vec.end());
    EXPECT_TRUE(is_sorted(vec.begin(), vec.end()));
    EXPECT_EQ(vec[0], 42);
}

TEST(QuickSortTest, TwoElementsSorted) {
    std::vector<int> vec = {1, 2};
    quick_sort(vec.begin(), vec.end());
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
}

TEST(QuickSortTest, TwoElementsUnsorted) {
    std::vector<int> vec = {2, 1};
    quick_sort(vec.begin(), vec.end());
    EXPECT_TRUE(is_sorted(vec.begin(), vec.end()));
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
}

TEST(QuickSortTest, SortedVector) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    quick_sort(vec.begin(), vec.end());
    EXPECT_EQ(vec, expected);
}

TEST(QuickSortTest, ReverseSortedVector) {
    std::vector<int> vec = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    quick_sort(vec.begin(), vec.end());
    EXPECT_EQ(vec, expected);
}

TEST(QuickSortTest, VectorWithDuplicates) {
    std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    quick_sort(vec.begin(), vec.end());
    std::vector<int> expected = {1, 1, 2, 3, 3, 4, 5, 5, 5, 6, 9};
    EXPECT_EQ(vec, expected);
}

TEST(QuickSortTest, VectorWithNegativeNumbers) {
    std::vector<int> vec = {-5, 3, -2, 0, -8, 7, -1, 2};
    quick_sort(vec.begin(), vec.end());
    std::vector<int> expected = {-8, -5, -2, -1, 0, 2, 3, 7};
    EXPECT_EQ(vec, expected);
}

TEST(QuickSortTest, VectorWithAllIdentical) {
    std::vector<int> vec = {5, 5, 5, 5, 5, 5};
    quick_sort(vec.begin(), vec.end());
    for (int val : vec) {
        EXPECT_EQ(val, 5);
    }
}


