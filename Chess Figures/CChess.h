#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef
struct desk
{
	void* fields[8][8];
}desk;
//циклом пробежаться и сказать, что они все 0 при инициализации
// функция, которая засовывает фигуру в доску( у фигуры есть x, y)
extern bool checkfig(void* desk, int x, int y);