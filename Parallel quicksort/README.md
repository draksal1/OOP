<h1> Parallel quicksort </h1>

Problem statement

Implement a parallel version of the fast sorting algorithm. The partitioning scheme should be defined using SchemePolicy classes. The following signatures of pquicksort functions are fixed and cannot be changed.

```
//pquicksort.hpp
template <class RandomIt, class SchemePolicy>
void pquicksort(RandomIt first, RandomIt last, SchemePolicy&&& partition);

template <class RandomIt, class Compare, class SchemePolicy>
void pquicksort(RandomIt first, RandomIt last, Compare comp, SchemePolicy&&& partition);
```

The parallel version of the algorithm works better than the sequential implementation only if the range size exceeds a certain threshold, which may vary depending on compilation parameters, platform or hardware. Experiment with different thresholds and range sizes to see how the runtime changes. And set the threshold to the minimum number of elements for a multithreaded implementation.

https://oop.afti.ru/task_assignments/5459
