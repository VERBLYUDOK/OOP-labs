#include "Figure.h"
#include "Hexagon.h"
#include "Pentagon.h"
#include "Rhombus.h"

int main() {
    int size {5}; // Начальный размер массива
    int count {0}; // Количество фигур в массиве
    Figure** figures = new Figure*[size];

    char choice;
    do {
        std::cout << "Меню:\n";
        std::cout << "1. Добавить фигуру в массив\n";
        std::cout << "2. Вывод фигур (координаты, геометрический центр, площадь)\n";
        std::cout << "3. Удалить фигуру по индексу\n";
        std::cout << "4. Выход\n";
        std::cout << "Выбор: ";

        std::cin >> choice;

        switch(choice) {
            case '1': {
                if (count >= size) {
                    size *= 2;
                    Figure** temp = new Figure*[size];
                    for (size_t i {0}; i < count; ++i) {
                        temp[i] = figures[i];
                    }
                    delete [] figures;
                    figures = temp;
                    temp = nullptr;
                }

                std::cout << "Выберите тип фигуры:\n";
                std::cout << "1. Ромб\n";
                std::cout << "2. 5-тиугольник\n";
                std::cout << "3. 6-тиугольник\n";
                std::cout << "Выбор: ";

                char figChoice;
                std::cin >> figChoice;

                switch(figChoice) {
                    case '1':
                        figures[count] = new Rhombus();
                        break;
                    case '2':
                        figures[count] = new Pentagon();
                        break;
                    case '3':
                        figures[count] = new Hexagon();
                        break;
                    default:
                        std::cout << "Некорректный ввод\n";
                        continue;
                }

                std::cin >> *figures[count];
                ++count;
                std::cout << "-----------------------\n";
                break;
            }
            case '2': {
                double totalArea {0.0};
                double area;
                for (size_t i {0}; i < count; ++i) {
                    std::cout << "Фигура " << i + 1 << ":\n";
                    std::cout << *figures[i];
                    area = static_cast<double>(*figures[i]);
                    std::cout << "Площадь: " << area << '\n';
                    totalArea += area;
                }
                std::cout << "Общая площадь: " << totalArea << '\n';
                std::cout << "-----------------------\n";
                break;
            }
            case '3': {
                std::cout << "Введите индекс (от 1 до " << count << "): ";
                int index;
                std::cin >> index;
                if (index < 1 || index > count) {
                    std::cout << "Некорректный ввод\n";
                } else {
                    delete figures[index - 1];
                    for (size_t i = index - 1; i < count; ++i) {
                        figures[i] = figures[i + 1];
                    }
                    figures[count] = nullptr;
                    --count;
                }
                std::cout << "-----------------------\n";
                break;
            }
            case '4':
                std::cout << "Выход...\n";
                break;
            default:
                std::cout << "Некорректный ввод\n";
                std::cout << "-----------------------\n";
        }
    } while (choice != '4');

    for (size_t i {0}; i < count; ++i) {
        delete figures[i];
    }
    delete[] figures;

    return 0;    
}