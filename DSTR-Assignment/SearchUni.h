#ifndef SEARCHUNI_H
#define SEARCHUNI_H

#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include "SortUni.h"

class SearchUni : public SortUni
{
public:
    // Linear Search
    string linearRank(string inputRank, string difference);
    int linearArRank(string inputArRank);
    int linearErRank(string inputErRank);
    int linearFsrRank(string inputFsrRank);
    int linearCpfRank(string inputCpfRank);
    int linearIsrRank(string inputIsrRank);
    int linearIfrRank(string inputIfrRank);
    int linearIrnRank(string inputIrnRank);
    int linearGerRank(string inputRank);
    int linearIns(string inputGerIns, string difference);
    int linearLC(string inputLC);

    // Binary Search By Rank
    void binarySearchByRank(string rank);

    //Print Searched University
    int printSearchedUni(int index);

    //Check If No Unversity Found
    int checknone(int noUni);
};

string SearchUni::linearRank(string inputRank, string difference)
{
    auto start = chrono::steady_clock::now();
    int matches[maxrow]; // Array to store the indices of matched universities
    int numMatches = 0;  // Number of matches found

    for (int i = 0; i < maxrow; i++)
    {
        if (universityarr[i][0] == inputRank)
        {
            matches[numMatches] = i;
            numMatches++;
        }
    }

    if (checknone(numMatches) == -1)
    {
        return "Invalid Rank!"; // Return an empty string to indicate no matches found
    }
    else
    {
        printheader();
        // Print the details of matched universities
        for (int i = 0; i < numMatches; i++)
        {
            int printindex = printSearchedUni(matches[i]);
        }
    }
    auto end = chrono::steady_clock::now();

    // Calculate the duration in milliseconds
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    if (difference == "0")
    {
        // Print the execution time
        cout << "Execution time for Linear Search: " << duration << " milliseconds" << endl;
    }
    // Return the institution name of the first matched rank
    return universityarr[matches[0]][1];
}

int SearchUni::linearArRank(string inputArRank)
{
    int matches[maxrow]; // Array to store the indices of matched universities
    int numMatches = 0;  // Number of matches found

    for (int i = 0; i < maxrow; i++)
    {
        if (universityarr[i][5] == inputArRank)
        {
            matches[numMatches] = i;
            numMatches++;
        }
    }

    if (checknone(numMatches) == -1)
    {
        return -1; // Return a value to indicate no matches found
    }

    printheader();
    // Print the details of matched universities
    for (int i = 0; i < numMatches; i++)
    {
        printSearchedUni(matches[i]);
    }
}

int SearchUni::linearErRank(string inputErRank)
{
    int matches[maxrow]; // Array to store the indices of matched universities
    int numMatches = 0;  // Number of matches found

    for (int i = 0; i < maxrow; i++)
    {
        if (universityarr[i][7] == inputErRank)
        {
            matches[numMatches] = i;
            numMatches++;
        }
    }

    if (checknone(numMatches) == -1)
    {
        return -1; // Return a value to indicate no matches found
    }

    printheader();
    // Print the details of matched universities
    for (int i = 0; i < numMatches; i++)
    {
        printSearchedUni(matches[i]);
    }
}

int SearchUni::linearFsrRank(string inputfsrRank)
{
    int matches[maxrow]; // Array to store the indices of matched universities
    int numMatches = 0;  // Number of matches found

    for (int i = 0; i < maxrow; i++)
    {
        if (universityarr[i][9] == inputfsrRank)
        {
            matches[numMatches] = i;
            numMatches++;
        }
    }

    if (checknone(numMatches) == -1)
    {
        return -1; // Return a value to indicate no matches found
    }

    printheader();
    // Print the details of matched universities
    for (int i = 0; i < numMatches; i++)
    {
        printSearchedUni(matches[i]);
    }
}

int SearchUni::linearCpfRank(string inputcpfRank)
{
    int matches[maxrow]; // Array to store the indices of matched universities
    int numMatches = 0;  // Number of matches found

    for (int i = 0; i < maxrow; i++)
    {
        if (universityarr[i][11] == inputcpfRank)
        {
            matches[numMatches] = i;
            numMatches++;
        }
    }

    if (checknone(numMatches) == -1)
    {
        return -1; // Return a value to indicate no matches found
    }

    printheader();
    // Print the details of matched universities
    for (int i = 0; i < numMatches; i++)
    {
        printSearchedUni(matches[i]);
    }
}

int SearchUni::linearIfrRank(string inputIfrRank)
{
    int matches[maxrow]; // Array to store the indices of matched universities
    int numMatches = 0;  // Number of matches found

    for (int i = 0; i < maxrow; i++)
    {
        if (universityarr[i][13] == inputIfrRank)
        {
            matches[numMatches] = i;
            numMatches++;
        }
    }

    if (checknone(numMatches) == -1)
    {
        return -1; // Return a value to indicate no matches found
    }

    printheader();
    // Print the details of matched universities
    for (int i = 0; i < numMatches; i++)
    {
        printSearchedUni(matches[i]);
    }
}

