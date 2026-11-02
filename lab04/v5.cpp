#include <iostream>
#include <cstdint>
#include <cstddef>
#include <random>
#include <limits>
#include <exception>
#include <iomanip>
#include <string>
#include <utility>
#include <new>
#include <stdexcept>

constexpr std::int32_t MAX_ROWS = 100;
constexpr std::int32_t MAX_COLUMNS = 100;

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

void deleteMatrix(std::int32_t **matrix, std::size_t rows)
{
    if (matrix == nullptr)
    {
        return;
    }
    for (std::size_t i = 0; i < rows; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

std::int32_t **createMatrix(std::size_t rows, std::size_t columns)
{
    std::int32_t **matrix = new std::int32_t *[rows]{};
    try
    {
        for (std::size_t i = 0; i < rows; ++i)
        {
            matrix[i] = new std::int32_t[columns]{};
        }
    }
    catch (...)
    {
        deleteMatrix(matrix, rows);
        throw;
    }
    return matrix;
}

void fillMatrix(std::int32_t **matrix, std::size_t rows, std::size_t columns)
{
    constexpr std::int32_t minimum = std::numeric_limits<std::int32_t>::min();
    constexpr std::int32_t maximum = std::numeric_limits<std::int32_t>::max();
    std::cout << "\nСпособ заполнения:\n1 - ручной ввод\n2 - случайные числа\n";
    std::int32_t mode = readInteger("Ваш выбор: ", 1, 2);
    if (mode == 1)
    {
        for (std::size_t i = 0; i < rows; ++i)
        {
            std::cout << "Строка " << i + 1 << ":\n";
            for (std::size_t j = 0; j < columns; ++j)
            {
                std::cout << "  Элемент " << j + 1 << ": ";
                matrix[i][j] = readInteger("", minimum, maximum);
            }
        }
    }
    else
    {
        std::int32_t lower = readInteger("Нижняя граница: ", minimum, maximum);
        std::int32_t upper = readInteger("Верхняя граница: ", lower, maximum);
        std::mt19937 generator{std::random_device{}()};
        std::uniform_int_distribution<std::int32_t> distribution(lower, upper);
        for (std::size_t i = 0; i < rows; ++i)
        {
            for (std::size_t j = 0; j < columns; ++j)
            {
                matrix[i][j] = distribution(generator);
            }
        }
    }
}

void printMatrix(const std::int32_t *const *matrix, std::size_t rows, std::size_t columns)
{
    for (std::size_t i = 0; i < rows; ++i)
    {
        for (std::size_t j = 0; j < columns; ++j)
        {
            std::cout << std::setw(12) << matrix[i][j];
        }
        std::cout << '\n'
                  << '\n';
    }
}

bool rowHasNegative(const std::int32_t *row, std::size_t columns)
{
    for (std::size_t j = 0; j < columns; ++j)
    {
        if (row[j] < 0)
        {
            return true;
        }
    }
    return false;
}

void printProduct(const std::int32_t *const *matrix, std::size_t rows, std::size_t columns)
{
    bool foundRow = false;
    bool foundZero = false;
    for (std::size_t i = 0; i < rows; ++i)
    {
        if (!rowHasNegative(matrix[i], columns))
        {
            foundRow = true;
            for (std::size_t j = 0; j < columns; ++j)
            {
                if (matrix[i][j] == 0)
                {
                    foundZero = true;
                }
            }
        }
    }

    std::cout << "\nОбщее произведение элементов строк без отрицательных чисел: ";
    if (!foundRow)
    {
        std::cout << "невозможно вычислить - подходящих строк нет.\n";
        return;
    }
    if (foundZero)
    {
        std::cout << "0\n";
        return;
    }

    std::int64_t product = 1;
    constexpr std::int64_t limit = std::numeric_limits<std::int64_t>::max();
    for (std::size_t i = 0; i < rows; ++i)
    {
        if (rowHasNegative(matrix[i], columns))
        {
            continue;
        }
        for (std::size_t j = 0; j < columns; ++j)
        {
            std::int64_t value = matrix[i][j];
            if (product > limit / value)
            {
                std::cout << "невозможно представить в std::int64_t(переполнение).\n";
                return;
            }
            product *= value;
        }
    }
    std::cout << product << '\n';
}

void moveMaximumToTopLeft(std::int32_t **matrix, std::size_t rows, std::size_t columns)
{
    std::int32_t maximum = 0;
    std::size_t maxRow = 0;
    std::size_t maxColumn = 0;
    for (std::size_t i = 0; i < rows; ++i)
    {
        for (std::size_t j = 0; j < columns; ++j)
        {
            if (matrix[i][j] > maximum)
            {
                maximum = matrix[i][j];
                maxRow = i;
                maxColumn = j;
            }
        }
    }
    if (maximum == 0)
    {
        std::cout << "\nПерестановка невозможна: положительных элементов нет.\n";
        return;
    }

    std::cout << "\nМаксимальный положительный элемент: " << maximum
              << "; исходная строка " << maxRow + 1
              << ", столбец " << maxColumn + 1 << ".\n";
    std::swap(matrix[0], matrix[maxRow]);
    for (std::size_t i = 0; i < rows; ++i)
    {
        std::swap(matrix[i][0], matrix[i][maxColumn]);
    }
    std::cout << "Матрица после перестановки строк и столбцов:\n";
    printMatrix(matrix, rows, columns);
}

int main()
{
    std::int32_t **matrix = nullptr;
    std::size_t rows = 0;
    std::size_t columns = 0;
    try
    {
        std::cout << "Введите размеры вашего прямоугольного массива.\n";
        rows = static_cast<std::size_t>(readInteger("Кол-во строк: ", 1, MAX_ROWS));
        columns = static_cast<std::size_t>(readInteger("Кол-во столбцов: ", 1, MAX_COLUMNS));
        matrix = createMatrix(rows, columns);
        fillMatrix(matrix, rows, columns);
        std::cout << "\nИсходная матрица:\n";
        printMatrix(matrix, rows, columns);
        printProduct(matrix, rows, columns);
        moveMaximumToTopLeft(matrix, rows, columns);
    }
    catch (const std::bad_alloc &)
    {
        std::cerr << "Ошибка: недостаточно памяти.\n";
    }
    catch (const std::exception &error)
    {
        std::cerr << "Ошибка: " << error.what() << '\n';
    }
    deleteMatrix(matrix, rows);
    return 0;
}