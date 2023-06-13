#ifndef STRUCT3_H
#define STRUCT3_H

#include "Struct_Feedback.h"
using namespace std;

template <class S> 
struct FavUniNode
{
    S username;
    S favuni;
    S locationcode;
    int total;
    FavUniNode<S> *prev;
    FavUniNode<S> *next;
};

template <class S> 
struct FavUniList
{
    FavUniNode<S> *head;
    FavUniNode<S> *tail;
    int size;

    FavUniList()
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }
    
    //everytime insertion is made, the total occurrence time will be checked
    //nm: username, uni: university name, lc: location code
    void insertFav(S nm, S uni, S lc)
    {
        FavUniNode<S> *n = new FavUniNode<S>;
        n->username = nm;
        n->favuni= uni;
        n->locationcode = lc;

        //count repeat times of uni in the fav list
        updateRepeatTimes(uni,lc);
        n->total = getUniRepeatTimes(uni,lc);

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

    //in delFavUni
    void deleteFirst()
    {
        if (size > 0)
        {
            FavUniNode<S> *DEL = head;
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

    //in delFavUni
    void deleteLast()
    {
        if (size > 0)
        {
            FavUniNode<S> *DEL = tail;
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

    //delete all fav uni record made by the user when the user account is being deleted
    void delFavUni(S un)
    {
        if (size > 0)
        {
            while (head != nullptr && head->username == un)
            {
                deleteFirst();
            }
            
            FavUniNode<S> *DEL = head;
            while (DEL != nullptr && DEL->next != nullptr)
            {
                if (DEL->next->username == un)
                {
                    FavUniNode<S> *temp = DEL->next;
                    DEL->next = temp->next;
                    if (temp->next != nullptr)
                    {
                        temp->next->prev = DEL;
                    }
                    delete temp;
                    size--;
                }
                else
                {
                    DEL = DEL->next;
                }
            }
        }
    }

    //check uni times appeared in list and then + 1
    int getUniRepeatTimes(S uni, S lc) 
    {  
        FavUniNode<S> *curr = head;
        int rpt = 1;
        if (head != nullptr) {
            while (curr != nullptr) 
            {
                if (curr->favuni == uni && curr->locationcode == lc) {
                    rpt += 1;
                }
                curr = curr->next;
            }
        } else {
            rpt = 1;
        }
        return rpt;
    }

    //update the uni's total appear time if it is repeated
    void updateRepeatTimes(S uni, S lc) 
    {
        FavUniNode<S> *curr = head;
        int rpt = getUniRepeatTimes(uni, lc);
        while (curr != nullptr) 
        {
            if (curr->favuni == uni && curr->locationcode == lc) {
                curr->total = rpt;
            }
            curr = curr->next;
        }
    }

    //check whether the user has saved before the uni as fav already
    bool userSaveSameFav(S un, S uni, S lc) 
    {
        FavUniNode<S> *curr = head;
        if (head != nullptr) {
            while (curr != nullptr) 
            {
                if (curr->username == un && curr->favuni == uni && curr->locationcode == lc) {
                    break;   
                }
                curr = curr->next;
            }
        } else {
            return 0;   //no data before yet, sure no repeating
        }

        if (curr == nullptr) {
            return 0;   //didn't find same uni name under the user
        } else {
            return 1;   //user cannot save a uni as fav TWICE
        }
    }

    //view all fav universities record
    void viewList() 
    {
        FavUniNode<S> *curr = head;

        cout << "\n********************************* Favourite University List ( " << size << " elements) **********************************\n" << endl;    
        cout << left << setw(16) << "Username" << setw(3) << "|" << setw(15) << "Location Code" 
            << setw(5) << "|" << setw(45) << "University Name"  << setw(5) << "|" << setw(6) << "Occurrences(Uni)"  << setw(10)  <<endl;
        cout << "------------------------------------------------------------------------------------------------------------" << endl; 
        while (curr != nullptr)
        {
            cout << left << setw(16) << curr->username << setw(3) << "|" << setw(15) << curr->locationcode 
            << setw(5) << "|" << setw(45) << curr->favuni  << setw(5) << "|" << setw(6) << curr->total << setw(10)  <<endl;
            cout << "------------------------------------------------------------------------------------------------------------" << endl; 
            curr = curr->next;
        }
        cout << "**********************************************END OF DISPLAYING*********************************************" << endl << endl;
    }

    //customer view their fav uni history
    void viewbyCus(S un)
    {
        FavUniNode<S> *curr = head;

        cout << "\n*********************************** Favourite University List ************************************\n" << endl;           
        cout << left << setw(15) << "Location Code" << setw(5) << "|" << setw(55) 
            << "University Name"  << setw(5) << "|" << setw(6) << "Occurrences(Uni)"  << setw(10)  <<endl;
        cout << "--------------------------------------------------------------------------------------------------" << endl; 
        while (curr != nullptr)
        {
            if (curr->username == un) {
                cout << left << setw(15) << curr->locationcode << setw(5) << "|" << setw(55) 
                    << curr->favuni  << setw(5) << "|" << setw(6) << curr->total << setw(10)  <<endl;
                cout << "--------------------------------------------------------------------------------------------------" << endl; 
            }
            curr = curr->next;
        }
        cout << "******************************************END OF DISPLAYING***************************************" << endl << endl;
    }

    //print top 10 fav uni report
    void viewTop10() {
        FavUniNode<S>* curr = head;
        FavUniNode<S>* highestNode = nullptr;
        string uni[10];
        string code [10];
        //array<string, 10> uni;
        int total;

        // Find the node with the highest total
        while (curr != nullptr) {
            if (highestNode == nullptr || curr->total > highestNode->total) {
                highestNode = curr;
            }
            curr = curr->next;
        }

        cout << "\n********************************** TOP 10 Favourite University Report ********************************\n" << endl;    
        cout << left << setw(4) << "NO" << setw(3) << "|" << setw(15) << "Location Code" 
            << setw(5) << "|" << setw(55) << "University Name"  << setw(3) << "|" << setw(6) << "Total Occurrences"  << setw(6)  <<endl;
        cout << "------------------------------------------------------------------------------------------------------" << endl; 

        // Print the top 10 occurrences
        for (int i = 0; i < 10 && highestNode != nullptr; i++) {
            cout << left << setw(4) << i+1 << setw(3) << "|" << setw(15) << highestNode->locationcode
                << setw(5) << "|" << setw(55) << highestNode->favuni  << setw(6) << "|" << setw(6) << highestNode->total << setw(6)  <<endl;
            cout << "------------------------------------------------------------------------------------------------------" << endl;  
            //cout << "FavUni: " << highestNode->favuni << ", Total: " << highestNode->total << endl;

            uni[i] = highestNode->favuni;   //4: Sunway,3; 5: Monash,3
            code[i] = highestNode->locationcode;
            total = highestNode->total;

            // Find the next highest node
            curr = head;
            highestNode = nullptr;
            while (curr != nullptr) {
                if ((highestNode == nullptr || curr->total > highestNode->total) && curr->total <= total) {
                    for (int j = 0; j < i+1; j++) {  //j<6
                        if (curr->favuni == uni[j] && curr->locationcode == code[j]) {
                            break;
                        } else if ((curr->favuni != uni[j] || curr->locationcode != code[j]) && j == i) {
                            highestNode = curr;
                        }   
                    }
                }
                curr = curr->next;
            }
        }
        cout << "\n******************************************** END OF Report *******************************************\n" << endl;
    }
};

#endif