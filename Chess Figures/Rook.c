// ��� va_arg
#include <stdarg.h>
#include <stdlib.h>
// ��� printf
#include <stdio.h>
#include "Rook.h"
// ��� struct Class
#include "new.h"
#define x(p) (((const struct Peace *)(p)) -> x)
#define y(p) (((const struct Peace *)(p)) -> y)
#include <stdbool.h>

// ���������� ������������ ��� ������ Point. ��������� ����������� ��������
// ������� ���������� � �� ����� ���������� ����� �������� (������ ��
// ���������), �� �������� ��� static.
static void* Rook_ctor(void* _self, va_list* app)
{
    struct Rook* self = ((const struct Class*)Peace)->ctor(_self, app);
    return self;
}
static void Rook_check(const void* _self,desk* desk)
{
    const struct Rook* self = _self;
    printf("Rook %d %d figure can kill:\n", x(self), y(self));
    int f1 = 1, f2 = 1, f3=1, f4=1;
    for (int i = 1; i < 8; i++)
    {
        if (i == 0)
        {
            continue;
        }
        if (f1)
        {
            f1 = checkfig(desk, x(self) + i, y(self));
        }
        if (f2)
        {
            f2 = checkfig(desk, x(self), y(self) + i);
        }
        if (f3)
        {
            f3 = checkfig(desk, x(self) - i, y(self));
        }
        if (f4)
        {
            f4 = checkfig(desk, x(self), y(self) - i);
        }
    }

}

// ���������� ������������ ������ draw ��� ������ Point. ����������� �����
// ����� �� ������������ ��� ������� ������, ������� ����������� � ��������
// ������ static.
static void Rook_draw(const void* _self)
{
    // �� �����, ��� ��, ��� ��� ��������, ��� ��������� �� Point
    const struct Rook* self = _self;
    printf("r");
    // ������ ���������
   // printf("\".\" at %d,%d\n", x(self), y(self));
}

// �������� ������ Point. ��� ���������� ����� ���������� � ���������� ������,
// �� ����� ���������� ����� (static)
static const struct Class _Rook = {
    // ������ ��������� ������ �������
    sizeof(struct Rook),
    // ��������� �� �������-�����������
    Rook_ctor,
    // ���������� �����������
    0,
    // ��������� �� ����������� ������� draw
    Rook_draw,
    Rook_check
};

// ���������� ����������� ��������� �� _Point, 

const void* Rook = &_Rook;