#ifndef STRUCT_H
#define STRUCT_H

#include <iostream>
#include <limits>
#include <regex>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

template <class U> 
struct UserNode
{
    U username;
    U password;
    U role;
    U logintime;
    UserNode<U> *prev;
    UserNode<U> *next;
};

template <class U> 
struct UserList
{
    UserNode<U> *head;
    UserNode<U> *tail;
    int size;

    UserList()
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }

    void insertUser(U u,U p, U r,U t)
    {
        UserNode<U> *n = new UserNode<U>;
        n->username = u;
        n->password = p;
        n->role = r;
        n->logintime = t;

        n->next = nullptr;
        n->prev = tail;
        tail = n;
        if (head == nullptr) { 
            head = n;
        } else {
            n->prev->next = n;
        }
        size ++;  
    }

    //used in delUser
    void deleteFirst()
    {
        if (size > 0)
        {
            UserNode<U> *DEL = head;
            if (head->next != nullptr) {
                head->next->prev = NULL;
                head = head->next;
            } else {
                head = NULL;
                tail = NULL;
            }
            delete DEL;
            size--;
        }
    }

    //used in delUser
    void deleteLast()
    {
        if (size > 0)
        {
            UserNode<U> *DEL = tail;
            if (tail->prev != nullptr) {
                tail->prev->next = NULL;
                tail = tail->prev;
            } else {
                tail = NULL;
                head = NULL;
            }
            delete DEL;
            size--;
        }
    }

    void delUser(string un)
    {
        if (size > 0)
        {
            if(head->username == un) {
                deleteFirst();
            } else if (tail->username == un) {
                deleteLast();
            } else {
                UserNode<U> *DEL = head->next;
                while (DEL != nullptr)
                {
                    if (DEL->username == un)
                    {
                        DEL->prev->next = DEL->next;
                        if (DEL->next != nullptr) {
                            DEL->next->prev = DEL->prev;
                        }
                        delete DEL;
                        size--;
                        return; // Exit the function after deleting the node
                    }
                    DEL = DEL->next;
                }
            }
        }
    }

    //make it from string to time, to compare with the time now    
    time_t convertStringToTime(const string& str) {
        tm timeStruct = {};  // Initialize with zeros to avoid undefined behavior
        istringstream ss(str);

        // Parse the string and extract its components
        ss >> get_time(&timeStruct, "%a %b %d %H:%M:%S %Y");

        // Check if the parsing was successful
        if (ss.fail()) {
            // Handle error
            throw runtime_error("Invalid time format: " + str);
        }

        // Convert the tm structure to time_t
        time_t timeValue = mktime(&timeStruct);

        // Check if the conversion was successful
        if (timeValue == -1) {
            // Handle error
            throw runtime_error("Failed to convert string to time_t: " + str);
        }

        return timeValue;
    }

    //to view all the user credentials
    void viewList()
    {
        UserNode<U> *curr = head;
        cout << "\n*********************** DISPLAY ALL USERS ( " << size << " elements) ***********************\n" << endl;
        cout << left << setw(20) << "Username" << setw(10) << "|" << setw(20) << "Password" << setw(9) << "|" << setw(10) << "Role" << endl;
        cout << "-------------------------------------------------------------------------------" << endl; 
        while (curr != nullptr)
        {
            cout << left << setw(20) << curr->username << setw(5)  << "|" << setw(25) << curr->password << setw(9) << "|" << setw(10) << curr->role << endl;
            cout << "-------------------------------------------------------------------------------" << endl; 
            curr = curr->next;
        }
        cout << "*******************************END OF DISPLAYING*******************************" << endl << endl;
    }

    //before deleting user, theeir activity status will be viewed
    void viewStatus()
    {
        UserNode<U> *curr = head;
        cout << "\n********************** User Activity Status ( " << size << " elements) *********************\n" << endl;
        cout << left << setw(20) << "Username" << setw(7) << "|" << setw(35) << "Last Login Date & Time" << setw(4) << "|" << setw(13) << "Status" << endl;
        cout << "-------------------------------------------------------------------------------" << endl; 
        time_t now = time(0);
        char *dt = ctime(&now);
        string timeNow = dt;

        time_t lastlogin;
        time_t duration;
        string status;
        
        while (curr != nullptr)
        {
            if (curr->logintime == "") {
                status = "Inactive";
            } else {
                lastlogin = convertStringToTime(curr->logintime);
                duration = now - lastlogin;
                if (duration < 300) {
                    status = "Active";
                } else {
                    status = "Inactive";
                }
            }
            cout << left << setw(20) << curr->username << setw(7) << "|" << setw(35) << curr->logintime << setw(4) << "|" << setw(13) << status << endl;
            cout << "-------------------------------------------------------------------------------" << endl; 
            curr = curr->next;
        }
        cout << "*******************************END OF DISPLAYING*******************************" << endl << endl;
    }

    //for login: authentication
    string checkUser(U nm)  
    {
        UserNode<U> *curr = head;
        while (curr != nullptr)
        {
            if (curr->username == nm)
            {
                break;
            }
            else
            {
                curr = curr->next;
            }
        }
        if (curr == nullptr) {
            cout << "\n$!@#%& Invalid User &%#@!$" << endl;
            return "0";
        } else {
            return curr->password;
        }
    }

    //for login: authorization
    int checkUserRole(U nm, U pw)   
    {
        UserNode<U> *curr = head;
        while (curr != nullptr)
        {
            if (curr->username == nm && curr->password == pw) {
                break;
            } else {
                curr = curr->next;
            }
        }
        if (curr->role == "admin") {
            return 1;
        } else if (curr->role == "customer") {
            return 2;   //registered user
        }
    }

    //for register: check is there same username storing in data
    bool checkUsername(string un)       
    {
        UserNode<U> *curr = head;
        while (curr != nullptr)
        {
            if (curr->username == un) {
                break;
            } else {
                curr = curr->next;
            }
        }
        if (curr == nullptr) { //no duplicate info
            return 1;
        } else {
            return 0;
        }
    }   

    //remove the spaces behind the logintime string
    string removeTrailingWhitespace(const string& str) {
        string result = str;
        size_t end = result.find_last_not_of(" \t\n\r");
        
        if (end != string::npos) {
            result.erase(end + 1);
        }
        
        return result;
    }

    void updateLoginTime(string un, string t)
    {
        UserNode<U> *curr = head;
        t = removeTrailingWhitespace(t);
        while (curr != nullptr)
        {
            if (curr->username == un) {
                break;
            } else {
                curr = curr->next;
            }
        }
        curr->logintime = t;
    }
};

#endif