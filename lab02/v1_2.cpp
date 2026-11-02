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
    unsigned int seen = 0;
    bool different = true;

    while (n > 0)
    {
        unsigned int digit = static_cast<unsigned int>(n % 10);
        unsigned int bit = 1u << digit;
        if ((seen & bit) != 0)
        {
            different = false;
            break;
        }
        seen |= bit;
        n /= 10;
    }

    if (different)
        std::cout << "Все цифры различны\n";
    else
        std::cout << "Есть одинаковые цифры\n";

    return 0;
}