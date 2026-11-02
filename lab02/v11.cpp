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

long long sumProperDivisors(long long number, long long limit)
{
    if (number == 1)
        return 0;

    long long sum = 1;
    long long divisor = 2;
    while (divisor <= number / divisor)
    {
        if (number % divisor == 0)
        {
            if (divisor > limit - sum)
                return 0;
            sum += divisor;

            long long other = number / divisor;
            if (other != divisor)
            {
                if (other > limit - sum)
                    return 0;
                sum += other;
            }
        }
        ++divisor;
    }
    return sum;
}

int main()
{
    setupConsole();

    long long a, b;
    std::cout << "Введите начало отрезка a: ";
    if (!readNatural(a))
        return 1;
    std::cout << "Введите конец отрезка b: ";
    if (!readNatural(b))
        return 1;
    if (a > b)
    {
        std::cout << "Ошибка: должно выполняться a <= b.\n";
        return 1;
    }

    long long number = a;
    bool found = false;
    std::cout << "Совершенные числа:\n";
    while (true)
    {
        if (sumProperDivisors(number, number) == number)
        {
            std::cout << number << ' ';
            found = true;
        }
        if (number == b)
            break;
        ++number;
    }
    if (!found)
        std::cout << "Нет";
    std::cout << '\n';

    return 0;
}