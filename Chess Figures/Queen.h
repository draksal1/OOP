#pragma once
// Стандартная преамбула для заголовочного файла, гарантирующая его однократное
// включение
#ifndef __Queen_h
#define __Queen_h 
#include "Peace.h"
// Структура объекта класса Point
struct Queen {
    const struct Peace _;
};


// Ссылка на указатель на описание класса Point, объявленный в point.c.
extern const void* Queen;

#endif