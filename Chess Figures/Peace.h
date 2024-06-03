#pragma once
// Стандартная преамбула для заголовочного файла, гарантирующая его однократное
// включение
#ifndef __point_h
#define __point_h
#include "new.h"
// Структура объекта класса Point
struct Peace {
    // Указатель на описание структуры класса (см. комментарии внутри функции
    // new)
    const void* Class;

    // Координаты точки
    int x, y;
};

// Невиртуальный метод класса. Смещает точку в 2D-пространстве.
void AddAtDesk(void* _self, desk* desk);

// Ссылка на указатель на описание класса Point, объявленный в point.c.
extern const void* Peace;
#endif