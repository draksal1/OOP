#pragma once
#include <type_traits>
#include<iterator>
#include <random>
#include <algorithm>
//очень желательно сделать, чтобы можно было сорт позвать без компоратора -- done
//тестируем все контейнеры с RAI, vector, deque, array, pointer -- done
// Для разных типов для дефолтного компаратора -- done
// Вектор с интами сортируем с comp=greater -- done
// Пишем свою функцию comp -- done
// Функтор - ?
//Пишем свой класс состоящий из чего нибудь с функцией сравнения -- done
// Пишем структуру, для которого переопределяем оператор меньше -- ?
//пишем структуры, переопределяем оператор больше и сортируем std::grade -- ?

// Делаем с концептами вместо enable_if
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

