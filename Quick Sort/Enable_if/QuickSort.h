#pragma once
#include <type_traits>
#include<iterator>
#include <random>
#include <algorithm>
//����� ���������� �������, ����� ����� ���� ���� ������� ��� ����������� -- done
//��������� ��� ���������� � RAI, vector, deque, array, pointer -- done
// ��� ������ ����� ��� ���������� ����������� -- done
// ������ � ������ ��������� � comp=greater -- done
// ����� ���� ������� comp -- done
// ������� - ?
//����� ���� ����� ��������� �� ���� ������ � �������� ��������� -- done
// ����� ���������, ��� �������� �������������� �������� ������ -- ?
//����� ���������, �������������� �������� ������ � ��������� std::grade -- ?

// ������ � ���������� ������ enable_if
namespace quicksort
{
    namespace impl
    {
        template <class RandomAccessIterator, class Compare>
        typename std::enable_if_t<std::is_base_of_v<std::random_access_iterator_tag, typename std::iterator_traits<RandomAccessIterator>::iterator_category>, void>
            QuickSort(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
        {
            auto size = std::distance(first, last);
            if (size <= 1)
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
            auto pivot = first[size / 2];
            //auto pivot = *std::next(first, std::distance(first, last) / 2);

            RandomAccessIterator left = first;
            RandomAccessIterator right = std::prev(last);

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
    template <class RandomAccessIterator, class Compare = std::less<>>
    typename std::enable_if_t<std::is_base_of_v<std::random_access_iterator_tag, typename std::iterator_traits<RandomAccessIterator>::iterator_category>, void>
        sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp = {})
    {
        if (first > last)
        {
            throw std::out_of_range("first>last");
        }

        impl::QuickSort(first, last, comp);
    }
}

