#pragma once
#include <algorithm>
#include <vector>
#include <future>

namespace parallel {
    namespace impl {
        template <class RandomIt, class Compare, class SchemePolicy>
        void pquicksort(RandomIt first, RandomIt last, Compare comp, const SchemePolicy& partition) {
            if (first >= last)
            {
                return;
            }

            std::vector<std::pair<RandomIt, RandomIt>> ranges;
            std::vector<std::future<void>> tasks;

            auto size = std::distance(first, last);
            auto ThreadsCount = partition.GetThreads(size);
            ThreadsCount = std::min(std::min(ThreadsCount, (int)std::thread::hardware_concurrency()),(int)size);
            int step = static_cast<int>(std::ceil(static_cast<double>(size) / static_cast<double>(ThreadsCount)));
            RandomIt temp = first;
            for (int i = 0; i < ThreadsCount; i++)
            {
                if (std::distance(temp, last) <= step)
                {
                    ranges.push_back({ temp, last });
                    break;
                }
                else {
                    RandomIt SecondPoint = std::next(temp, step - 1);
                    ranges.push_back({ temp, SecondPoint });
                    temp = SecondPoint;
                }
            }
            for (auto& it : ranges) {
                tasks.push_back(std::async(std::launch::async, [=] {std::sort(it.first, it.second, comp); }));
            }

            for (auto& task : tasks) {
                task.wait();
            }

            for (auto it = ++ranges.begin(); it < ranges.end(); it++) {
                auto it2 = it - 1;
                std::inplace_merge(first, it2->second, it->second, comp);
            }
        }
    }

    class DefaultPolicy {
    public:
        int GetThreads(ptrdiff_t size) const {
            if (size < 100) {
                return 1;
            }
            else if(size < 500) {
                return 2;
            }
            else if (size < 2000) {
                return 3;
            }
            else if (size < 10000) {
                return 4;
            }
            else if (size < 50000) {
                return 6;
            }
            else if (size < 500000) {
                return 7;
            }
            else{
                return 8;
            }
        }
    };
    template <typename Iter>
    concept RandomAccessIterator = std::is_base_of_v<std::random_access_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>
        && requires(Iter i, Iter j, int n, int k)
    {
        i + n; i - n; n + 1; i[n];
        k += n; k -= n;
        i < j; i > j; i <= j; i >= j;
        ++i; --i; *i;
    };
    template <RandomAccessIterator RandomIt, class SchemePolicy = DefaultPolicy>
    void sort1(RandomIt first, RandomIt last, const SchemePolicy& partition = {}) {
        impl::pquicksort(first, last, std::less<>(), partition);
    }

    template <RandomAccessIterator RandomIt, class Compare, class SchemePolicy = DefaultPolicy>
    void sort2(RandomIt first, RandomIt last, Compare comp, const SchemePolicy& partition = {}) {
        impl::pquicksort(first, last, comp, partition);
    }
}