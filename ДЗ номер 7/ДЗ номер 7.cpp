#include <iostream>
#include <Windows.h>

double Airplanes[2][8] = {
    { 300,  750, 1500, 2000, 1, 4, 7,   0 },
    { 1000, 1000, 2000, 3000, 2, 4, 6, 100 }
};

double Consumption(int plane, double weight) {
    for (int r = 0; r < 3; r++) {
        if (weight <= Airplanes[plane][1 + r]) {
            return Airplanes[plane][4 + r];
        }
    }
    return -1;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choose = 0;

    while (true)
    {
        system("cls");
        std::cout << "\n\n\n\t\tАвиапарк \"Спайди Спайдовича\"\n\n\n";
        std::cout << "1 - Выбрать самолёт\n";
        std::cout << "2 - Выйти\n";
        std::cin >> choose;

        if (choose == 1)
        {
            int planeNum = 0;
            system("cls");
            std::cout << "Самолёт №1: бак 300 л, расход 1/4/7 л/км (до 750/1500/2000 кг)\n";
            std::cout << "Самолёт №2: бак 1000 л + сбрасываемый 100 л, расход 2/4/6 л/км (до 1000/2000/3000 кг)\n\n";
            std::cout << "Введите номер самолёта (1 или 2): ";
            std::cin >> planeNum;

            if (planeNum != 1 && planeNum != 2) {
                std::cout << "\n!!!НЕКОРРЕКТНЫЙ ВЫБОР САМОЛЁТА!!!\n";
                Sleep(1500);
                continue;
            }
            int plane = planeNum - 1;

            double distanceAB, distanceBC, weight;
            std::cout << "Введите расстояние A-B (км): ";
            std::cin >> distanceAB;
            std::cout << "Введите расстояние B-C (км): ";
            std::cin >> distanceBC;
            std::cout << "Введите вес груза (кг): ";
            std::cin >> weight;

            if (distanceAB <= 0 || distanceBC <= 0 || weight < 0) {
                std::cout << "\n!!!НЕКОРРЕКТНЫЕ ДАННЫЕ!!!\n";
                Sleep(1000);
                break;
            }

            double r = Consumption(plane, weight);
            if (r < 0) {
                std::cout << "\nПревышена грузоподъёмность самолёта.\n";
                Sleep(1000);
                break;
            }

            double tankCap = Airplanes[plane][0];
            double dropCap = Airplanes[plane][7];

            double needAB = r * distanceAB;
            if (needAB > tankCap + dropCap) {
                std::cout << "\nНевозможно преодолеть расстояние A-B, т.к. не хватает топлива.\n";
                Sleep(1000);
                break;
            }

            double usedFromDrop;
            if (dropCap < needAB) {
                usedFromDrop = dropCap;
            }
            else {
                usedFromDrop = needAB;
            }

            double usedFromMain = needAB - usedFromDrop;
            double remainMain = tankCap - usedFromMain;

            double needBC = r * distanceBC;
            if (needBC > tankCap) {
                std::cout << "\nНевозможно преодолеть расстояние B-C, т.к. не хватает топлива.\n";
                Sleep(1000);
                break;
            }

            double refuel = needBC - remainMain;
            if (refuel < 0) refuel = 0;

            std::cout << "Расход топлива: " << r << " л/км\n";
            std::cout << "Нужно на A-B: " << needAB << " л\n";
            std::cout << "Остаток основного бака в B: " << remainMain << " л\n";
            std::cout << "Нужно на B-C: " << needBC << " л\n";
            std::cout << "Минимальная дозаправка в B: " << refuel << " л\n";
            Sleep(3000);
            break;
        }
        else if (choose == 2)
        {
            std::cout << "\nДо свидания!\n";
            Sleep(1000);
            break;
        }
        else
        {
            std::cout << "\n!!!НЕКОРРЕКТНЫЙ ВВОД, ВВЕДИТЕ НУЖНОЕ ЗНАЧЕНИЕ!!!\n";
            Sleep(1000);
        }
    }
    return 0;
}