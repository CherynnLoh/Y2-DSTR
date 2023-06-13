//"University.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

const int maxrow = 1422;
const int maxcol = 21;

class University
{
public:
    struct UniversityColumns
    {
        string rank;
        string institution;
        string locationCode;
        string location;
        string arScore;
        string arRank;
        string erScore;
        string erRank;
        string fsrScore;
        string fsrRank;
        string cpfScore;
        string cpfRank;
        string ifrScore;
        string ifrRank;
        string isrScore;
        string isrRank;
        string irnScore;
        string irnRank;
        string gerScore;
        string gerRank;
        string scoreScaled;
    };

    // Create a new static 2D array
    string  universityarr[maxrow][maxcol];

    //functions definition
    void readFile(const string filename, string universityarr[][maxcol], int &rowCount, int &columnCount, UniversityColumns unidata[]);
    void printuniarray(const string universityarr[][maxcol], int maxrow);
    void printCheckarray(const string universityarr[][maxcol], int maxrow);
    void universityarray();
    void printuniarray2();
    void printheader();
    void printdash();
    void displayUniversities();
};

// Store data from csv to 2D array
void University::readFile(const string filename, string universityarr[][maxcol], int &rowCount, int &columnCount, UniversityColumns unidata[])
{
    ifstream file(filename);
    string line;

    rowCount = 0;
    columnCount = maxcol;

    getline(file, line);
    while (getline(file, line) && rowCount < maxrow)
    {
        istringstream lineStream(line);
        string columndata;
        int currentColumnCount = 0;

        while (getline(lineStream, columndata, ','))
        {
            if (!columndata.empty())
            {
                universityarr[rowCount][currentColumnCount] = columndata;
            }
            else if (columndata.empty())
            {
                universityarr[rowCount][currentColumnCount] = "0";
            }
            else
            {
                universityarr[rowCount][currentColumnCount] = "";
            }

            // Remove leading and trailing quotation marks from institution name
            if (currentColumnCount == 1)
            {
                string& institutionName = universityarr[rowCount][currentColumnCount];
                if (!institutionName.empty() && institutionName.front() == '\"' && institutionName.back() == '\"')
                {
                    institutionName = institutionName.substr(1, institutionName.length() - 2);
                }
            }

            currentColumnCount++;
        }

        // Assign values to UniversityColumns variables
        unidata[rowCount].rank = universityarr[rowCount][0];
        unidata[rowCount].institution = universityarr[rowCount][1];
        unidata[rowCount].locationCode = universityarr[rowCount][2];
        unidata[rowCount].location = universityarr[rowCount][3];
        unidata[rowCount].arScore = universityarr[rowCount][4];
        unidata[rowCount].arRank = universityarr[rowCount][5];
        unidata[rowCount].erScore = universityarr[rowCount][6];
        unidata[rowCount].erRank = universityarr[rowCount][7];
        unidata[rowCount].fsrScore = universityarr[rowCount][8];
        unidata[rowCount].fsrRank = universityarr[rowCount][9];
        unidata[rowCount].cpfScore = universityarr[rowCount][10];
        unidata[rowCount].cpfRank = universityarr[rowCount][11];
        unidata[rowCount].ifrScore = universityarr[rowCount][12];
        unidata[rowCount].ifrRank = universityarr[rowCount][13];
        unidata[rowCount].isrScore = universityarr[rowCount][14];
        unidata[rowCount].isrRank = universityarr[rowCount][15];
        unidata[rowCount].irnScore = universityarr[rowCount][16];
        unidata[rowCount].irnRank = universityarr[rowCount][17];
        unidata[rowCount].gerScore = universityarr[rowCount][18];
        unidata[rowCount].gerRank = universityarr[rowCount][19];
        unidata[rowCount].scoreScaled = universityarr[rowCount][20];

        rowCount++;
    }

    file.close();
}

// view in table form
void University ::printuniarray(const string universityarr[][maxcol], int maxrow)
{
    printheader();
    for (int row = 0; row < maxrow; ++row)
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
            // cout << universityarr[row][col] << " ";
        }
        cout << endl;
    }
}

//function to print header (as header not included in 2Darray)
void University ::printheader()
{
    cout << "\n*********Zoom Out to Have a Better View*********\n";
    printdash();
    cout << endl;
    cout << left << setw(6) << "Rank" <<
    left << setw(60) << "Instituition "<<
    left << setw(14)<< "Location Code"<<
    left << setw(17) << "Location"<<
    left << setw(9) << "arScore"<<
    left << setw(8) << "arRank" <<
    left << setw(8) << "erScore" <<
    left << setw(8) << "erRank" <<
    left << setw(8) << "fsrScore" <<
    left << setw(8) << "fsrRank" <<
    left << setw(8) << "cpfScore" <<
    left << setw(8) << "cpfRank" <<
    left << setw(8) << "IfrScore" <<
    left << setw(8) << "IfrRank" <<
    left << setw(8) << "IsrScore" <<
    left << setw(8) << "IsrRank" <<
    left << setw(8) << "IrnScore" <<
    left << setw(8) << "IrnRank" <<
    left << setw(8) << "GerScore" <<
    left << setw(8) << "GerRank" <<
    left << setw(8) << "scoreScaled" << endl;
    printdash();
    cout << endl;

}

// additional : another viewpoint to check if variables are assigned correctly
void University ::printCheckarray(const string universityarr[][maxcol], int maxrow)
{

    for (int row = 0; row < maxrow; ++row)
    {

        cout << "Rank: " << universityarr[row][0] << endl;
        cout << "Institution: " << universityarr[row][1] << endl;
        cout << "Location Code: " << universityarr[row][2] << endl;
        cout << "Location: " << universityarr[row][3] << endl;
        cout << "AR Score: " << universityarr[row][4] << endl;
        cout << "AR Rank: " << universityarr[row][5] << endl;
        cout << "ER Score: " << universityarr[row][6] << endl;
        cout << "ER Rank: " << universityarr[row][7] << endl;
        cout << "FSR Score: " << universityarr[row][8] << endl;
        cout << "FSR Rank: " << universityarr[row][9] << endl;
        cout << "CPF Score: " << universityarr[row][10] << endl;
        cout << "CPF Rank: " << universityarr[row][11] << endl;
        cout << "IFR Score: " << universityarr[row][12] << endl;
        cout << "IFR Rank: " << universityarr[row][13] << endl;
        cout << "ISR Score: " << universityarr[row][14] << endl;
        cout << "ISR Rank: " << universityarr[row][15] << endl;
        cout << "IRN Score: " << universityarr[row][16] << endl;
        cout << "IRN Rank: " << universityarr[row][17] << endl;
        cout << "GER Score: " << universityarr[row][18] << endl;
        cout << "GER Rank: " << universityarr[row][19] << endl;
        cout << "Score Scaled: " << universityarr[row][20] << endl;
        cout << endl << "----------------------------------------------" << endl;
    }
}

//"main" function here to initialize filename, rowcount,columncount AND to call the functions here for easier use in main.cpp
void University ::universityarray()
{

    UniversityColumns unidata[maxrow];
    const string filename = "2023_QS_World_University_Rankings.csv";
    int rowCount = 0;
    int columnCount = 0;
 

    readFile(filename, universityarr, rowCount, columnCount, unidata);
    //printuniarray(universityarr, rowCount);
}

void University :: printdash(){
    for (int i = 0; i < 235; i++) {
    cout << "-";
}
}

void University::displayUniversities()
{
    printheader();
    printdash();
    printuniarray(universityarr, maxrow);
    printdash();
}
