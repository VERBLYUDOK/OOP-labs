#include <iostream>
#include <memory>
#include "Array.h"
#include "Figure.h"
#include "Hexagon.h"
#include "Pentagon.h"
#include "Rhombus.h"

int main() {
    using FigurePtr = std::shared_ptr<Figure<int>>;
    Array<FigurePtr> figures;

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
                std::cout << "Выберите тип фигуры:\n";
                std::cout << "1. Ромб\n";
                std::cout << "2. 5-тиугольник\n";
                std::cout << "3. 6-тиугольник\n";
                std::cout << "Выбор: ";

                char figChoice;
                std::cin >> figChoice;

                FigurePtr figure;

                switch(figChoice) {
                    case '1':
                        figure = std::make_shared<Rhombus<int>>();
                        break;
                    case '2':
                        figure = std::make_shared<Pentagon<int>>();
                        break;
                    case '3':
                        figure = std::make_shared<Hexagon<int>>();
                        break;
                    default:
                        std::cout << "Некорректный ввод\n";
                        continue;
                }

                std::cout << "Введите координаты вершин:\n";
                figure->Read(std::cin);
                figures.PushBack(figure);
                std::cout << "Фигура добавлена.\n";
                std::cout << "-----------------------\n";
                break;
            }
            case '2': {
                double totalArea = 0.0;
                for (size_t i = 0; i < figures.Size(); ++i) {
                    std::cout << "Фигура " << i + 1 << ":\n";
                    figures[i]->Print(std::cout);
                    double area = figures[i]->Area();
                    std::cout << "Площадь: " << area << '\n';
                    totalArea += area;
                }
                std::cout << "Общая площадь: " << totalArea << '\n';
                std::cout << "-----------------------\n";
                break;
            }
            case '3': {
                std::cout << "Введите индекс (от 1 до " << figures.Size() << "): ";
                size_t index;
                std::cin >> index;
                if (index < 1 || index > figures.Size()) {
                    std::cout << "Некорректный ввод\n";
                } else {
                    figures.RemoveAt(index - 1);
                    std::cout << "Фигура удалена.\n";
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

    // Умные указатели и шаблонный класс Array управляют памятью автоматически
    return 0;    
}
