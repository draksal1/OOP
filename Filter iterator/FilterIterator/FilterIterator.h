#pragma once
#include <iterator>
#include <type_traits>
#include <concepts>
#include <stdexcept>
#include <functional>





namespace iterators
{


    template <class Iterator >
    concept Iterator_valide = requires(Iterator it)
    {
        ++it;
        it++;
        *it;
        it == it;
        it != it;
    };


    template <Iterator_valide Iterator>
    class filter_range final

    {

    public:

        using value_type = typename std::iterator_traits<Iterator>::value_type;

        using Predicate = std::function<bool(const value_type&)>;



    private:

        Iterator first_;

        Iterator last_;

        Predicate predicate_;

        inline static int64_t s_id{}; // статическая, общая для всех экземпляров

        int64_t id{ ++s_id }; // увеличиваем общий id и инициализируем id экземпляра
        class filter_iterator final
        {
        public:
            using value_type = typename std::iterator_traits<Iterator>::value_type;
            using reference = typename std::iterator_traits<Iterator>::reference;
            using pointer = typename std::iterator_traits<Iterator>::pointer;
            using difference_type = typename std::iterator_traits<Iterator>::difference_type;
            using iterator_category = typename std::forward_iterator_tag;

            filter_iterator(Iterator begin_, Iterator end_, Predicate predicate_, int64_t id_) : id{ id_ }
            {
                iterator_end = end_;
                m_predicate = predicate_;
                iterator_begin = next_suitable(begin_);
            }

            reference operator*() const
            {
                if (iterator_begin == iterator_end)
                {
                    throw std::out_of_range("Trying to see end()");
                }
                return *iterator_begin;
            }

            filter_iterator& operator++()
            {
                if (iterator_begin != iterator_end)
                {
                    ++iterator_begin;
                    iterator_begin = next_suitable(iterator_begin);
                    return *this;

                }
                throw std::out_of_range("No way");
            }

            filter_iterator operator++(int)
            {
                auto a = *this;
                ++(*this);
                return a;
            }

            bool operator==(const filter_iterator& other) const noexcept

            {

                return id == other.id && iterator_begin == other.iterator_begin;

            }

            bool operator!=(const filter_iterator& other) const noexcept
            {
                return !(*this == other);
            }

        private:
            Iterator next_suitable(const Iterator& begin) const
            {
                for (auto iterator = begin; iterator != iterator_end; ++iterator)
                {
                    if (m_predicate(*iterator))
                    {
                        return iterator;
                    }
                }
                return iterator_end;
            }

            Predicate m_predicate;
            Iterator iterator_begin;
            Iterator iterator_end;
            int64_t id{};
        };

    public:
        using iterator = filter_iterator;
        explicit filter_range(const Iterator first, const Iterator last, Predicate predicate) : first_(first), last_(last), predicate_(predicate) {}
        iterator begin() noexcept
        {
            return filter_iterator(first_, last_, predicate_, id);
        }

        iterator end() noexcept
        {
            return filter_iterator(last_, last_, predicate_, id);
        }
    };
}

