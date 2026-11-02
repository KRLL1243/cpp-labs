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

    long long bestDigit = 0;
    int bestCount = 0;
    long long digit = 0;
    while (digit <= 9)
    {
        int count = 0;
        long long copy = n;
        while (copy > 0)
        {
            if (copy % 10 == digit)
                ++count;
            copy /= 10;
        }

        if (count > bestCount)
        {
            bestCount = count;
            bestDigit = digit;
        }
        ++digit;
    }

    std::cout << "Выбранная цифра: " << bestDigit << '\n';
    std::cout << "Результат: " << bestDigit << n << bestDigit << '\n';

    return 0;
}