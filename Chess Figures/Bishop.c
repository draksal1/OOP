// Для va_arg
#include <stdarg.h>
#include <stdlib.h>
// Для printf
#include <stdio.h>
#include "Bishop.h"
// Для struct Class
#include "new.h"
#include <stdbool.h>
#define x(p) (((const struct Peace *)(p)) -> x)
#define y(p) (((const struct Peace *)(p)) -> y)

// Реализация конструктора для класса Point. Поскольку конструктор является
// деталью реализации и не будет вызываться извне напрямую (только по
// указателю), он объявлен как static.
static void* Bishop_ctor(void* _self, va_list* app)
{
    struct Bishop* self = ((const struct Class*)Peace)->ctor(_self, app);
    return self;
}
static void Bishop_check(const void* _self, desk* desk)
{
    const struct Bishop* self = _self;
    printf("Bishop %d %d figure can kill:\n", x(self), y(self));
    bool f1 = 1, f2 = 1, f3=1, f4=1;
    for (int i = 1; i < 8; i++)
    {
        if (i == 0)
        {
            continue;
        }
        if (f1)
        {
            f1 = checkfig(desk, x(self) + i, y(self) + i);
        }
        if (f2)
        {
           f2 =  checkfig(desk, x(self) + i, y(self) - i);
        }
        if (f3)
        {
            f3 = checkfig(desk, x(self) - i, y(self) - i);
        }
        if (f4)
        {
            f4 = checkfig(desk, x(self) - i, y(self) + i);
        }

    }

}

// Реализация виртуального метода draw для класса Point. Виртуальный метод
// также не предназначен для прямого вызова, поэтому объявляется с ключевым
// словом static.
static void Bishop_draw(const void* _self)
{
    // Мы знаем, что то, что нам передали, это указатель на Point
    const struct Bishop* self = _self;
    printf("b");
    // Печать координат
   // printf("\".\" at %d,%d\n", x(self), y(self));
}


// Описание класса Point. Эта переменная будет находиться в глобальной памяти,
// но будет недоступна извне (static)
static const struct Class _Bishop = {
    // Размер структуры данных объекта
    sizeof(struct Bishop),
    // Указатель на функцию-конструктор
    Bishop_ctor,
    // Деструктор отсутствует
    0,
    // Указатель на виртуальную функцию draw
    Bishop_draw,
    Bishop_check
};

// Объявление глобального указателя на _Point, 

const void* Bishop = &_Bishop;