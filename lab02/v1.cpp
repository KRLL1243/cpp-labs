#include <iostream>
#define NOMINMAX
#include <limits>

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    long long n;
    bool different = true;
    std::cout << "Введите натуральное число: ";

    while (!(std::cin >> n) || n <= 0)
    {
        std::cout << "Введите натуральное число(натуральное!): ";

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    while (n > 0)
    {
        int digit = n % 10;
        unsigned long long m = n / 10;

        while (m > 0)
        {
            if (m % 10 == digit)
            {
                different = false;
                break;
            }
            m /= 10;
        }

        if (!different)
        {
            break;
        }

        n /= 10;
    }

    if (different)
        std::cout << "Все цифры различны";
    else
        std::cout << "Есть одинаковые цифры";

    return 0;
}