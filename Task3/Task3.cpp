/*3. Что не так в этом коде ? Перечислите, какие недостатки вы видите.Предложите свой вариант рефакторинга.*/

/* _____Исходный код_____ */
#include <stdio.h>
class Feature {
public:
    enum FeatureType { eUnknown, eCircle, eTriangle, eSquare };

    Feature () : type (eUnknown), points (0) {}
    ~Feature () {
        if (points)
            delete points;  //  память была выделена new double [n]; , нужен delete []
    }

    // метод не изменяет состояние, значит должен быть const
    bool isValid () {
        return type != eUnknown;
    }

    bool read (FILE* file) {
        if (fread (&type, sizeof (FeatureType), 1, file) != sizeof (FeatureType))
            return false;
        short n = 0;
        switch (type) {
            case eCircle: n = 3; break;
            case eTriangle:    n = 6; break;
            case eSquare: n = 8; break;
            default: type = eUnknown; return false;
        }
        // нет обработчика ошибок, на случай, что память не будет выделена. предпочитаю std::vector
        points = new double [n];
        if (!points)
            return false;
        // передача указателя на указатель,а не на сам массив
        return fread (&points, sizeof (double), n, file) == n * sizeof (double);
    }
    void draw () {
        // отсутствет проверка points на nullptr
        switch (type) {
            case eCircle: drawCircle (points [0], points [1], points [2]); break;
            case eTriangle: drawPoligon (points, 6); break;
            case eSquare: drawPoligon (points, 8); break;
        }
    }

protected:
    // нет реализации функций
    void drawCircle (double centerX, double centerY, double radius);
    void drawPoligon (double* points, int size);

    // следует перенести в private, чтобы не нарушать инкапсуляцию
    double* points;
    FeatureType type;
};

int main (int argc, char* argv []) {
    Feature feature;
    // нет проверки fopen на nullptr
    FILE* file = fopen ("features.dat", "r");

    // если read == false, нужен вывод ошибки
    feature.read (file);

    // отсутствует закрытие файла

    if (!feature.isValid ())
        return 1;
    return 0;
}


/* _____Исправленный код_____ */

#include <vector>
#include <iostream>

class Feature {
public:
    enum FeatureType { eUnknown, eCircle, eTriangle, eSquare };

    Feature () : type (eUnknown) {}

    // Деструктор по умолчанию (std::vector автоматически управляет памятью)
    ~Feature () = default;

    // Проверяем, является ли объект Feature валидным (тип не eUnknown)
    bool isValid () const {
        return type != eUnknown;
    }

    // Читаем данные из файла и инициализируем объект Feature
    bool read (FILE* file) {
        if (!file) return false;

        if (fread (&type, sizeof (FeatureType), 1, file) != 1)
            return false;

        size_t n = 0;

        switch (type) {
            case eCircle:   n = 3; break;
            case eTriangle: n = 6; break;
            case eSquare:   n = 8; break;
            default:        type = eUnknown;
                return false;
        }

        // Выделяем память для точек и читаем их из файла
        points.resize (n);
        return fread (points.data (), sizeof (double), n, file) == n;
    }

    // Отрисовываем фигуру в зависимости от её типа
    void draw () const {
        if (points.empty ()) return;

        switch (type) {
            case eCircle:    drawCircle  (points [0], points [1], points [2]);  break;
            case eTriangle:  drawPolygon (points.data (), 6);                   break;
            case eSquare:    drawPolygon (points.data (), 8);                   break;
        }
    }

private:
    // Отрисовка круга по координатам центра и радиусу
    void drawCircle (double centerX, double centerY, double radius) const;
    // Отрисовка многоугольника по массиву точек и их количеству
    void drawPolygon (const double* points, int size) const;

    std::vector<double> points;
    FeatureType type;
};

int main (int argc, char* argv []) {
    Feature feature;
    FILE* file = fopen ("features.dat", "r");
    if (!file) {
        std::cerr << "Failed to open file" << std::endl;
        return 1;
    }

    if (!feature.read (file)) {
        std::cerr << "Failed to read feature" << std::endl;
        fclose (file);
        return 1;
    }

    fclose (file);

    if (!feature.isValid ()) {
        std::cerr << "Invalid feature" << std::endl;
        return 1;
    }

    return 0;
}

void Feature::drawCircle (double centerX, double centerY, double radius) const {
    // реализация
}

void Feature::drawPolygon (const double* points, int size) const {
    // реализация
}
