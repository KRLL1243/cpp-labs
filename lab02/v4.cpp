#include <iostream>
#include <limits>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

void setupConsole()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
}

bool readNatural(long long &value)
{
    while (!(std::cin >> value) || value <= 0)
    {
        if (std::cin.eof() || std::cin.bad())
        {
            std::cout << "Ввод завершён.\n";
            return false;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка: введите целое число от 1 до " << std::numeric_limits<long long>::max() << ": ";
    }
    return true;
}

int main()
{
    setupConsole();

    long long n;
    std::cout << "Введите натуральное число N: ";
    if (!readNatural(n))
        return 1;

    int digits = 0;
    long long copy = n;
    while (copy > 0)
    {
        ++digits;
        copy /= 10;
    }

    if (digits % 2 == 0)
    {
        std::cout << "Результат: " << n << '\n';
    }
    else
    {
        copy = n;
        int steps = digits / 2;
        while (steps > 0)
        {
            copy /= 10;
            --steps;
        }
        int middle = copy % 10;
        std::cout << "Результат: " << middle << n << middle << '\n';
    }

    return 0;
}