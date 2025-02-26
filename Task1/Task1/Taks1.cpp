/*
************** ЗАДАНИЕ **************
Перечислите все проблемы, которые вы видите в данном коде :
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

/* _____Ответы:_____ */
/* Исходный код с указаниями на недочеты */

class Foo {
public:
    Foo (int j) { i = new int [j]; }
    ~Foo () { delete i; }
private:
    int* i;
};

class Bar : Foo {
public:
    /* Конструктор базового класса не вызывается */
    Bar (int j) { i = new char [j]; }

    /* Утечка памяти, должно быть delete[] i; */
    ~Bar () { delete i; }
private:
    char* i;
};

/* Должно быть int main() */
void main () {
    Foo* f = new Foo (100);
    Foo* b = new Bar (200);

    /* копирование без определенного оператора присваивания */
    *f = *b;
    /* неопределенное поведение при попытке удаления */
    delete f;

    /* Деструктор Bar не вызывается */
    delete b;
}

/* Исправленный код: */
#include <iostream>

class Foo {
public:
    Foo (int j) : i (new int [j]) {}

    /* Виртуальный деструктор */
    virtual ~Foo () { delete [] i; }

    /* Запрет копирования и присваивания */
    Foo (const Foo&) = delete;
    Foo& operator=(const Foo&) = delete;

protected:
    int* i;
};

class Bar : public Foo {
public:
    Bar (int j) : Foo (j), i (new char [j]) {}
    /* Освобождение массива */
    ~Bar () override { delete [] i; }

    /* Запрет копирования и присваивания */
    Bar (const Bar&) = delete;
    Bar& operator=(const Bar&) = delete;

private:
    char* i;
};

int main () {
    Foo* f = new Foo (100);
    Foo* b = new Bar (200);

    /* Теперь это вызовет ошибку компиляции, так как оператор присваивания удален */
    // *f = *b;

    delete f;
    delete b;

    return 0;
}

