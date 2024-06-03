// ����������� ��������� ��� ������������� �����, ������������� ��� �����������
// ���������
#ifndef __new_h
#define __new_h
#include "CChess.h"
// ����� ��� size_t (����������� ����� � ��������, ��������������� �����������
// �����������)
#include <stddef.h>

// ����� ��� va_list (���, �� ������� ������������ ������ � ����������
// ����������� ���������� � �������)
#include <stdarg.h>

/*
 * ������� ���������, � ������� �������� ���������� � ������. �� ������ ��
 * ���������� �������! ��� ������� ������ ���������� ����-������������ ����������
 * ���������� ���� Class.
 */
struct Class {
    // ������ ������� ������������ ������ � ������
    size_t size;
    /*
     * ��������� �� �������-�����������, ���������� � �������� ��������
     * �������. � �������� ������� ��������� (self) ������� ��������� ���������
     * �� ���������� ��� ������ ������ (�������� size).  ������ �������� �
     * ��������� �� ���������� ���� va_list, ������� ���������� �� ������ ��������
     * ������������. ���� ����������� ��������� �����-���� ���������, �� ������
     * �������� �� � ������� ������� ���������� * ������� va_arg.
     *
     * �������-����������� ���������� ���������, ������� �����
     * �������� ����������� ������ new. ��� �������, ��� ������ ������ self.
     *
     * ��������� ctor ����� ���� �������, � ���� ������ ��������
     * ��������������� ��������������� ������� �� ������������, � ������
     * ���������� ���������� ������.
     */
    void* (*ctor)(void* self, va_list* app);

    /*
     * ��������� �� �������-����������. � �������� ��������� ������� ���������
     * ��������� �� ������ � ������������ ����������� �������� �� �������:
     * �������� ������, ������������ ������������� ���������� ������ � �.�.
     *
     * ��������� dtor ����� ���� �������, � ���� ������ ������� ��
     * ������������, � ������ ������������� ���������� ������.
     *
     * ���������� ������ ������� ��� ���������, ������� ����������� �
     * �������� ��������� ������������ (������ ��� ������ self).
     */
    void* (*dtor)(void* self);

    /*
     * ��������� �� ���������� ����������� �������, ������� ����� ���������� �
     * ����������� �� ��������� ���� �������. � ������ ������� ���� ����� ����
     * ����������� �������, draw. ���� ������ ������� �������� ����������
     * ����������� �������, ��� ��� ������ ���� ��������� ���� � ����������������
     * �����������.
     *
     * ������ �������� ������� (self) � ��������� �� ������.
     */
    void (*draw)(const void* self);

    void (*check)(const void* self, void* desk);

};

// ������� �������� �������. ������ �������� � ��������� �� ���������-��������
// ������ (���� Class). ������ ��������� ����� �������� ������������ (ctor).
// ������� ���������� ��������� �� ��������� � ��������������������� ������.
void* new(const void* class, ...);

// ������� ����������� �������. �������� item � ��������� �� ������
// (������� ��� ����� ��������� �������� new). ����� ������������� ������
// �������� ���������� dtor (��� ��� �������).
void delete(void* item);

// ����������� ������� draw. �������� self � ��������� �� ������. � ����������� ��
// ������ ������� ����� ������� ��������������� ���������� draw.
void draw(const void* self);
void check(const void* self, desk* desk);
#endif