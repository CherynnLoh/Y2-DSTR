// "SortUni.h"
#ifndef SORTUNI_H
#define SORTUNI_H

#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include "University.h"
using namespace std;
using namespace chrono;

class SortUni : public University
{
public:
    //*Quick Sort***
    // Sort University Based on Ar Score
    void sortUniversityByARScore(int start, int end);
    void quickSortAr(int low, int high);
    int partitionAr(int low, int high);

    // Sort University Based on Fsr Sscore
    void sortUniversityByFsrScore(int start, int end);
    void quickSortFsr(int low, int high);
    int partitionFsr(int low, int high);

    // Sort University Based on Er Score
    void sortUniversityByErScore(int start, int end);
    void quickSortEr(int low, int high);
    int partitionEr(int low, int high);

    // Sort University Based on Institution
    void sortUniversityByIns(int start, int end);
    void quickSortIns(int low, int high);
    int partitionIns(int low, int high);

    // Insetion Sort for Guest - Time
    void sortUniversityByInst(int begin, int end);
    void selectionSortIns();
    int findMinimumIndex(int startRow, int endRow, int col);
    void swapRows(int row1, int row2);

    // Print Sorted Universities
    void printSortedArray(int startRow, int endRow);

    // Prompt for User Input - Customer Sort
    void userinput(string &start, string &end);
};

// ArScore
void SortUni::sortUniversityByARScore(int start, int end)
{
    quickSortAr(0, maxrow - 1);
    printSortedArray(start, end);
}
// FsrScore
void SortUni::sortUniversityByFsrScore(int start, int end)
{
    quickSortFsr(0, maxrow - 1);
    printSortedArray(start, end);
}
// ErScore
void SortUni::sortUniversityByErScore(int start, int end)
{
    quickSortEr(0, maxrow - 1);
    printSortedArray(start, end);
}

void SortUni ::quickSortAr(int low, int high)
{
    if (low < high)
    {
        int pi = partitionAr(low, high);
        quickSortAr(low, pi - 1);
        quickSortAr(pi + 1, high);
    }
}

void SortUni::quickSortFsr(int low, int high)
{
    if (low < high)
    {
        int pi = partitionFsr(low, high);
        quickSortFsr(low, pi - 1);
        quickSortFsr(pi + 1, high);
    }
}

void SortUni ::quickSortEr(int low, int high)
{
    if (low < high)
    {
        int pi = partitionEr(low, high);
        quickSortEr(low, pi - 1);
        quickSortEr(pi + 1, high);
    }
}

int SortUni::partitionAr(int low, int high)
{
    double pivot = stod(universityarr[high][4]); // Convert "arScore" to double

    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (stod(universityarr[j][4]) > pivot) // Compare "arScore" values
        {
            i++;

            // Swap rows
            for (int col = 0; col < maxcol; col++)
            {
                string temp = universityarr[i][col];
                universityarr[i][col] = universityarr[j][col];
                universityarr[j][col] = temp;
            }
        }
    }

    // Swap rows
    for (int col = 0; col < maxcol; col++)
    {
        string temp = universityarr[i + 1][col];
        universityarr[i + 1][col] = universityarr[high][col];
        universityarr[high][col] = temp;
    }

    return i + 1;
}

int SortUni::partitionFsr(int low, int high)
{
    double pivot = stod(universityarr[high][8]); // Convert "fsrScore" to double

    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (stod(universityarr[j][8]) > pivot) // Compare "fsrScore" values
        {
            i++;

            // Swap rows
            for (int col = 0; col < maxcol; col++)
            {
                string temp = universityarr[i][col];
                universityarr[i][col] = universityarr[j][col];
                universityarr[j][col] = temp;
            }
        }
    }

    // Swap rows
    for (int col = 0; col < maxcol; col++)
    {
        string temp = universityarr[i + 1][col];
        universityarr[i + 1][col] = universityarr[high][col];
        universityarr[high][col] = temp;
    }

    return i + 1;
}

int SortUni::partitionEr(int low, int high)
{
    double pivot = stod(universityarr[high][6]); // Convert "erScore" to double

    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (stod(universityarr[j][6]) > pivot) // Compare "erScore" values
        {
            i++;

            // Swap rows
            for (int col = 0; col < maxcol; col++)
            {
                string temp = universityarr[i][col];
                universityarr[i][col] = universityarr[j][col];
                universityarr[j][col] = temp;
            }
        }
    }

    // Swap rows
    for (int col = 0; col < maxcol; col++)
    {
        string temp = universityarr[i + 1][col];
        universityarr[i + 1][col] = universityarr[high][col];
        universityarr[high][col] = temp;
    }

    return i + 1;
}

