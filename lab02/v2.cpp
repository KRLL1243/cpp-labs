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

    long long copy = n;
    int minDigit = 9;
    while (copy > 0)
    {
        int digit = static_cast<int>(copy % 10);
        if (digit < minDigit)
            minDigit = digit;
        copy /= 10;
    }

    long long result = 0;
    long long place = 1;
    int kept = 0;
    copy = n;
    while (copy > 0)
    {
        int digit = static_cast<int>(copy % 10);
        bool remove;
        if (minDigit == 0)
            remove = (digit == 0);
        else
            remove = (digit % minDigit == 0);

        if (!remove)
        {
            result += digit * place;
            place *= 10;
            ++kept;
        }
        copy /= 10;
    }

    if (kept == 0)
        std::cout << "Все цифры удалены.\n";
    std::cout << "Результат: " << result << '\n';

    return 0;
}
