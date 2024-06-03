#pragma once
// Стандартная преамбула для заголовочного файла, гарантирующая его однократное
// включение
#ifndef __Rook_h
#define __Rook_h
#include "Peace.h"
// Структура объекта класса Point
struct Rook {
    const struct Peace _;
};


// Ссылка на указатель на описание класса Point, объявленный в point.c.
extern const void* Rook;

#endif

