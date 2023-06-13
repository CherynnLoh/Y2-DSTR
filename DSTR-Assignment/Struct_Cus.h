#ifndef STRUCT1_H
#define STRUCT1_H

#include "Struct_User.h"

template <class C> 
struct CusNode
{
    C username;
    C fullName;
    C gender;
    C email;
    C contact;

    CusNode<C> *prev;
    CusNode<C> *next;
};

template <class C> 
struct CusList
{
    CusNode<C> *head;
    CusNode<C> *tail;
    int size;

    CusList()
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }

    void insertCus(C un,C fn, C gd,C em,C ct)
    {
        CusNode<C> *n = new CusNode<C>;
        n->username = un;
        n->fullName = fn;
        n->gender = gd;
        n->email = em;
        n->contact = ct;

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

    //in delCus
    void deleteFirst()
    {
        if (size > 0)
        {
            CusNode<C> *DEL = head;
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

    //in delCus
    void deleteLast()
    {
        if (size > 0)
        {
            CusNode<C> *DEL = tail;
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

    //delete customer from the list
    void delCus(string un)
    {
        if (size > 0)
        {
            if(head->username == un) {
                deleteFirst();
            } else if (tail->username == un) {
                deleteLast();
            } else {
                CusNode<C> *DEL = head->next;
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

    //for admin to view all customer details
    void viewList()
    {
        CusNode<C> *curr = head;
        cout << "\n****************************************** DISPLAY ALL Customers ( " << size << " elements) ******************************************\n" << endl;
        cout << left << setw(16) << "Username" << setw(8) << "|" << setw(25) << "Full Name" << setw(6) << "|" << setw(10) << "Gender" << setw(10) << "|" 
            << setw(25) << "Email" << setw(8) << "|" << setw(16) << "Contact" << endl;
        cout << "-------------------------------------------------------------------------------------------------------------------------" << endl; 
        while (curr != nullptr)
        {
            cout << left << setw(16) << curr->username << setw(3) << "|" << setw(30) << curr->fullName << setw(5) << "|" << setw(11) << curr->gender << setw(7) << "|" 
            << setw(28) << curr->email << setw(4) << "|" << setw(20) << curr->contact << endl ;
            cout << "-------------------------------------------------------------------------------------------------------------------------" << endl; 
            curr = curr->next;
        }
        cout << "\n**************************************************** END OF DISPLAYING ***************************************************" << endl << endl;
    }

    //check no duplicate email while register new account or modify info
    bool checkInfo(string eml)
    {
        CusNode<C> *curr = head;
        while (curr != nullptr)
        { //check email
            if (curr->email == eml) {
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

    //show the customer latest details after updated
    void viewSingleCus(string unm)
    {
        CusNode<C> *curr = head;
        while (curr != nullptr)
        { //search the customer node
            if (curr->username == unm) {
                cout << "\nCustomer Information: " << endl;
                cout << "-------------------------------------------------------------------------------------------------------------------------" << endl; 
                cout << left << setw(16) << "Username" << setw(8) << "|" << setw(25) << "Full Name" << setw(6) << "|" << setw(10) << "Gender" << setw(10) << "|" 
                    << setw(25) << "Email" << setw(8) << "|" << setw(16) << "Contact" << endl;
                cout << "-------------------------------------------------------------------------------------------------------------------------" << endl; 
                cout << left << setw(16) << curr->username << setw(3) << "|" << setw(30) << curr->fullName << setw(5) << "|" << setw(11) << curr->gender << setw(7) << "|" 
                << setw(28) << curr->email << setw(4) << "|" << setw(20) << curr->contact << endl ;
                cout << "-------------------------------------------------------------------------------------------------------------------------" << endl; 
                // cout << curr->username << "||" << curr->fullName << "||" << curr->gender 
                // << "||" << curr->email << "||" << curr->contact << endl << endl;
                break;
            } else {
                curr = curr->next;
            } 
        }
    }

    //update the customer details in the linkedlist (email/contact)
    void updateCus(string unm, string id, string newData)
    {
        //search the customer node
        CusNode<C> *curr = head;
        while (curr != nullptr)
        { 
            if (curr->username == unm) { 
                break;
            } else {
                curr = curr->next;
            } 
        }
        /* update email/contact */
        if (id == "1") {
            curr->email = newData;
        } else {
            curr->contact = newData;   
        }
        viewSingleCus(unm);
    }
};

#endif