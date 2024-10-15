#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <cstdlib>

using namespace std;

void create(double* arr, int SIZE, double MIN, double MAX, int i)
{
    if (i < SIZE)
    {
        arr[i] = MIN + static_cast<double>(rand()) / RAND_MAX * (MAX - MIN);
        create(arr, SIZE, MIN, MAX, i + 1);
    }
}

void Print(double* arr, int SIZE, int i)
{
    if (i < SIZE)
    {
        cout << setw(10) << fixed << setprecision(2) << arr[i];
        Print(arr, SIZE, i + 1);
    }
    else
    {
        cout << endl;
    }
}

double sumOddIndexed(double* arr, int SIZE, int i)
{
    if (i >= SIZE) return 0.0;
    return (i % 2 != 0 ? arr[i] : 0) + sumOddIndexed(arr, SIZE, i + 1);
}

double sumBetweenNegatives(double* arr, int SIZE, int i, int& firstNeg, int& lastNeg)
{
    if (i >= SIZE) return 0.0;
    if (arr[i] < 0)
    {
        if (firstNeg == -1) firstNeg = i;
        lastNeg = i;
    }
    return arr[i] + sumBetweenNegatives(arr, SIZE, i + 1, firstNeg, lastNeg);
}

void compressArray(double* arr, int SIZE, double* tempArr, int& newSize, int i)
{
    if (i < SIZE)
    {
        if (abs(arr[i]) > 1) tempArr[newSize++] = arr[i];
        compressArray(arr, SIZE, tempArr, newSize, i + 1);
    }
}

void fillZeros(double* arr, int SIZE, int start)
{
    for (int i = start; i < SIZE; i++)
        arr[i] = 0;
}

int main()
{
    srand(static_cast<unsigned>(time(NULL)));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int SIZE;
    cout << "Введіть розмір масиву (SIZE): ";
    cin >> SIZE;

    double MIN = -20.0, MAX = 20.0;
    double* arr = new double[SIZE];

    create(arr, SIZE, MIN, MAX, 0);
    cout << "Згенерований масив: ";
    Print(arr, SIZE, 0);

    int firstNeg = -1, lastNeg = -1;
    double sumNegatives = sumBetweenNegatives(arr, SIZE, 0, firstNeg, lastNeg);

    cout << "Сума елементів масиву з непарними номерами: " << sumOddIndexed(arr, SIZE, 0) << endl;
    cout << "Сума елементів масиву між першим і останнім від'ємними елементами: "
        << (firstNeg != -1 && lastNeg != -1 ? sumNegatives : 0.0) << endl;

    double* tempArr = new double[SIZE];
    int newSize = 0;
    compressArray(arr, SIZE, tempArr, newSize, 0);
    fillZeros(arr, SIZE, newSize);

    cout << "Стиснений масив: ";
    Print(arr, SIZE, 0);

    delete[] arr;
    delete[] tempArr;

    return 0;
}
