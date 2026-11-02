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

bool isPrime(long long number)
{
    if (number < 2)
        return false;
    if (number == 2)
        return true;
    if (number % 2 == 0)
        return false;

    long long divisor = 3;
    while (divisor <= number / divisor)
    {
        if (number % divisor == 0)
            return false;
        divisor += 2;
    }
    return true;
}

int main()
{
    setupConsole();

    long long t;
    std::cout << "Введите количество пар T: ";
    if (!readNatural(t))
        return 1;

    long long found = 0;
    long long p = 3;
    const long long limit = std::numeric_limits<long long>::max();
    std::cout << "Пары близнецов:\n";
    while (found < t)
    {
        if (p > limit - 2)
        {
            std::cout << "Достигнута граница типа; выведено пар: " << found << '\n';
            return 1;
        }
        if (isPrime(p) && isPrime(p + 2))
        {
            std::cout << p << ' ' << p + 2 << '\n';
            ++found;
        }
        p += 2;
    }

    return 0;
}