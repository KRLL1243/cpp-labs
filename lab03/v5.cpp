#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <new>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

const std::int32_t MAX_ARRAY_SIZE = 1000;

std::int32_t readInteger(const std::string &prompt, std::int32_t minimum, std::int32_t maximum)
{
    while (true)
    {
        std::cout << prompt;
        std::int32_t value{};

        if (std::cin >> value)
        {
            int nextCharacter = std::cin.peek();
            bool numberEnded = std::cin.eof() || nextCharacter == ' ' || nextCharacter == '\n' || nextCharacter == '\t' || nextCharacter == '\r';
            if (numberEnded && value >= minimum && value <= maximum)
            {
                return value;
            }
        }

        if (std::cin.eof() || std::cin.bad())
        {
            throw std::runtime_error("Ввод завершён.");
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка: введите целое число от " << minimum << " до " << maximum << ".\n";
    }
}

void fillArray(std::int32_t *values, std::size_t count)
{
    std::cout << "\nСпособ заполнения:\n1 - ручной ввод\n2 - случайные числа\n";
    std::int32_t inputMode = readInteger("Ваш выбор: ", 1, 2);
    const std::int32_t minimum = std::numeric_limits<std::int32_t>::min();
    const std::int32_t maximum = std::numeric_limits<std::int32_t>::max();

    if (inputMode == 1)
    {
        std::cout << "Введите элементы массива:\n";
        for (std::size_t index = 0; index < count; ++index)
        {
            std::cout << "Элемент " << index + 1 << ": ";
            values[index] = readInteger("", minimum, maximum);
        }
    }
    else
    {
        std::int32_t lowerBound = readInteger("Нижняя граница: ", minimum, maximum);
        std::int32_t upperBound = readInteger("Верхняя граница: ", lowerBound, maximum);
        std::mt19937 generator(std::random_device{}());
        std::uniform_int_distribution<std::int32_t> distribution(lowerBound, upperBound);
        for (std::size_t index = 0; index < count; ++index)
        {
            values[index] = distribution(generator);
        }
    }
}

void printArray(const std::int32_t *values, std::size_t count)
{
    std::cout << '[';
    for (std::size_t index = 0; index < count; ++index)
    {
        if (index > 0)
        {
            std::cout << ' ';
        }
        std::cout << values[index];
    }
    std::cout << "]\n";
}

std::int64_t calculateProduct(const std::int32_t *values, std::size_t first, std::size_t last)
{
    bool negative = false;
    for (std::size_t index = first; index < last; ++index)
    {
        if (values[index] == 0)
        {
            return 0;
        }
        if (values[index] < 0)
        {
            negative = !negative;
        }
    }

    std::int64_t limit = -std::numeric_limits<std::int64_t>::max();
    if (negative)
    {
        limit = std::numeric_limits<std::int64_t>::min();
    }

    std::int64_t negativeProduct = -1;
    for (std::size_t index = first; index < last; ++index)
    {
        std::int64_t absoluteValue = values[index];
        absoluteValue = std::abs(absoluteValue);
        if (negativeProduct < limit / absoluteValue)
        {
            throw std::overflow_error("произведение выходит за допустимый диапазон.");
        }
        negativeProduct *= absoluteValue;
    }

    if (negative)
    {
        return negativeProduct;
    }
    return -negativeProduct;
}

void processArray(std::int32_t *values, std::size_t count)
{
    fillArray(values, count);
    std::cout << "\nИсходный массив: ";
    printArray(values, count);

    std::size_t signChanges = 0;
    std::size_t firstZero = count;
    std::size_t secondZero = count;

    for (std::size_t index = 0; index < count; ++index)
    {
        if (index > 0 && ((values[index - 1] < 0) != (values[index] < 0)))
        {
            ++signChanges;
        }
        if (values[index] == 0)
        {
            if (firstZero == count)
            {
                firstZero = index;
            }
            else if (secondZero == count)
            {
                secondZero = index;
            }
        }
    }

    std::cout << "Количество перемен знака: " << signChanges << '\n';
    std::cout << "Произведение между первым и вторым нулями: ";
    if (secondZero == count)
    {
        std::cout << "невозможно вычислить - в массиве меньше двух нулей.\n";
    }
    else if (secondZero == firstZero + 1)
    {
        std::cout << "между нулями нет элементов.\n";
    }
    else
    {
        try
        {
            std::int64_t product = calculateProduct(values, firstZero + 1, secondZero);
            std::cout << product << '\n';
        }
        catch (const std::overflow_error &error)
        {
            std::cout << "невозможно вычислить - " << error.what() << '\n';
        }
    }

    std::size_t evenPosition = 0;
    for (std::size_t index = 0; index < count; ++index)
    {
        if (values[index] % 2 == 0)
        {
            std::int32_t evenValue = values[index];
            for (std::size_t position = index; position > evenPosition; --position)
            {
                values[position] = values[position - 1];
            }
            values[evenPosition] = evenValue;
            ++evenPosition;
        }
    }

    std::cout << "Массив после преобразования(сначала чётные, затем нечётные): ";
    printArray(values, count);
}

int main()
{
    std::int32_t *dynamicValues = nullptr;
    try
    {
        std::cout << "Выберите тип массива:\n1 - статический массив\n2 - динамический массив\n3 - std::vector\n";
        std::int32_t arrayType = readInteger("Ваш выбор: ", 1, 3);
        std::cout << "Допустимое количество элементов: от 1 до " << MAX_ARRAY_SIZE << ".\n";
        std::size_t count = static_cast<std::size_t>(readInteger("Количество элементов: ", 1, MAX_ARRAY_SIZE));

        if (arrayType == 1)
        {
            std::int32_t values[MAX_ARRAY_SIZE]{};
            processArray(values, count);
        }
        else if (arrayType == 2)
        {
            dynamicValues = new std::int32_t[count]{};
            processArray(dynamicValues, count);
        }
        else
        {
            std::vector<std::int32_t> values(count);
            processArray(values.data(), count);
        }
    }
    catch (const std::bad_alloc &)
    {
        delete[] dynamicValues;
        std::cerr << "Ошибка: недостаточно памяти.\n";
        return 1;
    }
    catch (const std::exception &error)
    {
        delete[] dynamicValues;
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }

    delete[] dynamicValues;
    return 0;
}
