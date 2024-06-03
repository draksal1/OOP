
#pragma once
// Стандартная преамбула для заголовочного файла, гарантирующая его однократное
// включение
#ifndef __Bishop_h
#define __Bishop_h 
#include "Peace.h"
// Структура объекта класса Point
struct Bishop {
    const struct Peace _;
};


// Ссылка на указатель на описание класса Point, объявленный в point.c.
extern const void* Bishop;

#endif
