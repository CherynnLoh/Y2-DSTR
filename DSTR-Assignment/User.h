#ifndef USER_H
#define USER_H

#include "Struct_FavUni.h"
#include "Cus.h"
#include "SearchUni.h"

class User
{
private:
    string uname;
    string pass;
    string logintime;
    string status;
    int role;

public:
    User(){};
    ~User(){};

    // login from guestmenu
    int login(UserList<string> &uLst)
    {
        string usrnm, pw, pw_check = "0";
        while (true)
        {
            cout << "\nLog In Page:\n-----------------------------------------\n(Enter 'Q' to quit)\n"
                 << endl;
            cout << "Username: ";
            cin >> usrnm;
            if (usrnm == "Q" || usrnm == "q")
            {
                break; // go back to guestmenu
            }
            else
            {
                pw_check = uLst.checkUser(usrnm); // to get the username's corresponding password from linkedlist
                if (pw_check == "0")
                {
                    continue;
                }
            }
            int count = 0;
            while (count < 3)
            {
                cout << "\nPassword: ";
                cin >> pw;
                if (pw == "Q" || pw == "q")
                {

                    break; // go back to guest menu
                    // return 0;
                }
                else
                {
                    if (pw == pw_check)
                    {
                        this->uname = usrnm;
                        this->pass = pw;
                        this->role = uLst.checkUserRole(usrnm, pw);
                        cout << "\n-----------------------------------------\nLog In Successfully!\n-----------------------------------------" << endl;
                        cout << "\n**************************************************************************************************************************";
                        time_t now = time(0);
                        char *dt = ctime(&now);
                        string timeNow = dt;
                        uLst.updateLoginTime(usrnm, timeNow);
                        return this->role;
                    }
                    else if (pw != pw_check)
                    {
                        cout << "\n$!@#%& Invalid Password &%#@!$" << endl;
                        if (count == 2)
                        {
                            cout << "\n$!@#%& You have reached the limit of trying the password (3 times)! &%#@!$" << endl;

                            break; // to quit login
                        }
                        count++;
                    }
                }
            }
            break;
        }
        cout << "\n**************************************************************************************************************************";
    }

