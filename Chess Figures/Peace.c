// ��� va_arg
#include <stdarg.h>
#include <stdlib.h>
// ��� printf
#include <stdio.h>
#include "Peace.h"
// ��� struct Class
#include "new.h"

// ���������� ������� move
void AddAtDesk(void* _self,desk* desk)
{
    struct Peace* self = _self;
    desk->fields[self->x][self->y] = self;
}

// ���������� ������������ ��� ������ Peace. ��������� ����������� ��������
// ������� ���������� � �� ����� ���������� ����� �������� (������ ��
// ���������), �� �������� ��� static.
static void* Peace_ctor(void* _self, va_list* app)
{
    // � ���������� ������ ����� ��������� Peace
    struct Peace* self = _self;

    // ������ 2-� �������� new � ��������� � ���� x
    self->x = va_arg(*app, int);
    // ������ 3-� �������� new � ��������� � ���� y
    self->y = va_arg(*app, int);
    if (self->x < 0 || self->x >= 8 || self->y < 0 || self->y >= 8) {

        free(self);

        return NULL;

    }
    // ���������� ��������� �� ������
    return self;
}

// ���������� ������������ ������ draw ��� ������ Peace. ����������� �����
// ����� �� ������������ ��� ������� ������, ������� ����������� � ��������
// ������ static.
static void Peace_draw(const void* _self)
{
    // �� �����, ��� ��, ��� ��� ��������, ��� ��������� �� Peace
    const struct Peace* self = _self;

    // ������ ���������
    printf("P");
}

// �������� ������ Peace. ��� ���������� ����� ���������� � ���������� ������,
// �� ����� ���������� ����� (static)
static const struct Class _Peace = {
    // ������ ��������� ������ �������
    sizeof(struct Peace),
    // ��������� �� �������-�����������
    Peace_ctor,
    // ���������� �����������
    0,
    // ��������� �� ����������� ������� draw
    Peace_draw
};

// ���������� ����������� ��������� �� _Peace, ������� � ����� ������������
// ����� ����� Peace ��� ������������� (������� ���������� ��� ������� new).
const void* Peace = &_Peace;