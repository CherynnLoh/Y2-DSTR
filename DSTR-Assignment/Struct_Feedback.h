#ifndef STRUCT2_H
#define STRUCT2_H

#include "Struct_Cus.h"
#include "SearchUni.h"

template <class F>
struct FeedbackNode
{
    F id;
    F username;
    F university;
    F locationcode;
    F feedback;
    F reply;
    F fbDate;
    FeedbackNode<F> *prev;
    FeedbackNode<F> *next;
};

template <class F>
struct FeedbackList
{
    FeedbackNode<F> *head;
    FeedbackNode<F> *tail;
    int size;

    FeedbackList()
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }

    // get the last ID in from the list
    string getLastID()
    {
        return tail->id;
    }

    // id will be generated; reply is empty when feedback is inserted; date will be get here
    // nm: username, u: universityname, f: feedback, l: location code
    void insertFeedback(F nm, F u, F f, F l)
    {
        FeedbackNode<F> *n = new FeedbackNode<F>;

        // ID GENERATOR
        if (head == nullptr)
        {
            n->id = "1";
        }
        else
        {
            int num = stoi(getLastID()) + 1;
            n->id = to_string(num);
        }

        // GET TIME NOW
        time_t now = time(0);
        char *dt = ctime(&now);
        string timeNow = dt;

        n->username = nm;
        n->university = u;
        n->locationcode = l;
        n->feedback = f;
        n->reply = "";
        n->fbDate = timeNow;

        n->next = nullptr;
        n->prev = tail;
        tail = n;
        if (head == nullptr)
        {
            head = n;
        }
        else
        {
            n->prev->next = n;
        }
        size++;
    }

    void deleteFirst()
    {
        if (size > 0)
        {
            FeedbackNode<F> *DEL = head;
            if (head->next != nullptr)
            {
                head->next->prev = NULL;
                head = head->next;
            }
            else
            {
                head = NULL;
                tail = NULL;
            }
            delete DEL;
            size--;
        }
    }

    void deleteLast()
    {
        if (size > 0)
        {
            FeedbackNode<F> *DEL = tail;
            if (tail->prev != nullptr)
            {
                tail->prev->next = NULL;
                tail = tail->prev;
            }
            else
            {
                tail = NULL;
                head = NULL;
            }
            delete DEL;
            size--;
        }
    }

    // delete all feedbacks from the user after deleting the user
    void delFeedback(string un)
    {
        if (size > 0)
        {
            while (head != nullptr && head->username == un)
            {
                deleteFirst();
            }

            FeedbackNode<F> *DEL = head;
            while (DEL != nullptr && DEL->next != nullptr)
            {
                if (DEL->next->username == un)
                {
                    FeedbackNode<F> *temp = DEL->next;
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

    // view all feedbacks
    void viewList()
    {
        FeedbackNode<F> *curr = head;
        string status;

        cout << "\n************************* Feedback List ( " << size << " elements) *************************\n"
             << endl;
        while (curr != nullptr)
        {
            if (curr->reply == "")
            {
                status = "Pending";
            }
            else
            {
                status = "Completed";
            }
            cout << "\n[" << curr->id << "] "
                 << "Username: " << curr->username << "\n    Status: " << status << "\n    Location Code: " << curr->locationcode
                 << "\t\t\tUniversity Name: " << curr->university << "\n    Date: " << curr->fbDate << "\nFeedback: " << curr->feedback << "\nReply: " << curr->reply << endl;
            cout << "-------------------------------------------------------------------------------" << endl;
            curr = curr->next;
        }
        cout << "*******************************END OF DISPLAYING*******************************" << endl
             << endl;
    }

    // admin: move back and forth between feedback
    //  num = ID, choice = prev/next
    string getFeedbackNow(F num, char choice)
    {
        if (head != nullptr)
        {
            FeedbackNode<F> *curr = head;
            if (num == "0")
            {
                if (size > 1)
                {
                    curr = tail->prev; // to get the last node by default
                }
            }
            else
            {
                while (curr->id != num)
                {
                    curr = curr->next; // id wont be zero, this works normal
                }
            }

            // to find the previous or next
            FeedbackNode<F> *currviewing = curr;
            if (size > 1)
            {
                if (choice == 'p')
                {
                    curr = curr->prev;
                }
                else
                {
                    curr = curr->next;
                }
            }

            // to determine the node (p/n) is at the end of the list now
            if (curr == NULL)
            {
                cout << "\n$!@#%& You have reached the end of the list, try again with another menu choice! &%#@!$" << endl;
                viewFeedbackNow(currviewing->id);
                return currviewing->id;
            }
            else
            {
                viewFeedbackNow(curr->id);
            }
            return curr->id;
        }
        else
        {
            cout << "\nThe feedback list is still empty for now." << endl;
            return "-1";
        }
    }

    // admin: within getFeedbackNow
    //  num = ID
    void viewFeedbackNow(F num)
    {
        if (head != nullptr)
        {
            FeedbackNode<F> *curr = tail;
            if (num == "0")
            {
                curr = tail->prev;
            }
            else
            {
                while (curr->id != num)
                {
                    curr = curr->prev; // check with feedback ID
                }
            }
            cout << "\n===========================================================================================================================";
            cout << "\n<| Now Viewing" << endl;

            string status;
            if (curr->reply == "")
            {
                status = "Pending";
            }
            else
            {
                status = "Completed";
            }
            cout << "\n[" << curr->id << "] "
                 << "Username: " << curr->username << "\n    Status: " << status << "\n    Location Code: " << curr->locationcode
                 << "\t\t\tUniversity Name: " << curr->university << "\n    Date: " << curr->fbDate << "\nFeedback: " << curr->feedback << "\nReply: " << curr->reply << endl;
            cout << "\n===========================================================================================================================";
        }
    }

    // admin reply the customer feedback
    //  num = ID
    void reply(F num)
    {
        // search the customer node
        FeedbackNode<F> *curr = head;
        while (curr != nullptr)
        {
            if (curr->id == num)
            {
                viewFeedbackNow(num);
                break;
            }
            else
            {
                curr = curr->next;
            }
        }

        // enter reply
        string replyTxt;
        while (true)
        {
            cout << "\n Feedback Reply  \n-----------------------------------------"
                    "\n Enter 'Q' to quit replying and go back to Feedback Menu"
                    "\n\nReply Message: ";
            getline(cin, replyTxt); // to get input
            if (replyTxt == "Q" || replyTxt == "q")
            {
                string a;
                cout << "\nATTENTION: Are you sure to QUIT replying to this feedback? (choose Y if yes): ";
                cin >> a;
                if (a == "Y" || a == "y")
                {
                    cout << "\n**************************************************************************************************************************";
                    cout << "\n$!@#%& Redirecting you to the beginning of feedback menu &%#@!$" << endl;
                    break; // back to feedback menu
                }
                else
                {
                    cout << "\n$!@#%& Redirecting you to the beginning of feedback reply menu &%#@!$" << endl;
                }
            }
            else
            {
                curr->reply = replyTxt;
                cout << "\n----------------------------------\nReply to the feedback ID " << curr->id << " has been made.\n-----------------------------------------" << endl;
                cout << "\n**************************************************************************************************************************";
                cout << "\n$!@#%& Redirecting you to the beginning of feedback menu &%#@!$" << endl;
                break;
            }
        }
    }

    // customer: move back and forth between feedback
    //  num = ID, choice = prev/next
    string getcusFeedback(F num, F un, char choice) // num = ID, choice = prev/next
    {
        if (head != nullptr)
        {
            FeedbackNode<F> *curr = tail;
            if (num == "0")
            {
                while (curr->username != un) // find the last node FROM THIS CUS to show
                {
                    curr = curr->prev;
                }
                if (size > 1)
                {
                    curr = curr->prev; // to find the node before the last feedback from the specific customer
                }
            }
            else
            {
                while (curr->id != num)
                {
                    curr = curr->prev;
                }
            }

            // to find the previous or next
            FeedbackNode<F> *currviewing = curr;
            if (size > 1)
            {
                if (choice == 'p')
                {
                    do
                    {
                        curr = curr->prev;
                        if (curr != nullptr && curr->username == un) // prevent dereference error
                        {
                            break;
                        }
                    } while (curr != nullptr);
                }
                else
                {
                    do
                    {
                        curr = curr->next;
                        if (curr != nullptr && curr->username == un)
                        {
                            break;
                        }
                    } while (curr != nullptr);
                }
            }
            else
            {
                cout << "\n!! ONLY ONE DATA EXIST RIGHT NOW !!" << endl;
            }

            // to determine the node (p/n) is at the end of the list now
            if (curr == NULL)
            {
                cout << "\n$!@#%& You have reached the end of the list, try again with another menu choice! &%#@!$" << endl;
                viewFeedbackNow(currviewing->id);
                return currviewing->id;
            }
            else
            {
                viewFeedbackNow(curr->id);
            }
            return curr->id;
        }
        else
        {
            cout << "\nThe feedback list is still empty for now." << endl;
            return "-1";
        }
    }

    void viewCusFeedback(F num) // num = ID
    {
        if (head != nullptr)
        {
            FeedbackNode<F> *curr = tail;
            while (curr->id != num)
            {
                curr = curr->prev;
            }
            cout << "\n===========================================================================================================================";
            cout << "\n<| Now Viewing" << endl;

            string status;
            if (curr->reply == "")
            {
                status = "Pending";
            }
            else
            {
                status = "Completed";
            }
            cout << "\n[" << curr->id << "] "
                 << "Username: " << curr->username << "\n    Status: " << status << "\n    Location Code: " << curr->locationcode
                 << "\t\t\tUniversity Name: " << curr->university << "\n    Date: " << curr->fbDate << "\nFeedback: " << curr->feedback << "\nReply: " << curr->reply << endl;
            cout << "\n===========================================================================================================================";
        }
    }

    bool checkUser(F nm)
    {
        FeedbackNode<F> *curr = head;
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
        if (curr == nullptr)
        {
            cout << "\n$!@#%& You have no feedback history. &%#@!$" << endl;
            return 0;
        }
        else
        {
            return 1;
        }
    }

    bool checkUni(F uni, F lc, F un)
    {
        FeedbackNode<F> *curr = head;
        while (curr != nullptr)
        {
            if (curr->username == un && curr->university == uni && curr->locationcode == lc)
            {
                string a;
                cout << "\n$!@#%& You have made feedback on this University before! &%#@!$"
                        "\nDo you want to make a new feedback?  "
                        "\n Enter 'Y' if yes: ";
                cin >> a;
                if (a == "Y" || a == "y")
                {
                    return true; // proceed to make a new feedback
                }
                else
                {
                    return false; // do not proceed with new feedback
                }
            }
            curr = curr->next;
        }

        return true; // no duplicate feedback found, proceed to make a new feedback
    }
    void validateInput(SearchUni &uni, string &universityname, string &locationCode, int &index)
    {
        try
        {
            index = uni.linearIns(universityname, "1");

            if (index > 0)
            {
                string rankinput;
                cout << "\nSelect a Rank: ";
                cin >> rankinput;

                // Try to convert the user input to an integer
                int selectedRank = stoi(rankinput);

                // Check if the input rank is within the valid range
                if (selectedRank >= 1 && selectedRank <= maxrow)
                {
                    string institutionName = uni.linearRank(rankinput, "1");

                    if (!institutionName.empty())
                    {
                        universityname = institutionName;
                        locationCode = uni.universityarr[selectedRank - 1][2];

                        // You can add code here to retrieve the feedback node for the university
                    }
                    else
                    {
                        cout << "\nInvalid university rank!";
                    }
                }
                else
                {
                    cout << "\nInvalid rank input!";
                    locationCode = " ";
                }
            }
            else
            {
                locationCode = " ";
            }
        }
        catch (const std::exception &e)
        {
            cout << "\nInvalid input! Please enter a valid rank as an integer.";
            locationCode = " ";
        }
    }
};

#endif