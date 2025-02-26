/*
************** ������� **************
����������� ��� ��������, ������� �� ������ � ������ ���� :
*/

class Foo {
public:
    Foo (int j) { i = new int [j]; }
    ~Foo () { delete i; }
private:
    int* i;
};

class Bar : Foo {
public:
    Bar (int j) { i = new char [j]; }
    ~Bar () { delete i; }
private:
    char* i;
};


void main () {
    Foo* f = new Foo (100);
    Foo* b = new Bar (200);
    *f = *b;
    delete f;
    delete b;
}

/* _____������:_____ */
/* �������� ��� � ���������� �� �������� */

class Foo {
public:
    Foo (int j) { i = new int [j]; }
    ~Foo () { delete i; }
private:
    int* i;
};

class Bar : Foo {
public:
    /* ����������� �������� ������ �� ���������� */
    Bar (int j) { i = new char [j]; }

    /* ������ ������, ������ ���� delete[] i; */
    ~Bar () { delete i; }
private:
    char* i;
};

/* ������ ���� int main() */
void main () {
    Foo* f = new Foo (100);
    Foo* b = new Bar (200);

    /* ����������� ��� ������������� ��������� ������������ */
    *f = *b;
    /* �������������� ��������� ��� ������� �������� */
    delete f;

    /* ���������� Bar �� ���������� */
    delete b;
}

/* ������������ ���: */
#include <iostream>

class Foo {
public:
    Foo (int j) : i (new int [j]) {}

    /* ����������� ���������� */
    virtual ~Foo () { delete [] i; }

    /* ������ ����������� � ������������ */
    Foo (const Foo&) = delete;
    Foo& operator=(const Foo&) = delete;

protected:
    int* i;
};

class Bar : public Foo {
public:
    Bar (int j) : Foo (j), i (new char [j]) {}
    /* ������������ ������� */
    ~Bar () override { delete [] i; }

    /* ������ ����������� � ������������ */
    Bar (const Bar&) = delete;
    Bar& operator=(const Bar&) = delete;

private:
    char* i;
};

int main () {
    Foo* f = new Foo (100);
    Foo* b = new Bar (200);

    /* ������ ��� ������� ������ ����������, ��� ��� �������� ������������ ������ */
    // *f = *b;

    delete f;
    delete b;

    return 0;
}