int SearchUni::linearIsrRank(string inputIsrRank)
{
    int matches[maxrow]; // Array to store the indices of matched universities
    int numMatches = 0;  // Number of matches found

    for (int i = 0; i < maxrow; i++)
    {
        if (universityarr[i][15] == inputIsrRank)
        {
            matches[numMatches] = i;
            numMatches++;
        }
    }

    if (checknone(numMatches) == -1)
    {
        return -1; // Return a value to indicate no matches found
    }

    printheader();
    // Print the details of matched universities
    for (int i = 0; i < numMatches; i++)
    {
        printSearchedUni(matches[i]);
    }
}

int SearchUni::linearIrnRank(string inputIrnRank)
{
    int matches[maxrow]; // Array to store the indices of matched universities
    int numMatches = 0;  // Number of matches found

    for (int i = 0; i < maxrow; i++)
    {
        if (universityarr[i][17] == inputIrnRank)
        {
            matches[numMatches] = i;
            numMatches++;
        }
    }

    if (checknone(numMatches) == -1)
    {
        return -1; // Return a value to indicate no matches found
    }

    printheader();
    // Print the details of matched universities
    for (int i = 0; i < numMatches; i++)
    {
        printSearchedUni(matches[i]);
    }
}

int SearchUni::linearGerRank(string inputGerRank)
{
    int matches[maxrow]; // Array to store the indices of matched universities
    int numMatches = 0;  // Number of matches found

    for (int i = 0; i < maxrow; i++)
    {
        if (universityarr[i][19] == inputGerRank)
        {
            matches[numMatches] = i;
            numMatches++;
        }
    }

    if (checknone(numMatches) == -1)
    {
        return -1; // Return a value to indicate no matches found
    }

    printheader();
    // Print the details of matched universities
    for (int i = 0; i < numMatches; i++)
    {
        printSearchedUni(matches[i]);
    }
}

int SearchUni::linearIns(string inputIns, string difference)
{
    int matches[maxrow]; // Array to store the indices of matched universities
    int numMatches = 0;  // Number of matches found

    for (int i = 0; i < maxrow; i++)
    {
        string currentInstitution = universityarr[i][1];

        // Check if the input institution matches a substring of the current institution
        if (currentInstitution.find(inputIns) != string::npos)
        {
            matches[numMatches] = i;
            numMatches++;
        }
    }
    // cout << matches[numMatches] << endl;
    if (difference == "1")
    {
        if (checknone(numMatches) == -1)
        {
            return -1; // Return a value to indicate no matches found
        }
    }

    if (numMatches > 0 && difference == "1")
    {
        printheader();
        // Print the details of matched universities
        for (int i = 0; i < numMatches; i++)
        {
            printSearchedUni(matches[i]);
        }
    }
}

int SearchUni::linearLC(string inputLC)
{
    int matches[maxrow]; // Array to store the indices of matched universities
    int numMatches = 0;  // Number of matches found

    for (int i = 0; i < maxrow; i++)
    {
        if (universityarr[i][2] == inputLC)
        {
            matches[numMatches] = i;
            numMatches++;
        }
    }

    if (checknone(numMatches) == -1)
    {
        return -1; // Return a value to indicate no matches found
    }

    printheader();
    // Print the details of matched universities
    for (int i = 0; i < numMatches; i++)
    {
        printSearchedUni(matches[i]);
    }
}

int SearchUni ::printSearchedUni(int index)
{

    for (int col = 0; col < maxcol && !universityarr[index][col].empty(); ++col)
    {
        if (col == 0)
        {
            string str = universityarr[index][col];
            cout << left << setw(6) << str.substr(0, 6);
        }
        else if (col == 1)
        {
            string str = universityarr[index][col];
            cout << left << setw(65) << str.substr(0, 60);
        }
        else if (col == 2)
        {
            string str = universityarr[index][col];
            cout << left << setw(9) << str.substr(0, 9);
        }
        else if (col == 3)
        {
            string str = universityarr[index][col];
            cout << left << setw(18) << str.substr(0, 15);
        }
        else
        {
            cout << left << setw(8) << universityarr[index][col];
        }
        // cout << universityarr[row][col] << " ";
    }
    cout << endl;
    return index;
}

int SearchUni ::checknone(int noUni)
{
    if (noUni == 0)
    {
        std::cout << "No University Found." << std::endl;
        return -1; // Return a value to indicate no matches found
    }
}

void SearchUni::binarySearchByRank(string searchRank)
{
    auto start = chrono::steady_clock::now();
    int left = 0;
    int right = maxrow - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int currentRank = stoi(universityarr[mid][0]);

        if (currentRank == stoi(searchRank))
        {
            printheader();
            printSearchedUni(mid);
            break;
            // return mid; // Rank found at index mid
        }
        else if (currentRank < stoi(searchRank))
        {
            left = mid + 1; // Search in the right half
        }
        else
        {
            right = mid - 1; // Search in the left half
        }
    }
    auto end = chrono::steady_clock::now();

    // Calculate the duration in milliseconds
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    // Print the execution time
    cout << "Execution time for Binary Search: " << duration << " milliseconds" << endl;
}

#endif