#pragma once
#include <type_traits>
#include<iterator>
#include <random>
#include <algorithm>


namespace quicksort
{
    template <typename Iter>
    concept RandomAccessIterator = std::is_base_of_v<std::random_access_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>
        && requires(Iter i, Iter j, int n, int k)
    {
        i + n; i - n; n + 1; i[n];
        k += n; k -= n;
        i < j; i > j; i <= j; i >= j;
        ++i; --i; *i;
    };
    namespace impl
    {
        template <RandomAccessIterator It, class Compare>

        void QuickSort(It first, It last, Compare compare)
        {
            if (std::distance(first, last) <= 1)
            {
                return;
            }

            //if (std::distance(first, last) == 2)
            //{
            //    if (!compare(*first, *std::prev(last)))
            //    {
            //        std::iter_swap(first, std::prev(last));
            //    }
            //    return;
            //}

            auto pivot = *std::next(first, std::distance(first, last) / 2);

            It left = first;
            It right = std::prev(last);

            while (left <= right) {
                while (compare(*left, pivot) && left <= right) {
                    ++left;
                }

                while (compare(pivot, *right) && left <= right) {
                    --right;                    
                }

                if (left <= right) {
                    std::iter_swap(left, right);
                    ++left;
                    --right;
                }
            }

            QuickSort(first, right + 1, compare);
            QuickSort(left, last, compare);
        }

    }
    

    template <RandomAccessIterator It, class Compare = std::less<>>
    void sort(It first, It last, Compare comp = {})
    {
        if (first>last)
        {
            throw std::out_of_range("first>last");
        }
        impl::QuickSort(first, last, comp);
    }
}