    // Admin Menu: after log in with role admin
    void adminMenu(UserList<string> &uLst, CusList<string> &cLst, FeedbackList<string> &fbLst, FavUniList<string> &fuLst)
    {
        string chc;
        while (true)
        {
            cout << "\n Admin Menu List:\n -----------------------------------------"
                    "\n 1. View All Customer Details"
                    "\n 2. Update Customer Details"
                    "\n 3. Delete Inactive User Account"
                    "\n 4. Feedback"
                    "\n 5. Generate Report"
                    "\n 6. Log out"
                 << endl;
            cout << "\nEnter Your Choice: ";
            cin >> chc;
            cout << "\n**************************************************************************************************************************";

            // read admin menu choice
            if (chc == "1")
            {
                // to stay at customer details page or back to admin menu
                while (true)
                {
                    // show Customer Details
                    cLst.viewList();

                    // viewing options
                    string a;
                    cout << "View All User Credentials?(y) or Back to Menu? (b): ";
                    cin >> a;

                    // show All User Credentials
                    if (a == "Y" || a == "y")
                    {
                        uLst.viewList();

                        // to stay at credential page or back to customer details page
                        while (true)
                        {
                            string a1;
                            cout << "Back to View Customer Details? (b): ";
                            cin >> a1;
                            if (a1 != "B" && a1 != "b")
                            {
                                cout << "\n$!@#%& Please only type when you want to go back &%#@!$" << endl
                                     << endl;
                            }
                            else
                            {
                                cout << "\n**************************************************************************************************************************";
                                break;
                            }
                        }
                    }
                    // to stay at customer details page
                    else if (a == "B" || a == "b")
                    {
                        cout << "\n**************************************************************************************************************************";
                        break;
                    }
                    // to stay at customer details page
                    else
                    {
                        cout << "\n$!@#%& Please only type when you want to go back or proceed to view user credentials &%#@!$" << endl
                             << endl;
                    }
                }
            }
            else if (chc == "2")
            {
                bool flag = true; // flag to quit registering if == false
                cout << "\n Modify Customer Information \n -----------------------------------------";
                while (flag)
                {
                    /* part 1: AdminMenu -> get username */
                    string unm, opt;
                    cout << "\n Modify Step 1: Username\n -----------------------------------------"
                            "\n Enter 'Q' to quit modifying and go back to Admin Menu"
                         << endl;
                    cout << "\nCustomer's Username: ";
                    cin >> unm;

                    // back to ADMIN Menu
                    if (unm == "Q" || unm == "q")
                    {
                        string a;
                        cout << "\nATTENTION: Are you sure to QUIT modifying? (choose Y if yes): ";
                        cin >> a;
                        if (a == "Y" || a == "y")
                        {
                            break; // back to adminmenu
                        }
                        /* part 2: UserList -> check username -> if yes: (CusList) view the Cus Details; if not: LOOP BACK */
                    }
                    else if (!uLst.checkUsername(unm))
                    { // found username existed
                        // cLst.viewSingleCus(unm);
                        cout << "\n**************************************************************************************************************************";
                        /* part 3: AdminMenu -> choose to modify email or contact  */
                        while (true)
                        {
                            cLst.viewSingleCus(unm); // view customer details
                            cout << "\n Modify Step 2: Choose one to update\n -----------------------------------------"
                                    "\n Enter 'Q' to quit modifying and go back to Admin Menu\n"
                                    "\n 1. Email"
                                    "\n 2. Contact"
                                 << endl;
                            cout << "\nEnter Your Choice: ";
                            cin >> opt;
                            if (opt == "Q" || opt == "q")
                            { // go back to AdminMenu
                                string a1;
                                cout << "\nATTENTION: Are you sure to QUIT modifying? (choose Y if yes): ";
                                cin >> a1;
                                if (a1 == "Y" || a1 == "y")
                                {
                                    flag = false;
                                    break; // back to adminmenu
                                }
                            }
                            else if (opt != "1" && opt != "2")
                            { // Not choosing from options, loop asking option
                                cout << "\n$!@#%& Invalid Input (Please choose based on the number on menu) &%#@!$" << endl;
                                cout << "\n**************************************************************************************************************************";
                            }
                            else
                            { // Options Made
                                /* part 4: classCustomer -> input new email/contact */
                                cout << "\n**************************************************************************************************************************";
                                Customer cus;
                                flag = cus.modifyCus(unm, opt, cLst);
                                break;
                            }
                        }
                    }
                    else
                    { // username does not exist, loop asking username
                        cout << "\n$!@#%& Username does not exist. Try Again! &%#@!$" << endl;
                    }
                }
                cout << "\n**************************************************************************************************************************";
            }
            else if (chc == "3")
            {
                string unm;
                cout << "\n Delete User Based on Inactivity \n -----------------------------------------";
                while (true)
                {
                    // view User Activity Status (less than 5 mins last logged in == active)
                    uLst.viewStatus();
                    cout << " Deleting Part 1: Username To be Deleted \n -----------------------------------------"
                            "\n Enter 'Q' to quit deleting and go back to Admin Menu"
                            "\n\nCustomer's Username: ";
                    cin >> unm;
                    // BACK TO ADMIN MENU
                    if (unm == "Q" || unm == "q")
                    {
                        string a;
                        cout << "\nATTENTION: Are you sure to QUIT deleting accounts? (choose Y if yes): ";
                        cin >> a;
                        if (a == "Y" || a == "y")
                        {
                            break; // back to adminmenu
                        }
                    }
                    // ADMIN CANNOT BE DELETED
                    else if (unm == "admin")
                    {
                        cout << "\n**************************************************************************************************************************";
                        cout << "\n$!@#%& Admin account cannot be deleted. Try Again! &%#@!$" << endl;
                    }
                    // found username existed
                    else if (!uLst.checkUsername(unm))
                    {
                        cout << "\n**************************************************************************************************************************";
                        string a1;
                        cout << "\n Deleting Part 2: Confirmation to Delete \n -----------------------------------------" << endl;
                        cout << "ATTENTION: Confirm to delete user \"" << unm << "\"? (choose Y if yes): ";
                        cin >> a1;
                        if (a1 == "Y" || a1 == "y")
                        {
                            uLst.delUser(unm);
                            cLst.delCus(unm);
                            fbLst.delFeedback(unm);
                            fuLst.delFavUni(unm);
                            cout << "\n**************************************************************************************************************************";
                            cout << "\n-----------------------------------------\nSuccessfully deleted the user!\n-----------------------------------------" << endl;
                        }
                        else
                        {
                            cout << "\n**************************************************************************************************************************";
                            cout << "\n$!@#%& Failed to delete the user &%#@!$" << endl;
                            cout << "\n$!@#%& Redirecting you to the beginning of viewing user status &%#@!$" << endl;
                        }
                    }
                    // username does not exist, loop asking username
                    else
                    {
                        cout << "\n**************************************************************************************************************************";
                        cout << "\n$!@#%& Username does not exist. Try Again! &%#@!$" << endl;
                    }
                }
                cout << "\n**************************************************************************************************************************";
            }
            else if (chc == "4")
            {
                cout << "\n Customer's Feedback \n -----------------------------------------";
                int x = 1;
                char viewChoice = 'n';
                string viewingId = "0"; // view the latest ID first
                while (true && viewingId != "-1")
                {
                    // when first enter this option, 0 is to view the last node in linkedlist
                    if (viewingId == "0")
                    {
                        viewingId = fbLst.getFeedbackNow(viewingId, viewChoice);
                        if (viewingId == "-1")
                        {
                            break;
                        }
                        // while error occurs in below code, current node will be showed again
                    }
                    else if (x == 0)
                    {
                        fbLst.viewFeedbackNow(viewingId);
                        x = 1;
                    }

                    // enter feedback menu
                    cout << "\n Feedback Menu  \n -----------------------------------------"
                            "\n Previous: 'p' \tNext: 'n' "
                            "\n Reply: 'r' \tBack to Admin Menu: 'q' "
                            "\n\nEnter your choice(p/n/r/q): ";
                    cin >> viewChoice;
                    // to quit and back to adminmenu
                    if (viewChoice == 'Q' || viewChoice == 'q')
                    {
                        string a;
                        cout << "\nATTENTION: Are you sure to QUIT viewing feedback? (choose Y if yes): ";
                        cin >> a;
                        // double confirm to go back
                        if (a == "Y" || a == "y")
                        {
                            break; // back to adminmenu
                            // decided not to go back so this will loop again (try again)
                        }
                        else
                        {
                            cout << "\n**************************************************************************************************************************";
                            x = 0;
                        }
                        // to reply feedback (after replied it will loop again)
                    }
                    else if (viewChoice == 'R' || viewChoice == 'r')
                    {
                        cout << "\n**************************************************************************************************************************";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
                        fbLst.reply(viewingId);
                        x = 0;
                        // to view prev or the next node of the current showing node
                    }
                    else if (viewChoice == 'p' || viewChoice == 'n')
                    {
                        viewingId = fbLst.getFeedbackNow(viewingId, viewChoice);
                        cout << "\n**************************************************************************************************************************";
                        // invalid option is chosen from feedback menu (try again)
                    }
                    else
                    {
                        cout << "\n$!@#%& Invalid Input (Please choose based on the number on menu) &%#@!$" << endl;
                        cout << "\n**************************************************************************************************************************";
                        x = 0;
                    }
                }
                cout << "\n**************************************************************************************************************************";
            }
            else if (chc == "5")
            {
                fuLst.viewTop10();
                while (true)
                {
                    string a;
                    cout << "Back to Menu? (b): ";
                    cin >> a;
                    if (a != "B" && a != "b")
                    {
                        cout << "\n$!@#%& Please only type when you want to go back &%#@!$" << endl
                             << endl;
                    }
                    else
                    {
                        cout << "\n**************************************************************************************************************************";
                        break;
                    }
                }
            }
            else if (chc == "6")
            {
                string a;
                cout << "\nATTENTION: Are you sure to LOG OUT? (choose Y if yes): ";
                cin >> a;
                if (a == "Y" || a == "y")
                {
                    break; // log out
                }          // if not back to admin menu
            }
            else
            {
                cout << "\n**************************************************************************************************************************";
                cout << "\n$!@#%& Invalid Input (Please choose based on the number on menu) &%#@!$" << endl;
            }
        }
        cout << "\n**************************************************************************************************************************";
    }

