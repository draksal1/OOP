// ��� va_arg
#include <stdarg.h>
#include <stdlib.h>
// ��� printf
#include <stdio.h>
#include "Bishop.h"
// ��� struct Class
#include "new.h"
#include <stdbool.h>
#define x(p) (((const struct Peace *)(p)) -> x)
#define y(p) (((const struct Peace *)(p)) -> y)

// ���������� ������������ ��� ������ Point. ��������� ����������� ��������
// ������� ���������� � �� ����� ���������� ����� �������� (������ ��
// ���������), �� �������� ��� static.
static void* Bishop_ctor(void* _self, va_list* app)
{
    struct Bishop* self = ((const struct Class*)Peace)->ctor(_self, app);
    return self;
}
static void Bishop_check(const void* _self, desk* desk)
{
    const struct Bishop* self = _self;
    printf("Bishop %d %d figure can kill:\n", x(self), y(self));
    bool f1 = 1, f2 = 1, f3=1, f4=1;
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
           f2 =  checkfig(desk, x(self) + i, y(self) - i);
        }
        if (f3)
        {
            f3 = checkfig(desk, x(self) - i, y(self) - i);
        }
        if (f4)
        {
            f4 = checkfig(desk, x(self) - i, y(self) + i);
        }

    }

}

// ���������� ������������ ������ draw ��� ������ Point. ����������� �����
// ����� �� ������������ ��� ������� ������, ������� ����������� � ��������
// ������ static.
static void Bishop_draw(const void* _self)
{
    // �� �����, ��� ��, ��� ��� ��������, ��� ��������� �� Point
    const struct Bishop* self = _self;
    printf("b");
    // ������ ���������
   // printf("\".\" at %d,%d\n", x(self), y(self));
}


// �������� ������ Point. ��� ���������� ����� ���������� � ���������� ������,
// �� ����� ���������� ����� (static)
static const struct Class _Bishop = {
    // ������ ��������� ������ �������
    sizeof(struct Bishop),
    // ��������� �� �������-�����������
    Bishop_ctor,
    // ���������� �����������
    0,
    // ��������� �� ����������� ������� draw
    Bishop_draw,
    Bishop_check
};

// ���������� ����������� ��������� �� _Point, 

const void* Bishop = &_Bishop;