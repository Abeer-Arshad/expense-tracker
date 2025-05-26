#include<iostream>
#include<string>
using namespace std;

// Node for a single product in a product list
class node {
public:
    string data;
    node* next;

    node(string value) {
        data = value;
        next = NULL;
    }
};

// MasterNode to hold the head of a product list
class mnode {
public:
    node* lkhead;  // Head of the product list
    mnode* mnext;  // Pointer to the next master node

    mnode(node* lkh) {
        lkhead = lkh;
        mnext = NULL;
    }
};

// MasterList to hold the heads of all product lists
class maslist {
public:
    mnode* mhead;  // Head of the master list

    maslist() {
        mhead = NULL;
    }

    // Add the head of a new product list to the master list
    void inmlist(node* pin) {
        mnode* mnewnode = new mnode(pin);
        if (mhead == NULL) {
            mhead = mnewnode;
        } else {
            mnode* mtemp = mhead;
            while (mtemp->mnext != NULL) {
                mtemp = mtemp->mnext;
            }
            mtemp->mnext = mnewnode;
        }
    }

    // Display the product lists stored in the master list
    void display() {
         if (mhead == NULL) {
            cout << "Master list is empty.\n";
            return;
        }
        mnode* temp = mhead;
        int listNumber = 1;
        int no=1;
        while (temp != NULL) {
            cout << "List " << listNumber++ <<endl;
            node* current = temp->lkhead;
            while (current != NULL) {
                if (no==1){cout<<"Name : ";}
                else if(no==2){cout<<"Amount : ";}
                else if(no==3){cout<<"Date : ";}
                cout << current->data <<endl;
                current = current->next;
                no++;
            }
            cout << endl;
            temp = temp->mnext;
        }
    }
    void mostexp(int val){
         if (mhead == NULL) {
            cout << "Master list is empty.\n";
            return;
        }
        string tvalue;
        tvalue = to_string(val);
        mnode* temp = mhead;
        int listNumber = 1;
        cout<<"Most Expensive product :"<<endl;
        while (temp != NULL) {
            node* current = temp->lkhead;
           if(current->next->data==tvalue)
            {int no=1; 
            cout<<listNumber<<")"<<" "<<endl;
            while (current != NULL) {
                if (no==1){cout<<"Name : ";}
                else if(no==2){cout<<"Amount : ";}
                else if(no==3){cout<<"Date : ";}
                cout << current->data <<endl;
                current = current->next;
                no++;
            }
                listNumber++;
            }
            temp = temp->mnext;}
        }
    //  Update field in specific list
    void updateList(int listNumber, int field, string newValue) {
         if (mhead == NULL) {
            cout << "list is empty.\n";
    
            return;
        }

        mnode* temp = mhead;
        int count = 1;
        while (temp != NULL && count < listNumber) {
            temp = temp->mnext;
            count++;
        }
        if (temp == NULL) {
            cout << "Invalid list number.\n";
            return;
        }

        node* current = temp->lkhead;
   if (field == 1) {
        // Already at Name
    } else if (field == 2 && current != NULL) {
        current = current->next;
    } else if (field == 3 && current != NULL && current->next != NULL) {
        current = current->next->next;
    } else {
        cout << "Invalid field number or list structure.\n";
        return;
    }

        if (current == NULL) {
            cout << "Invalid field number.\n";
            return;
        }

        current->data = newValue;
        cout << "Field updated successfully.\n";
    }

    //  Delete a specific list
    void deleteList(int listNumber) {
        if (mhead == NULL) {
            cout << "Master list is empty.\n";
            return;
        }

        mnode* temp = mhead;
        mnode* prev = NULL;
        int count = 1;

        while (temp != NULL && count < listNumber) {
            prev = temp;
            temp = temp->mnext;
            count++;
        }

        if (temp == NULL) {
            cout << "Invalid list number.\n";
            return;
        }

        // Delete linked list of that node
        node* current = temp->lkhead;
        while (current != NULL) {
            node* next = current->next;
            delete current;
            current = next;
        }

        // Remove master node from master list
        if (prev == NULL) {
            // Deleting first node
            mhead = temp->mnext;
        } else {
            prev->mnext = temp->mnext;
        }

        delete temp;
        cout << "List deleted successfully.\n";
    }    

};

// A class to manage individual product lists
class newlist {
public:
    node* head;  // Head of the individual product list
    maslist& mobj;  // Reference to the global master list
    
    newlist(maslist& master) : mobj(master) {
        head = NULL;
    }

    // Insert a new product into the list
    void inlist(string value) {
        node* newnode = new node(value);
        if (head == NULL) {
            head = newnode;
            mobj.inmlist(head);  // Add the head of the list to the master list
        } else {
            node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newnode;
        }
    }

    // Display the current product list
    void display() {
        node* temp = head;
        while (temp != NULL) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

int main() {
    maslist masterList;  // Create a single master list that stores all heads
    int ch;
    int total=0,max=0;
    do
    {
    cout<<"1) Enter new product"<<endl;
    cout<<"2) Total spend Money "<<endl;
    cout<<"3) Most expensive Product "<<endl;
    cout<<"4) Update any data"<<endl;
    cout<<"5) Delete any data "<<endl;
    cout<<"6) Display all data"<<endl;
    cout<<"7) Exit"<<endl;
    cin>>ch;
    switch(ch)
    {
    case 1:
    {
        newlist list(masterList);  // Pass masterList to newlist instance

       
        for (int i = 0; i < 3; ++i) {
            string product;
            if(i==0)
            {
                cout<<"Enter name :";
                cin >> product;
                list.inlist(product);  // Add product to the list
            }
            if(i==1)
            {
                int amount;
                cout<<"Enter amount : ";
                cin>>amount;
                if(amount>=max)
                {
                    max=amount;
                }
                total= total+amount;
                product = to_string(amount);
                list.inlist(product);  // Add product to the list
            }
            if(i==2)
            {
                cout<<"Enter date (dd-mm-yyyy) :";
                cin >> product;
                list.inlist(product);  // Add product to the list
            }
        }
    break;
    }
    case 2:
    {
         masterList.display();
        cout<<"Total spend money = "<<total<<endl;
        break;
    }
    case 3:
    {
        masterList.mostexp(max);
        break;
    }
    case 4: {
        masterList.display();
    int listNum, field;
    string newVal;
    cout << "Enter list number to update: ";
    cin >> listNum;
    cout << "Enter field no to update (1: Name, 2: Amount, 3: Date): ";
    cin >> field;
    cout << "Enter new value: ";
    cin.ignore(); // to consume leftover newline
    getline(cin, newVal);
    masterList.updateList(listNum, field, newVal);

    break;
}
case 5: {
    int listNum;
    cout << "Enter list number to delete: ";
    cin >> listNum;
    masterList.deleteList(listNum);
    break;
}

    case 6:
    {
    // Display all the product lists
    cout << "\nDisplaying Master List (heads of each list): " << endl;
    masterList.display();
    break;
    }
    case 7:
    {
        return 0;
    }
    default:
    {
        break;
    }
    }
    }while(ch!=7);
    return 0;
}
