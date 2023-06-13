#include <iostream>
#include "User.h"
#include "Cus.h"
#include "SearchUni.h"

using namespace std;

int main()
{
    UserList<string> *UL1 = new UserList<string>;
    CusList<string> *CL1 = new CusList<string>;
    FeedbackList<string> *FBL1 = new FeedbackList<string>;
    FavUniList<string> *FUL1 = new FavUniList<string>;
    User u1;

    UL1->insertUser("admin", "Admin#12", "admin", ""); // INSERT ADMIN DATA INTO USER LINKED LIST
    CL1->insertCus("wnqyu", "Wan Ning", "Female", "wanni123@gmail.com", "0125673245");
    UL1->insertUser("wnqyu", "Wn@12345", "customer", "");

    cout << "**************************************************************************************************************************"
            "\n******************************************** University Recommendation System ********************************************"
            "\n\n**************************************************************************************************************************";
    while (true)
    {
        User users;
        SearchUni uni;
        uni.universityarray();

        string chc, starting, end;
        cout << "\n Guest Menu List:\n -----------------------------------------"
                "\n 1. Login"
                "\n 2. View Univeristies"
                "\n 3. Sort University Information By Institution Ascendingly"
                "\n 4. Search University Details By Rank"
                "\n 5. Register as Customer"
                "\n ** Enter any other keys will quit the program"
             << endl;
        cout << "\nEnter Your Choice: ";
        cin >> chc;
        cout << "\n**************************************************************************************************************************";
        if (chc == "1")
        {
            int l = u1.login(*UL1);
            if (l == 1)
            {
                Customer c1;
                u1.adminMenu(*UL1, *CL1, *FBL1, *FUL1);
            }
            else if (l == 2)
            {
                Customer c1;
                u1.customerMenu(uni, *FBL1, *FUL1);
            }
        }
        else if (chc == "2")
        {
            cout << "\nView Universities Function" << endl;
            uni.displayUniversities();
        }
        else if (chc == "3")
        {
            while (true)
            {
                cout << "\nSort Universities Menu"
                        "\n1. Selection Sort "
                        "\n2. Quick Sort"
                        "\n3. Exit to Main Menu"
                        "\nSelect an Option: ";
                cin >> chc;

                if (chc == "1")
                {
                    // Selection Sort
                    while (true)
                    {
                        cout << "Please Enter a Start Range (0-1421): ";
                        cin >> starting;
                        cout << "Please Enter a End Range (0-1421): ";
                        cin >> end;
                        if (users.check_number(starting, end))
                        {
                            int startrange = stoi(starting);
                            int endrange = stoi(end);
                            uni.sortUniversityByInst(startrange, endrange);
                            break;
                        }
                        else
                        {
                            cout << "Invalid Input ! Please Enter a digit !" << endl;
                        }
                    }
                }
                else if (chc == "2")
                {
                    // Quick Sort
                    while (true)
                    {
                        cout << "Please Enter a Start Range (0-1421): ";
                        cin >> starting;
                        cout << "Please Enter a End Range (0-1421): ";
                        cin >> end;

                        if (users.check_number(starting, end))
                        {
                            int startrange = stoi(starting);
                            int endrange = stoi(end);
                            uni.sortUniversityByIns(startrange, endrange);
                            break;
                        }
                        else
                        {
                            cout << "Invalid Input !!!" << endl;
                        }
                    }
                }
                else if (chc == "3")
                {
                    break;
                }
                else
                {
                    cout << "Invalid Input! Redirecting back to Sort Universities Menu" << endl;
                }
            }
        }
        else if (chc == "4")
        {
            while (true)
            {
                cout << "\nSearch Universities Menu"
                        "\n---------------------------"
                        "\n1. Linear Search "
                        "\n2. Binary Search"
                        "\n3. Exit to Main Menu"
                        "\nSelect an Option: ";
                cin >> chc;
                if (chc == "1")
                {
                    cout << "\nLinear Search for University"
                            "\n-----------------------------";
                    cout << "\nEnter a University Rank: ";
                    string Rank;
                    cin >> Rank;

                    uni.linearRank(Rank,"0");
                }
                else if (chc == "2")
                {
                    while (true)
                    {
                        cout << "\nBinary Search for University"
                                "\n-----------------------------";
                        cout << "\nEnter a University Rank: ";
                        string Rank;
                        cin >> Rank;

                        if (users.check_number2(Rank))
                        {
                            uni.binarySearchByRank(Rank);
                            break;
                        }
                        else
                        {
                            cout << "Invalid Input" << endl;
                        }
                    }
                }
                else if (chc == "3")
                {
                    break;
                }
                else
                {
                    cout << "Invalid Input! Redirecting back to Search Universities Menu" << endl;
                }
            }
        }
        else if (chc == "5")
        {
            Customer c1;
            c1.regCus(*UL1, *CL1);
        }
        else
        {
            string a;
            cout << "\nATTENTION: Are you sure to QUIT the program? (choose Y if yes): ";
            cin >> a;
            if (a == "Y" || a == "y")
            {
                break;
            }
        }
    }

    cout << "****************************************************END OF THE PROGRAM****************************************************" << endl
         << endl;
    return 0;
}


