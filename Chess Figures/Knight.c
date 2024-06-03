// Для va_arg
#include <stdarg.h>
#include <stdlib.h>
// Для printf
#include <stdio.h>
#include "Knight.h"
// Для struct Class
#include "new.h"

#define x(p) (((const struct Peace *)(p)) -> x)
#define y(p) (((const struct Peace *)(p)) -> y)

// Реализация конструктора для класса Point. Поскольку конструктор является
// деталью реализации и не будет вызываться извне напрямую (только по
// указателю), он объявлен как static.
static void* Knight_ctor(void* _self, va_list* app)
{
    struct Knight* self = ((const struct Class*)Peace)->ctor(_self, app);
    return self;
}
static void Knight_check(const void* _self,desk* desk)
{
    const struct Knight* self = _self;
    printf("Knight %d %d figure can kill:\n", x(self), y(self));
    int ArrayX[8] = { 2, 2, -2, -2, 1, 1, -1, -1 };
    int ArrayY[8] = { 1, -1, 1, -1, 2, -2, 2, -2 };
    for (int i = 0; i < 8; i++)
    {
        checkfig(desk, x(self) + ArrayX[i], y(self)+ArrayY[i]);
    }

}

// Реализация виртуального метода draw для класса Point. Виртуальный метод
// также не предназначен для прямого вызова, поэтому объявляется с ключевым
// словом static.
static void Knight_draw(const void* _self)
{
    // Мы знаем, что то, что нам передали, это указатель на Point
    const struct Knight* self = _self;
    printf("k");
    // Печать координат
   // printf("\".\" at %d,%d\n", x(self), y(self));
}
// Описание класса Point. Эта переменная будет находиться в глобальной памяти,
// но будет недоступна извне (static)
static const struct Class _Knight = {
    // Размер структуры данных объекта
    sizeof(struct Knight),
    // Указатель на функцию-конструктор
    Knight_ctor,
    // Деструктор отсутствует
    0,
    // Указатель на виртуальную функцию draw
    Knight_draw,
    Knight_check
};

// Объявление глобального указателя на _Point, который и будет представлять
// собой класс Point для пользователей (служить аргументом для функции new).
const void* Knight = &_Knight;