#ifndef SORTING_H
#define SORTING_H

// Header-only

// Для swap
#include "collvalue.h"
#include <algorithm> 
#include <iterator> 

// ----------------------------- Пузырёк (например) --------------------------------------
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{

    for (Iterator i = begin; i != end; ++i) {
        Iterator j = begin;

        for (Iterator j = i+1; j != end; ++j) {
            if (*j > *std::next(j)) {
                std::iter_swap(j, std::next(j));
            }
            ++j;
        }
    }
}

template <typename Iterator>
Iterator partition(Iterator begin, Iterator end) {

    Iterator pivot = (begin + end) / 2;
    auto pivot_value = *pivot;
    
    Iterator i = begin;
    Iterator j = std::prev(end); 
    
    while (true) {
        while (*i < pivot_value) {
            ++i;
        }
        
        while (*j > pivot_value) {
            --j;
        }
        
        if (std::distance(i, j) <= 0) {
            break;
        }
        
        std::iter_swap(i, j);
        ++i;
        --j;
    }
    return j;
}
// --------------------------- QuickSort (например) ---------------------------------------
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    if (end - begin <= 1) return;

    Iterator pivot = partition(begin, end);
    
    quick_sort(begin, pivot);
    quick_sort(std::next(pivot), end);
}

#endif // SORTING_H