void SortUni::printSortedArray(int startRow, int endRow)
{
    // sortUniversityByFsrScore();
    printheader();

    // Validate the range of rows
    if (startRow < 0 || endRow >= maxrow || startRow > endRow)
    {
        cout << "Invalid range!" << endl;
        return;
    }

    for (int row = startRow; row <= endRow; ++row)
    {

        for (int col = 0; col < maxcol && !universityarr[row][col].empty(); ++col)
        {
            if (col == 0)
            {
                string str = universityarr[row][col];
                cout << left << setw(6) << str.substr(0, 6);
            }
            else if (col == 1)
            {
                string str = universityarr[row][col];
                cout << left << setw(65) << str.substr(0, 60);
            }
            else if (col == 2)
            {
                string str = universityarr[row][col];
                cout << left << setw(9) << str.substr(0, 9);
            }
            else if (col == 3)
            {
                string str = universityarr[row][col];
                cout << left << setw(18) << str.substr(0, 15);
            }
            else
            {
                cout << left << setw(8) << universityarr[row][col];
            }
        }
        cout << endl;
    }
}

void SortUni::userinput(string &start, string &end)
{
    cout << "\nThere are a total of 1422 Universities." << endl;
    cout << "Please Enter Start Range (0-1421): ";
    cin >> start;
    cout << "Please Enter End Range (0-1421): ";
    cin >> end;
}

void SortUni::sortUniversityByIns(int begin, int end)
{
    auto start = high_resolution_clock::now(); // Start measuring time

    quickSortIns(0, maxrow - 1);
    printSortedArray(begin, end);

    auto stop = high_resolution_clock::now();                  // Stop measuring time
    auto duration = duration_cast<milliseconds>(stop - start); // Calculate duration in milliseconds

    cout << "Execution time: " << duration.count() << " milliseconds" << endl;
}

void SortUni ::quickSortIns(int low, int high)
{
    if (low < high)
    {
        int pi = partitionIns(low, high);
        quickSortIns(low, pi - 1);
        quickSortIns(pi + 1, high);
    }
}

int SortUni::partitionIns(int low, int high)
{
    string pivot = universityarr[high][1];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (universityarr[j][1].compare(pivot) < 0) // Compare institution names in ascending order
        {
            i++;
            for (int col = 0; col < maxcol; col++)
            {
                string temp = universityarr[i][col];
                universityarr[i][col] = universityarr[j][col];
                universityarr[j][col] = temp;
            }
        }
    }

    for (int col = 0; col < maxcol; col++)
    {
        string temp = universityarr[i + 1][col];
        universityarr[i + 1][col] = universityarr[high][col];
        universityarr[high][col] = temp;
    }

    return i + 1;
}

void SortUni::sortUniversityByInst(int begin, int end)
{
    auto start = high_resolution_clock::now(); // Start measuring time

    selectionSortIns();
    printSortedArray(begin, end);

    auto stop = high_resolution_clock::now();                  // Stop measuring time
    auto duration = duration_cast<milliseconds>(stop - start); // Calculate duration in milliseconds

    cout << "Execution time: " << duration.count() << " milliseconds" << endl;
}

void SortUni::selectionSortIns()
{
    for (int i = 0; i < maxrow - 1; i++)
    {
        int minIndex = findMinimumIndex(i, maxrow - 1, 1);
        swapRows(i, minIndex);
    }
}

int SortUni::findMinimumIndex(int startRow, int endRow, int col)
{
    int minIndex = startRow;
    for (int i = startRow + 1; i <= endRow; i++)
    {
        if (universityarr[i][col].compare(universityarr[minIndex][col]) < 0)
        {
            minIndex = i;
        }
    }
    return minIndex;
}

void SortUni::swapRows(int row1, int row2)
{
    for (int col = 0; col < maxcol; col++)
    {
        string temp = universityarr[row1][col];
        universityarr[row1][col] = universityarr[row2][col];
        universityarr[row2][col] = temp;
    }
}

#endif //