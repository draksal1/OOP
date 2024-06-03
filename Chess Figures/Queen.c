// ��� va_arg
#include <stdarg.h>
#include <stdlib.h>
// ��� printf
#include <stdio.h>
#include "Queen.h"
// ��� struct Class
#include "new.h"
#include <stdbool.h>
#define x(p) (((const struct Peace *)(p)) -> x)
#define y(p) (((const struct Peace *)(p)) -> y)

// ���������� ������������ ��� ������ Point. ��������� ����������� ��������
// ������� ���������� � �� ����� ���������� ����� �������� (������ ��
// ���������), �� �������� ��� static.
static void* Queen_ctor(void* _self, va_list* app)
{
    struct Queen* self = ((const struct Class*)Peace)->ctor(_self, app);
    return self;
}
static void Queen_check(const void* _self,desk* desk)
{
    const struct Queen* self = _self;
    printf("Queen %d %d figure can kill:\n", x(self), y(self));
    bool f1=1, f2=1, f3=1, f4=1, f5 = 1, f6 = 1, f7 = 1, f8 = 1;
    for (int i = 1; i < 8; i++)
    {
        if (i == 0)
        {
            continue;
        }
        if (f1)
        {
            f1 = checkfig(desk, x(self) + i, y(self) + i);
        }
        if (f2)
        {
            f2 = checkfig(desk, x(self) + i, y(self) - i);
        }
        if (f3)
        {
            f3 = checkfig(desk, x(self) + i, y(self));
        }
        if (f4)
        {
            f4 = checkfig(desk, x(self), y(self) + i);
        }
        if (f5)
        {
            f5 = checkfig(desk, x(self) - i, y(self) - i);
        }
        if (f6)
        {
            f6= checkfig(desk, x(self) - i, y(self) + i);
        }
        if (f7)
        {
            f7 = checkfig(desk, x(self) - i, y(self));
        }
        if (f8)
        {
            f8 = checkfig(desk, x(self), y(self) - i);
        }

    }

}

// ���������� ������������ ������ draw ��� ������ Point. ����������� �����
// ����� �� ������������ ��� ������� ������, ������� ����������� � ��������
// ������ static.
static void Queen_draw(const void* _self)
{
    // �� �����, ��� ��, ��� ��� ��������, ��� ��������� �� Point
    const struct Queen* self = _self;
    printf("Q");
    // ������ ���������
   // printf("\".\" at %d,%d\n", x(self), y(self));
}

// �������� ������ Point. ��� ���������� ����� ���������� � ���������� ������,
// �� ����� ���������� ����� (static)
static const struct Class _Queen = {
    // ������ ��������� ������ �������
    sizeof(struct Queen),
    // ��������� �� �������-�����������
    Queen_ctor,
    // ���������� �����������
    0,
    // ��������� �� ����������� ������� draw
    Queen_draw,
    Queen_check
};

// ���������� ����������� ��������� �� _Point, ������� � ����� ������������
// ����� ����� Point ��� ������������� (������� ���������� ��� ������� new).
const void* Queen = &_Queen;