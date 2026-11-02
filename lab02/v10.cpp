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

bool isArmstrong(long long number)
{
    int digits = 0;
    long long copy = number;
    while (copy > 0)
    {
        ++digits;
        copy /= 10;
    }

    long long sum = 0;
    copy = number;
    while (copy > 0)
    {
        long long digit = copy % 10;
        long long power = 1;
        int step = 0;
        while (step < digits)
        {
            if (digit != 0 && power > number / digit)
                return false;
            power *= digit;
            ++step;
        }

        if (power > number - sum)
            return false;
        sum += power;
        copy /= 10;
    }
    return sum == number;
}

int main()
{
    setupConsole();

    long long n;
    std::cout << "Введите натуральное число N: ";
    if (!readNatural(n))
        return 1;

    long long number = 1;
    bool found = false;
    std::cout << "Числа Армстронга:\n";
    while (number <= n)
    {
        if (isArmstrong(number))
        {
            std::cout << number << ' ';
            found = true;
        }
        if (number == n)
            break;
        ++number;
    }
    if (!found)
        std::cout << "Нет";
    std::cout << '\n';

    return 0;
}