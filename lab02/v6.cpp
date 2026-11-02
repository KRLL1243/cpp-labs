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

    if (n == 1)
    {
        std::cout << "У числа 1 нет простых множителей.\n";
        return 0;
    }

    long long copy = n;
    long long divisor = 2;
    bool first = true;
    std::cout << "Разложение: ";
    while (divisor <= copy / divisor)
    {
        while (copy % divisor == 0)
        {
            if (!first)
                std::cout << " * ";
            std::cout << divisor;
            first = false;
            copy /= divisor;
        }
        ++divisor;
    }

    if (copy > 1)
    {
        if (!first)
            std::cout << " * ";
        std::cout << copy;
    }
    std::cout << '\n';

    return 0;
}