    // Customer Menu: after log in with role customer
    void customerMenu(SearchUni &uni, FeedbackList<string> &fbLst, FavUniList<string> &fuLst)
    {
        string chc;
        while (true)
        {
            cout << "\n Customer Menu List:\n ----------------------------------"
                    "\n 1. Sort the Data"
                    "\n 2. Search University Details"
                    "\n 3. Save Favourite Univerisity"
                    "\n 4. Feedback"
                    "\n 5. Log Out"
                 << endl;
            cout << "\nEnter Your Choice: ";
            cin >> chc;
            cout << "\n**************************************************************************************************************************";
            if (chc == "1")
            {
                while (true)
                {
                    string start, end;

                    cout << "\n Sort By ..... in Descending Order"
                            "\n 1. ARS (Academic Reputation Score)"
                            "\n 2. FSR (Faculty/Student Ratio Score)"
                            "\n 3. ERS (Employer Reputation Score)"
                            "\n 4. Exit to Customer Main Menu"
                            "\n Enter an Option: ";
                    cin >> chc;

                    if (chc == "1")
                    {
                        while (true)
                        {
                            uni.userinput(start, end);
                            if (check_number(start, end))
                            {
                                int startrange = stoi(start);
                                int endrange = stoi(end);
                                uni.sortUniversityByARScore(startrange, endrange); // Print the sorted university data
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
                        while (true)
                        {
                            uni.userinput(start, end);
                            if (check_number(start, end))
                            {
                                int startrange = stoi(start);
                                int endrange = stoi(end);
                                uni.sortUniversityByFsrScore(startrange, endrange); // Print the sorted university data
                                break;
                            }
                            else
                            {
                                cout << "Invalid Input ! Please Enter a digit !" << endl;
                            }
                        }
                    }
                    else if (chc == "3")
                    {
                        while (true)
                        {
                            uni.userinput(start, end);
                            if (check_number(start, end))
                            {
                                int startrange = stoi(start);
                                int endrange = stoi(end);
                                uni.sortUniversityByErScore(startrange, endrange); // Print the sorted university data
                                break;
                            }
                            else
                            {
                                cout << "Invalid Input ! Please Enter a digit !" << endl;
                            }
                        }
                    }
                    else if (chc == "4")
                    {
                        break;
                    }
                    else
                    {
                        cout << "Invaild Input!" << endl;
                    }
                }
            }
            else if (chc == "2")
            {
                cout << "HI" << endl;
                while (true)
                {
                    string searchinput;
                    cout << "\n Search University Based on ...."
                            "\n 1. QS Rank"
                            "\n 2. Institution Name"
                            "\n 3. Location Code"
                            "\n 4. AR Rank (Academic Reputation)"
                            "\n 5. ER Rank (Employer Reputation)"
                            "\n 6. FSR Rank (Faculty / Student Ratio)"
                            "\n 7. CPF Rank (Citations per Faculty)"
                            "\n 8. IFR Rank (International Faculty Ratio)"
                            "\n 9. ISR Rank (International Student Ratio)"
                            "\n 10. IRN Rank (International Research Network)"
                            "\n 11. GER Rank (Employment Outcome)"
                            "\n 12. Exit to Customer Main Menu"
                            "\n Enter an Option: ";
                    cin >> chc;

                    if (chc == "1")
                    {
                        // The rank to search for
                        cout << "\nEnter Rank: ";
                        cin >> searchinput;
                        uni.linearRank(searchinput, "1");
                    }
                    else if (chc == "2")
                    {
                        cout << "\nEnter Institution Name: ";
                        cin >> searchinput;
                        uni.linearIns(searchinput, "1");
                    }
                    else if (chc == "3")
                    {
                        cout << "\nEnter Location Code: ";
                        cin >> searchinput;
                        uni.linearLC(searchinput);
                    }
                    else if (chc == "4")
                    {
                        cout << "\nEnter Ar Rank: ";
                        cin >> searchinput;
                        uni.linearArRank(searchinput);
                    }
                    else if (chc == "5")
                    {
                        cout << "\nEnter Er Rank: ";
                        cin >> searchinput;
                        uni.linearErRank(searchinput);
                    }
                    else if (chc == "6")
                    {
                        cout << "\nEnter Fsr Rank: ";
                        cin >> searchinput;
                        uni.linearFsrRank(searchinput);
                    }
                    else if (chc == "7")
                    {
                        cout << "\nEnter CPF Rank: ";
                        cin >> searchinput;
                        uni.linearCpfRank(searchinput);
                    }
                    else if (chc == "8")
                    {
                        cout << "\nEnter IFR Rank: ";
                        cin >> searchinput;
                        uni.linearIfrRank(searchinput);
                    }
                    else if (chc == "9")
                    {
                        cout << "\nEnter ISR Rank: ";
                        cin >> searchinput;
                        uni.linearIsrRank(searchinput);
                    }
                    else if (chc == "10")
                    {
                        cout << "\nEnter IRN Rank: ";
                        cin >> searchinput;
                        uni.linearIrnRank(searchinput);
                    }
                    else if (chc == "11")
                    {
                        cout << "\nEnter GER Rank: ";
                        cin >> searchinput;
                        uni.linearGerRank(searchinput);
                    }
                    else if (chc == "12")
                    {
                        break;
                    }
                    else
                    {
                        cout << "Invaild Input!" << endl;
                    }
                }
            }
            else if (chc == "3")
            {
                string univ, lc;
                int index;

                while (true)
                {
                    cout << "\nSave Favourite University\n----------------------------------"
                            "\n1. Save Favourite University"
                            "\n2. View Favourite University"
                            "\n3. Exit to Customer Main Menu\n"
                            "\nEnter an Option: ";

                    cin >> chc;

                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
                    if (chc == "1")
                    {
                        int number = 1;
                        while (number >= 1)
                        {
                            cout << "\nPlease Enter University Name (q to quit): ";
                            getline(cin, univ);

                            bool justString = isStringOnly(univ);
                            if (!justString)
                            {
                                cout << "Invalid Input! Please enter a valid university name." << endl;
                                continue;
                            }
                            else if (univ == "q" || univ == "Q")
                            {
                                break;
                            }

                            fbLst.validateInput(uni, univ, lc, index);

                            if (!univ.empty() && !lc.empty() && lc != " ")
                            {
                                // ssint index = uni.linearIns(univ, "0");
                                if (index >= 0)
                                {
                                    bool isSaved = fuLst.userSaveSameFav(this->uname, univ, lc);

                                    if (!isSaved)
                                    {
                                        fuLst.insertFav(this->uname, univ, lc);
                                        cout << "Your favourite university " << univ << " is successfully saved!" << endl;
                                        cout << "\n**************************************************************************************************************************";
                                    }
                                    else
                                    {
                                        cout << "\n$!@#%& REPEATED FAVOURITE UNIVERSITY &%#@!$" << endl;
                                    }

                                    string a1;
                                    cout << "\nSaving another Favourite University? (Enter Y if yes, Other key to quit): ";
                                    cin >> a1;
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer

                                    if (a1 != "Y" && a1 != "y")
                                    {
                                        cout << "Redirecting back to Save University Menu\n"; // Return to Save University Menu if the user doesn't want to save another favourite university
                                        break;
                                    }
                                }
                            }
                            else if (lc == " ")
                            {
                                number = 0;
                            }
                            else
                            {
                                break;
                            }
                        }
                    }

                    else if (chc == "2")
                    {
                        fuLst.viewbyCus(this->uname);
                    }
                    else if (chc == "3")
                    {
                        break;
                    }
                    else
                    {
                        cout << "Invalid Input! Redirecting back to Save Unviersity Menu";
                    }
                }
            }

            else if (chc == "4")
            {
                string choice;
                int index;
                while (true)
                {
                    // feedback menu for cus
                    cout << "\n Feedback Menu \n ----------------------------------"
                            "\n1. Give Feedback"
                            "\n2. View Reply"
                            "\n3. Exit to Customer Menu "
                            "\n\nEnter choice: ";
                    cin >> choice;
                    // to create new feedback
                    if (choice == "1")
                    {
                        string univ, fb, lc; // fb = feedback, lc = location code
                        // search the uni name and location code from array (MODIFY PART 1)
                        while (true)
                        {
                            cout << "\nPlease Enter University Name (q to quit): ";
                            cin >> univ;
                            bool juststring = isStringOnly(univ);
                            if (univ == "q" || univ == "Q")
                            {
                                break;
                            }
                            else if (juststring)
                            {

                                fbLst.validateInput(uni, univ, lc, index);

                                if (!univ.empty() && !lc.empty() && lc != " ")
                                {
                                    bool isDuplicate = fbLst.checkUni(univ, lc, this->uname);

                                    if (isDuplicate)
                                    {
                                        while (true)
                                        {
                                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
                                            cout << "\nEnter Feedback for " << univ << " :";
                                            getline(cin, fb);

                                            // Validate feedback length
                                            if (fb.empty())
                                            {
                                                cout << "Error: Feedback cannot be empty." << endl;
                                                continue; // Restart the loop to re-prompt for valid input
                                            }

                                            // Count the number of words in the feedback
                                            int wordCount = 0;
                                            for (char c : fb)
                                            {
                                                if (c == ' ')
                                                {
                                                    wordCount++;
                                                }
                                            }
                                            wordCount++; // Increment by 1 for the last word

                                            // Validate word count
                                            if (wordCount <= 5)
                                            {
                                                cout << "Error: Feedback should have more than 5 words." << endl;
                                                continue; // Restart the loop to re-prompt for valid input
                                            }
                                            else
                                            {
                                                fbLst.insertFeedback(this->uname, univ, fb, lc);
                                                cout << "Feedback for " << univ << " Successsfully Sent!" << endl;
                                                break;
                                            }
                                        }
                                        break;
                                    }

                                    else
                                    {
                                        cout << "\nYou decided not to give feedback.";
                                        cout << "\n$!@#%& Redirecting you to the Customer menu &%#@!$" << endl;
                                        break;
                                    }
                                }
                                else if (lc == " ")
                                {
                                    // break;
                                }
                                else
                                {
                                    // cout << "\nRedirecting you to the Feedback menu..." << endl;
                                    //  break;
                                }
                            }

                            else
                            {
                                cout << "Invalid Input!";
                            }
                        }
                    }

                    // to view feedback history and check reply from admin
                    else if (choice == "2")
                    {

                        cout << "\n View Feedback \n ----------------------------------";
                        int x = 1;
                        char viewChoice = 'n';
                        string viewingId = "0"; // view the latest first
                        // check if the user has made at least one feedback before
                        if (fbLst.checkUser(this->uname))
                        {
                            while (true && viewingId != "-1")
                            {
                                // to view the latest feedback made by the user (view with prev/next option)
                                if (viewingId == "0")
                                {
                                    viewingId = fbLst.getcusFeedback(viewingId, this->uname, viewChoice);
                                }
                                // when error occurs, the current node will be displayed again
                                else if (x == 0)
                                {
                                    fbLst.viewCusFeedback(viewingId);
                                    x = 1;
                                }
                                // customer feedback menu
                                cout << "\nView Feedback Menu  \n----------------------------------"
                                        "\n Previous: 'p' \tNext: 'n' "
                                        "Back to the Main Feedback Menu: 'b' "
                                        "\n\n Enter your choice(p/n/b): ";
                                cin >> viewChoice;
                                //
                                if (viewChoice == 'B' || viewChoice == 'b')
                                {
                                    string a;
                                    cout << "\nATTENTION: Are you sure to QUIT viewing feedback? (choose Y if yes): ";
                                    cin >> a;
                                    if (a == "Y" || a == "y")
                                    {
                                        break; // back to feedback menu
                                    }
                                    else
                                    {
                                        cout << "\n**************************************************************************************************************************";
                                        x = 0;
                                    }
                                }
                                // view previous or next node
                                else if (viewChoice == 'p' || viewChoice == 'n')
                                {
                                    viewingId = fbLst.getcusFeedback(viewingId, this->uname, viewChoice);
                                    cout << "\n**************************************************************************************************************************";
                                }
                                // invalid menu choice
                                else
                                {
                                    cout << "\n$!@#%& Invalid Input (Please choose based on the number on menu) &%#@!$" << endl;
                                    cout << "\n**************************************************************************************************************************";
                                    x = 0;
                                }
                            }
                        }
                        // no feedback has been made before
                        else
                        {
                            continue;
                        }
                    }
                    // invalid menu choice //MODIFY PART 2
                    else if (choice == "3")
                    {
                        break;
                    }
                    else
                    {
                        cout << "Invalid Menu Option..Redirecting back to Feedback Menu" << endl;
                    }
                }
            }
            else if (chc == "5")
            {
                string a;
                cout << "\nATTENTION: Are you sure to LOG OUT? (choose Y if yes): ";
                cin >> a;
                if (a == "Y" || a == "y")
                {
                    break; // log out
                }          // if not back to cus menu
            }
            else
            {
                cout << "\n$!@#%& Invalid Input (Please choose based on the number on menu) &%#@!$" << endl;
            }
        }
    }
    // used in the options in customer menu to validate the input is a string when asked for university name (save fav and feedback to uni)
    static bool isStringOnly(const string &input)
    {
        for (char c : input)
        {
            if (isdigit(c))
            {
                return false; // Contains numeric characters
            }
        }
        return true; // String only
    }

    // to validate the input of Selection Sort - Guest Menu
    bool check_number(string str, string str2)
    {
        for (int i = 0; i < str.length(); i++)
            if (isdigit(str[i]) == false || isdigit(str2[i]) == false)
                return false;
        return true;
    }

    // to validate the input of Binary Search Algorithm - Guest Menu
    bool check_number2(string str)
    {
        for (int i = 0; i < str.length(); i++)
            if (isdigit(str[i]) == false)
                return false;
        return true;
    }
};

#endif