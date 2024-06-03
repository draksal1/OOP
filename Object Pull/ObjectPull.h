#include <stdexcept>
#include <vector>
#include <cstdint>
#include <memory>
#include <type_traits>

template <typename T>
concept NoThrowDestructor = std::is_nothrow_destructible<T>::value;

template <NoThrowDestructor T>
class ObjectPool {
private:
    std::vector<uint8_t> rawMemory;
    std::vector<bool> allocated;

public:
    // Конструктор: выделяет память под size объектов
    ObjectPool(size_t size) : rawMemory(sizeof(T)* size), allocated(size, false) {}

    ~ObjectPool() {
        for (size_t i = 0; i < allocated.size(); ++i) {
            if (allocated[i]) {
                // Вызываем деструктор для занятых объектов
                T* obj = reinterpret_cast<T*>(&rawMemory[i * sizeof(T)]);
                obj->~T();
            }
        }
    }
    int GetAllocatedCount()
    {
        int result = 0;
        for (auto it = allocated.begin(); it < allocated.end(); ++it)
        {
            if (*it)
            {
                result++;
            }
        }
        return result;
    }
    // Аллокация объекта из пула
    template <typename... Args, typename = std::enable_if_t<std::is_constructible_v<T, Args...>>>
    T& alloc(Args&&... args) {
        for (size_t i = 0; i < allocated.size(); ++i) {
            if (!allocated[i]) {
                T* obj = new (&rawMemory[i * sizeof(T)]) T{std::forward<Args>(args)...};
                allocated[i] = true;
                return *obj;
            }
        }
        throw std::out_of_range("No available objects in the pool.");
    }

    // Освобождение объекта и его частичная деинициализация
    void free(T& obj) {
        // Находим соответствующий кусок памяти в хранилище
        auto index = (reinterpret_cast<uint8_t*>(&obj) - rawMemory.data())/sizeof(T);
        
        if (index < allocated.size() && allocated[index] && index>=0) {
            // Вызываем деструктор объекта
            allocated[index] = false;
            obj.~T();
        }
        else {
            throw std::invalid_argument("Object does not belong to the pool.");
        }
    }
};
