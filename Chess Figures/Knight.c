// ��� va_arg
#include <stdarg.h>
#include <stdlib.h>
// ��� printf
#include <stdio.h>
#include "Knight.h"
// ��� struct Class
#include "new.h"

#define x(p) (((const struct Peace *)(p)) -> x)
#define y(p) (((const struct Peace *)(p)) -> y)

// ���������� ������������ ��� ������ Point. ��������� ����������� ��������
// ������� ���������� � �� ����� ���������� ����� �������� (������ ��
// ���������), �� �������� ��� static.
static void* Knight_ctor(void* _self, va_list* app)
{
    struct Knight* self = ((const struct Class*)Peace)->ctor(_self, app);
    return self;
}
static void Knight_check(const void* _self,desk* desk)
{
    const struct Knight* self = _self;
    printf("Knight %d %d figure can kill:\n", x(self), y(self));
    int ArrayX[8] = { 2, 2, -2, -2, 1, 1, -1, -1 };
    int ArrayY[8] = { 1, -1, 1, -1, 2, -2, 2, -2 };
    for (int i = 0; i < 8; i++)
    {
        checkfig(desk, x(self) + ArrayX[i], y(self)+ArrayY[i]);
    }

}

// ���������� ������������ ������ draw ��� ������ Point. ����������� �����
// ����� �� ������������ ��� ������� ������, ������� ����������� � ��������
// ������ static.
static void Knight_draw(const void* _self)
{
    // �� �����, ��� ��, ��� ��� ��������, ��� ��������� �� Point
    const struct Knight* self = _self;
    printf("k");
    // ������ ���������
   // printf("\".\" at %d,%d\n", x(self), y(self));
}
// �������� ������ Point. ��� ���������� ����� ���������� � ���������� ������,
// �� ����� ���������� ����� (static)
static const struct Class _Knight = {
    // ������ ��������� ������ �������
    sizeof(struct Knight),
    // ��������� �� �������-�����������
    Knight_ctor,
    // ���������� �����������
    0,
    // ��������� �� ����������� ������� draw
    Knight_draw,
    Knight_check
};

// ���������� ����������� ��������� �� _Point, ������� � ����� ������������
// ����� ����� Point ��� ������������� (������� ���������� ��� ������� new).
const void* Knight = &_Knight;