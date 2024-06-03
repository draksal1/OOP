// Для va_arg
#include <stdarg.h>
#include <stdlib.h>
// Для printf
#include <stdio.h>
#include "Queen.h"
// Для struct Class
#include "new.h"
#include <stdbool.h>
#define x(p) (((const struct Peace *)(p)) -> x)
#define y(p) (((const struct Peace *)(p)) -> y)

// Реализация конструктора для класса Point. Поскольку конструктор является
// деталью реализации и не будет вызываться извне напрямую (только по
// указателю), он объявлен как static.
static void* Queen_ctor(void* _self, va_list* app)
{
    struct Queen* self = ((const struct Class*)Peace)->ctor(_self, app);
    return self;
}
static void Queen_check(const void* _self,desk* desk)
{
    const struct Queen* self = _self;
    printf("Queen %d %d figure can kill:\n", x(self), y(self));
    bool f1=1, f2=1, f3=1, f4=1, f5 = 1, f6 = 1, f7 = 1, f8 = 1;
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
            f2 = checkfig(desk, x(self) + i, y(self) - i);
        }
        if (f3)
        {
            f3 = checkfig(desk, x(self) + i, y(self));
        }
        if (f4)
        {
            f4 = checkfig(desk, x(self), y(self) + i);
        }
        if (f5)
        {
            f5 = checkfig(desk, x(self) - i, y(self) - i);
        }
        if (f6)
        {
            f6= checkfig(desk, x(self) - i, y(self) + i);
        }
        if (f7)
        {
            f7 = checkfig(desk, x(self) - i, y(self));
        }
        if (f8)
        {
            f8 = checkfig(desk, x(self), y(self) - i);
        }

    }

}

// Реализация виртуального метода draw для класса Point. Виртуальный метод
// также не предназначен для прямого вызова, поэтому объявляется с ключевым
// словом static.
static void Queen_draw(const void* _self)
{
    // Мы знаем, что то, что нам передали, это указатель на Point
    const struct Queen* self = _self;
    printf("Q");
    // Печать координат
   // printf("\".\" at %d,%d\n", x(self), y(self));
}

// Описание класса Point. Эта переменная будет находиться в глобальной памяти,
// но будет недоступна извне (static)
static const struct Class _Queen = {
    // Размер структуры данных объекта
    sizeof(struct Queen),
    // Указатель на функцию-конструктор
    Queen_ctor,
    // Деструктор отсутствует
    0,
    // Указатель на виртуальную функцию draw
    Queen_draw,
    Queen_check
};

// Объявление глобального указателя на _Point, который и будет представлять
// собой класс Point для пользователей (служить аргументом для функции new).
const void* Queen = &_Queen;