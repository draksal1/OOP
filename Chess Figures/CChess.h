#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef
struct desk
{
	void* fields[8][8];
}desk;
//������ ����������� � �������, ��� ��� ��� 0 ��� �������������
// �������, ������� ���������� ������ � �����( � ������ ���� x, y)
extern bool checkfig(void* desk, int x, int y);