// Для va_arg
#include <stdarg.h>
#include <stdlib.h>
// Для printf
#include <stdio.h>
#include "King.h"
// Для struct Class
#include "new.h"
#define x(p) (((const struct Peace *)(p)) -> x)
#define y(p) (((const struct Peace *)(p)) -> y)

// Реализация конструктора для класса Point. Поскольку конструктор является
// деталью реализации и не будет вызываться извне напрямую (только по
// указателю), он объявлен как static.
static void* King_ctor(void *_self, va_list* app)
{
    struct King* self = ((const struct Class*)Peace)->ctor(_self, app);
    return self;
}
static void King_check(const void* _self, desk* desk){
    const struct King* self = _self;
    printf("King %d %d figure can kill:\n", x(self), y(self));
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {   
            if (j == 0 && i == 0)
            {
                continue;
            }
            checkfig(desk, x(self) + i, y(self) + j);
        }
    }
}

// Реализация виртуального метода draw для класса Point. Виртуальный метод
// также не предназначен для прямого вызова, поэтому объявляется с ключевым
// словом static.
static void King_draw(const void* _self)
{
    // Мы знаем, что то, что нам передали, это указатель на Point
    const struct King* self = _self;
    printf("K");
    // Печать координат
}

// Описание класса Point. Эта переменная будет находиться в глобальной памяти,
// но будет недоступна извне (static)
static const struct Class _King = {
    // Размер структуры данных объекта
    sizeof(struct King),
    // Указатель на функцию-конструктор
    King_ctor,
    // Деструктор отсутствует
    0,
    // Указатель на виртуальную функцию draw
    King_draw,
    King_check,
};

// Объявление глобального указателя на _Point, который и будет представлять
// собой класс Point для пользователей (служить аргументом для функции new).
const void* King = &_King;