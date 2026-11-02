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

    long long n;
    std::cout << "Введите натральное число N: ";
    if (!readNatural(n))
        return 1;

    long long a = 2;
    bool found = false;
    std::cout << "Дружественные пары:\n";
    while (a <= n)
    {
        long long b = sumProperDivisors(a, n);
        if (b > a && sumProperDivisors(b, a) == a)
        {
            std::cout << a << ' ' << b << '\n';
            found = true;
        }
        if (a == n)
            break;
        ++a;
    }
    if (!found)
        std::cout << "Нет\n";

    return 0;
}