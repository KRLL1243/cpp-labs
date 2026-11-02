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

long long digitSum(long long number)
{
    long long sum = 0;
    while (number > 0)
    {
        sum += number % 10;
        number /= 10;
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
    std::cout << "Подходящие числа:\n";
    while (true)
    {
        if (isPrime(number) && isPrime(digitSum(number)))
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