#pragma once
// Стандартная преамбула для заголовочного файла, гарантирующая его однократное
// включение
#ifndef __Knight_h
#define __Knight_h
#include "Peace.h"
// Структура объекта класса Point
struct Knight {
    const struct Peace _;
};


// Ссылка на указатель на описание класса Point, объявленный в point.c.
extern const void* Knight;

#endif
