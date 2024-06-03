// Для va_arg
#include <stdarg.h>
#include <stdlib.h>
// Для printf
#include <stdio.h>
#include "Peace.h"
// Для struct Class
#include "new.h"

// Реализация функции move
void AddAtDesk(void* _self,desk* desk)
{
    struct Peace* self = _self;
    desk->fields[self->x][self->y] = self;
}

// Реализация конструктора для класса Peace. Поскольку конструктор является
// деталью реализации и не будет вызываться извне напрямую (только по
// указателю), он объявлен как static.
static void* Peace_ctor(void* _self, va_list* app)
{
    // В выделенную память ляжет структура Peace
    struct Peace* self = _self;

    // Достаём 2-й аргумент new и сохраняем в поле x
    self->x = va_arg(*app, int);
    // Достаём 3-й аргумент new и сохраняем в поле y
    self->y = va_arg(*app, int);
    if (self->x < 0 || self->x >= 8 || self->y < 0 || self->y >= 8) {

        free(self);

        return NULL;

    }
    // Возвращаем указатель на объект
    return self;
}

// Реализация виртуального метода draw для класса Peace. Виртуальный метод
// также не предназначен для прямого вызова, поэтому объявляется с ключевым
// словом static.
static void Peace_draw(const void* _self)
{
    // Мы знаем, что то, что нам передали, это указатель на Peace
    const struct Peace* self = _self;

    // Печать координат
    printf("P");
}

// Описание класса Peace. Эта переменная будет находиться в глобальной памяти,
// но будет недоступна извне (static)
static const struct Class _Peace = {
    // Размер структуры данных объекта
    sizeof(struct Peace),
    // Указатель на функцию-конструктор
    Peace_ctor,
    // Деструктор отсутствует
    0,
    // Указатель на виртуальную функцию draw
    Peace_draw
};

// Объявление глобального указателя на _Peace, который и будет представлять
// собой класс Peace для пользователей (служить аргументом для функции new).
const void* Peace = &_Peace;