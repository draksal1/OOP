#pragma once
// ����������� ��������� ��� ������������� �����, ������������� ��� �����������
// ���������
#ifndef __point_h
#define __point_h
#include "new.h"
// ��������� ������� ������ Point
struct Peace {
    // ��������� �� �������� ��������� ������ (��. ����������� ������ �������
    // new)
    const void* Class;

    // ���������� �����
    int x, y;
};

// ������������� ����� ������. ������� ����� � 2D-������������.
void AddAtDesk(void* _self, desk* desk);

// ������ �� ��������� �� �������� ������ Point, ����������� � point.c.
extern const void* Peace;
#endif