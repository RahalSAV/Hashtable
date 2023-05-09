#include <iostream>
#include "linkedlist.cpp"
using namespace std;

struct HashTable {
    int MAX_LENGTH = 4;
    int MAX_CHAIN_LENGTH = 2;
    LinkedList* password = new LinkedList[MAX_LENGTH];

    bool isFull() {
        bool full = true;
        for (int i = 0; i < MAX_LENGTH; i++) {
            if (password[i].head == NULL) {
                full = false;
                break;
            }
        }
        return full;
    }

    int hashfunc(string user_name) {
        int sum = 0;
        for (int i = 0; i < user_name.length(); i++) {
            sum += int(user_name[i]);
        }
        int hash = sum % MAX_LENGTH;
        return hash;
    }

    bool is_slot_empty(int hash) {
        if (password[hash].head == NULL) {
            return true;
        }
        else {
            return false;
        }
    }

    void insert(string user_name, string user_password) {
        int hash = hashfunc(user_name);
        bool empty = is_slot_empty(hash);
        if (empty && password[hash].length < MAX_CHAIN_LENGTH) {
            password[hash].insert(user_name.data(), user_password.data());
        }
        else {
            cout << "Linked List reached MAX CAP!\n";
        }
    }

    void print_hashtable() {
        for (int i = 0; i < MAX_LENGTH; i++) {
            cout << "[" << i << "]-->";
            password[i].print_list();
        }
    }

    void hash_lookup(string user_name) {
        int hash = hashfunc(user_name);
        bool empty = is_slot_empty(hash);
        if (!empty) {
            Node* current = password[hash].head;
            while (current != NULL) {
                if (current->data == user_name) {
                    cout << "Password found: " << current->password << endl;
                    return;
                }
                current = current->next;
            }
            cout << "Password not found for user: " << user_name << endl;
        }
        else {
            cout << "User not found: " << user_name << endl;
        }
    }
};

int main() {
    HashTable* hashtbl = new HashTable;
    cout << hashtbl->isFull() << "\n";
    int command = 0;
    string user_name;
    string password;
    while (command != -1) {
        cout << "Type command: ";
        cin >> command;
        switch (command) {
        case 1:
            cout << "Enter user name: ";
            cin >> user_name;
            cout << "Enter password to be saved: ";
            cin >> password;
            hashtbl->insert(user_name, password);
            break;
        case 2:
            cout << "Enter user name to look up password: ";
            cin >> user_name;
            hashtbl->hash_lookup(user_name);
            break;
        case 3:
            hashtbl->print_hashtable();
            break;
        case -1:
            hashtbl->print_hashtable();
            cout << "Exiting...\n";
            break;
        }
    }
    return 0;
}
