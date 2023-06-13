#ifndef CUS_H
#define CUS_H

// #include "User.h"

class Customer
{
private:
    string uname;
    string fullName;
    string gender;
    string email;
    string contact;

public:
    Customer(){};
    ~Customer(){};

    //password format: 1 Upper, 1 Lower, 1 Num, 1 Special Char; length >=8
    bool PassIsValid(string pass)
    {
        const regex pattern ("(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[@#$%^&+=])(?=\\S+$).{8,}");  
        return regex_match(pass,pattern);
    }
    
    //phone number format: (+60)xxxxxxxxx/xxxxxxxxxx
    bool ContactIsValid(string num)
    {
        const regex pattern("\\+?6?(?:01[0-46-9]\\d{7,8}|0\\d{8})");
        return regex_match(num,pattern);
    }

    //email format xxx@xxx.xxx
    bool EmailIsValid(string mail)
    {
        const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
        return regex_match(mail,pattern);
    }

    //check EmailIsValid and is there duplicate email found in the list 
    //ONE EMAIL ONE CUSTOMER
    bool checkEmail(string mail, CusList<string> &cLst)
    {
        if (EmailIsValid(mail) && cLst.checkInfo(mail)) {
            return 1;
        } else if (!EmailIsValid(mail)) {
            cout << "\n$!@#%& Your Email Format is Wrong &%#@!$" << endl;
            
            return 0;
        } else if (!cLst.checkInfo(mail)) {
            cout << "\n$!@#%& Email has been registered before &%#@!$" << endl;
            return 0;
        }
    }

    //register customer form 
    //can quit anytime while filling the info
    void regCus(UserList<string> &uLst,CusList<string> &cLst)
    {
        string unm, fnm, gdr, eml, con, pass;
        bool flag = true;

        cout << "\n Customer Registration Form:\n -----------------------------------------" << endl; 
        cout << " Enter 'Q' at any part in the form will lead to EXIT the registration process" <<endl;
        
        //username
        while (flag)
        {
            cout << "\n Username: ";    
            cin >> unm;
            if (unm == "Q" || unm == "q") {
                string a;
                cout << "\nATTENTION: Are you sure to QUIT register? (choose Y if yes): ";
                cin >> a;
                if (a == "Y" || a == "y") {
                    flag = false;
                }
            } else if (unm.length() >= 4) {
                if (!uLst.checkUsername(unm)) {
                    cout << "$!@#%& Someone has used this username already &%#@!$" << endl;
                } else {
                    break;
                }
            } else {
                cout << "$!@#%& Username must consist of at least 4 characters &%#@!$" << endl;
            }
            //check from List func is there duplicate username //must be more than 3 characters
        }

        //full name
        while (flag)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
            cout << "\n Full Name: " ;    
            getline(cin,fnm);
            if (fnm == "Q" || fnm == "q") {
                string a;
                cout << "\nATTENTION: Are you sure to QUIT register? (choose Y if yes): ";
                cin >> a;
                if (a == "Y" || a == "y") {
                    flag = false;
                }
            } else if (fnm.empty()) {
                cout << "$!@#%& Full name CANNOT left in blank &%#@!$" << endl;
            } else {
                break;
            }    
        }

        //gender
        while (flag)
        {
            string ans;
            cout << "\n Male (M) \t Female (F)"
                    "\n Select Your Gender (M/F): " ; //make option male and female only
            cin >> ans;
            if (ans == "Q" || ans == "q") {
                string a;
                cout << "\nATTENTION: Are you sure to QUIT register? (choose Y if yes): ";
                cin >> a;
                if (a == "Y" || a == "y") {
                    flag = false;
                }
            } else if (ans == "F" || ans == "f") {
                gdr = "Female";
                break;
            } else if (ans == "M" || ans == "m") {
                gdr = "Male";
                break;
            } else {
                cout << "\n$!@#%& Invalid Input (Please insert only \"F\" or \"M\" as stated) &%#@!$" << endl << endl;
            }
        }
        
        //email
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
        while (flag)
        {
            cout << "\n Email: ";    
            getline(cin,eml);
            if (eml == "Q" || eml == "q") {
                string a;
                cout << "\nATTENTION: Are you sure to QUIT register? (choose Y if yes): " ;
                cin >> a;
                if (a == "Y" || a == "y") {
                    flag = false;
                }
            } else if (checkEmail(eml, cLst)) {
                break;
            } 
        }

