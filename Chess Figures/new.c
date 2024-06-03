// ��� calloc � free
#include <stdlib.h>

// ��� assert.h
#include <assert.h>
#include "new.h"

// ���������� ������� new
void* new(const void* _class, ...)
{
    // ���������� ��� ����������� ���������. ���� �� � �������� ��� void *
    // (� ����� �������� ������ � ������), ��-�� �����, ��� ��� struct Class *.
    const struct Class* class = _class;

// �������� ������. ����������� ������� calloc ������ ������������ ���
// �������� ��������. Ÿ ������ �������� � ������ �������, ������ � ������
// ������ �������. ����� ��������� ���������������� ���������� ������
// ��� �������� ��� ������ � ���������� ���������.
void* p = calloc(1, class->size);

// �������� �� ��, ��� ������ ����������
assert(p);

// ������������ ������ �������. ��� ������� � ������� �������� ���, ��� � �����
// ������ ������ ������, ���������� ��� ������, ���������� ��������� ��
// ���������� ��������� ���� Class, ����������� ����� ����� �������. �����
// ���� ��������� ����� � ���������� class. p ��� ��� ��������� �� �� �����,
// ���� ������ ���� class.
*(const struct Class**)p = class;

// ���� ����� �����������...
if (class->ctor) {
    va_list ap;

    // �������������� ������ � ����������� �����������. ����� ����������
    // va_start ap ����� ��������� �� ��������� �������� ����� _class,
    // �� ���� ������ ��������, ������� ������ ��������� �������-������������.
    va_start(ap, _class);

    // �������� �����������
    p = class->ctor(p, &ap);

    // ������� ap
    va_end(ap);
    // ���������� ��������� �� ������
    }
    return p;
}

// ���������� ������� delete
void delete(void* self)
{
    // ��������� ��� ����������� ������ � �������� ������ �������,
    // ������� ������� �������������� �����
    const struct Class** cp = self;

    // �������� �����������. *cp �������� ��������� �� struct Class,
    // �� ������� ������ ���� dtor
    if (self && *cp && (*cp)->dtor)
        // ���� ���������� �����, �������� ���. �� ������ ������� ���������
        // �� �������� ���� ������
        self = (*cp)->dtor(self);

    // ����������� ���������� ���� ������
    free(self);
}

// ���������� ������� draw
void draw(const void* self)
{
    // ��������� ��� ����������� ������ � �������� ������ �������,
    // ������� ������� �������������� �����
    const struct Class* const* cp = self;

    // ���������, ��� ������, �������� ������ � ��������� �� ���������� ������������
    // ������ �������� ����������
    assert(self && *cp && (*cp)->draw);

    // �������� ����������� ����� �� ���������
    (*cp)->draw(self);
}

void check(const void* self, desk* desk)
{
    // ��������� ��� ����������� ������ � �������� ������ �������,
    // ������� ������� �������������� �����
    const struct Class* const* cp = self;

    // ���������, ��� ������, �������� ������ � ��������� �� ���������� ������������
    // ������ �������� ����������
    assert(self && *cp && (*cp)->check);

    // �������� ����������� ����� �� ���������
    (*cp)->check(self, desk);
}
