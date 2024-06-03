// ��� va_arg
#include <stdarg.h>
#include <stdlib.h>
// ��� printf
#include <stdio.h>
#include "King.h"
// ��� struct Class
#include "new.h"
#define x(p) (((const struct Peace *)(p)) -> x)
#define y(p) (((const struct Peace *)(p)) -> y)

// ���������� ������������ ��� ������ Point. ��������� ����������� ��������
// ������� ���������� � �� ����� ���������� ����� �������� (������ ��
// ���������), �� �������� ��� static.
static void* King_ctor(void *_self, va_list* app)
{
    struct King* self = ((const struct Class*)Peace)->ctor(_self, app);
    return self;
}
static void King_check(const void* _self, desk* desk){
    const struct King* self = _self;
    printf("King %d %d figure can kill:\n", x(self), y(self));
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {   
            if (j == 0 && i == 0)
            {
                continue;
            }
            checkfig(desk, x(self) + i, y(self) + j);
        }
    }
}

// ���������� ������������ ������ draw ��� ������ Point. ����������� �����
// ����� �� ������������ ��� ������� ������, ������� ����������� � ��������
// ������ static.
static void King_draw(const void* _self)
{
    // �� �����, ��� ��, ��� ��� ��������, ��� ��������� �� Point
    const struct King* self = _self;
    printf("K");
    // ������ ���������
}

// �������� ������ Point. ��� ���������� ����� ���������� � ���������� ������,
// �� ����� ���������� ����� (static)
static const struct Class _King = {
    // ������ ��������� ������ �������
    sizeof(struct King),
    // ��������� �� �������-�����������
    King_ctor,
    // ���������� �����������
    0,
    // ��������� �� ����������� ������� draw
    King_draw,
    King_check,
};

// ���������� ����������� ��������� �� _Point, ������� � ����� ������������
// ����� ����� Point ��� ������������� (������� ���������� ��� ������� new).
const void* King = &_King;