        //contact
        while (flag)
        {
            cout << "\n Contact: ";    
            getline(cin,con);
            if (con == "Q" || con == "q") {
                string a;
                cout << "\nATTENTION: Are you sure to QUIT register? (choose Y if yes): " ;
                cin >> a;
                if (a == "Y" || a == "y") {
                    flag = false;
                }
            } else if (ContactIsValid(con)) {
                break;
            } else {
                cout << "\n$!@#%& Your Contact is in Wrong Format &%#@!$" << endl;
            }
        }

        //PASSWORD
        while (flag)
        {
            string pass2;           
            cout << "\n New Password: ";    
            getline(cin,pass);
            if (pass == "Q" || pass == "q") {   //to quit from register
                string a;
                cout << "\nATTENTION: Are you sure to QUIT register? (choose Y if yes): " ;
                cin >> a;
                if (a == "Y" || a == "y") {
                    
                    flag = false;
                }
            } else if (PassIsValid(pass)) {     //password is strong enough
                cout << "\n Confirm New Password: ";    
                getline(cin,pass2);
                if (pass2 == "Q" || pass2 == "q") {
                    string a2;
                    cout << "\nATTENTION: Are you sure to QUIT register? (choose Y if yes): " ;
                    cin >> a2;
                    if (a2 == "Y" || a2 == "y") {    
                        flag = false;
                    } else {
                        cout << "$!@#%& Redirecting you to Enter New Password again &%#@!$" << endl;
                    }
                } else if (pass == pass2) {     //double confirm password success
                    break;
                } else {                        //fail to confirm password
                    cout << "\n$!@#%& Confirmation of Password is failed &%#@!$" << endl;
                    cout << "$!@#%& Redirecting you to Enter New Password again &%#@!$" << endl;
                }
            } else {                            //password is not strong enough
                cout << "\n$!@#%& \nYour Password must consist of at least 8 characters with "
                "\n1 Uppercase Letter, 1 Lowercase Letter, 1 Number and 1 Special Character(@#$%^&+=) without spaces \n&%#@!$" << endl;
            }
        }

        if (flag == true) {
            uLst.insertUser(unm,pass,"customer","");
            cLst.insertCus(unm,fnm,gdr,eml,con);
            cout << "\n-----------------------------------------\nRegister Successfully!\n-----------------------------------------" << endl;
            cLst.viewSingleCus(unm);
        } else {
            cout << "$!@#%& Redirecting you back to the Guest Menu &%#@!$" << endl;
        }
    }

    //modify email or contact
    bool modifyCus(string unm, string id, CusList<string> &cLst)
    {
        /* part 5: classCustomer -> check email or contact -> if yes: (CusList) update list; if not: LOOP BACK */                    
        string newData;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
        //EMAIL
        if (id == "1")
        {
            while (true)
            {
                cout << "\n Modify Step 3: New Email \n -----------------------------------------" ;
                cout << "\n (Enter 'B' to go back to last page)\n\nNew Email: ";
                cin >> newData;
                if (newData == "B" || newData == "b") {
                    string a;
                    cout << "\nATTENTION: Go back to Modify Step 1? (choose Y if yes): " ;
                    cin >> a;
                    if (a == "Y" || a == "y") {
                        cout << "\n**************************************************************************************************************************";
                        return true;   //back to modify menu
                    }
                } else if (checkEmail(newData,cLst)) {
                    /* part 6: CusList -> Update Data */
                    cLst.updateCus(unm,id,newData);
                    cout <<"\n-----------------------------------------\nEmail is updated successfully!\n-----------------------------------------" << endl;
                    return false;       //back to adminmenu
                } else {
                    cout << "$!@#%& Email remains unchanged; TRY AGAIN! &%#@!$" << endl; //Loop again
                }
            }    
        //CONTACT
        } else if (id == "2") {
            while (true)
            {
                cout << "\n Modify Step 3: New Contact \n -----------------------------------------" ;
                cout << "\n (Enter 'B' to go back to last page)\n\nNew Contact: ";
                cin >> newData;
                if (newData == "B" || newData == "b") {
                    string a;
                    cout << "\nATTENTION: Go back to Modify Step 1?  (choose Y if yes): " ;
                    cin >> a;
                    if (a == "Y" || a == "y") {
                        cout << "\n**************************************************************************************************************************";
                        return true;   //back to modifymenu
                    }
                } else if (ContactIsValid(newData)) {
        /* part 6: CusList -> Update Data */
                    cLst.updateCus(unm,id,newData);
                    cout <<"\n-----------------------------------------\nContact is updated successfully!\n------------------------------------------------" << endl; 
                    return false;       //back to guestmenu
                } else {
                    cout << "$!@#%& Contact remains unchanged; TRY AGAIN! &%#@!$" << endl; //Loop again
                }
            }    
        }
    }

};

#endif