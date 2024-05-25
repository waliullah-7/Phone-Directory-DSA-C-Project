#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class ContactNode {
public:
    ContactNode* connections[26];
    bool endOfContact;
    string fullName;
    string phoneNumber;
    string email;
    string birthDate;
    string homeAddress;

    ContactNode() {
        for (int i = 0; i < 26; ++i) {
            connections[i] = nullptr;
        }
        endOfContact = false;
        fullName = "";
        phoneNumber = "";
        email = "";
        birthDate = "";
        homeAddress = "";
    }
};

class Directory {
public:
    ContactNode* root;

    Directory() {
        root = new ContactNode();
    }

    void addContact(string fullName, string phoneNumber, string email = "", string birthDate = "", string homeAddress = "") {
        ContactNode* current = root;
        cout << "Adding contact: " << fullName << " (" << phoneNumber << ")" << endl;
        for (char c : fullName) {
            c = tolower(c);
            int index = c - 'a';
            if (current->connections[index] == nullptr) {
                current->connections[index] = new ContactNode();
            }
            current = current->connections[index];
        }
        current->endOfContact = true;
        current->fullName = fullName;
        current->phoneNumber = phoneNumber;
        current->email = email;
        current->birthDate = birthDate;
        current->homeAddress = homeAddress;
        cout << "Contact added!" << endl;
    }

    void editContact(string fullName, string newPhoneNumber, string newEmail = "", string newBirthDate = "", string newHomeAddress = "") {
        ContactNode* current = findNode(fullName);
        if (current && current->endOfContact) {
            current->phoneNumber = newPhoneNumber;
            current->email = newEmail;
            current->birthDate = newBirthDate;
            current->homeAddress = newHomeAddress;
            cout << "Contact updated!" << endl;
        } else {
            cout << "Contact not found." << endl;
        }
    }

    void deleteContact(string fullName) {
        if (deleteContactHelper(root, fullName, 0)) {
            cout << "Contact deleted!" << endl;
        } else {
            cout << "Contact not found." << endl;
        }
    }

    bool deleteContactHelper(ContactNode* node, string& fullName, int depth) {
        if (!node) return false;

        if (depth == fullName.size()) {
            if (node->endOfContact) {
                node->endOfContact = false;
                return true;
            }
            return false;
        }

        int index = tolower(fullName[depth]) - 'a';
        if (deleteContactHelper(node->connections[index], fullName, depth + 1)) {
            if (!node->endOfContact) {
                delete node->connections[index];
                node->connections[index] = nullptr;
                return true;
            }
        }
        return false;
    }

    ContactNode* findNode(string fullName) {
        ContactNode* current = root;
        for (char c : fullName) {
            int index = tolower(c) - 'a';
            if (current->connections[index] == nullptr) {
                return nullptr;
            }
            current = current->connections[index];
        }
        return current;
    }

    vector<ContactNode*> searchContacts(string fullName) {
        vector<ContactNode*> result;
        ContactNode* current = root;
        for (char c : fullName) {
            int index = tolower(c) - 'a';
            if (current->connections[index] == nullptr) {
                return result; // No contacts found
            }
            current = current->connections[index];
        }
        collectAllContacts(current, result);
        return result;
    }

    void collectAllContacts(ContactNode* node, vector<ContactNode*>& result) {
        if (node->endOfContact) {
            result.push_back(node);
        }
        for (int i = 0; i < 26; ++i) {
            if (node->connections[i] != nullptr) {
                collectAllContacts(node->connections[i], result);
            }
        }
    }

    void displayContactInfo(ContactNode* node) {
        if (node->endOfContact) {
            cout << "Name: " << node->fullName << endl;
            cout << "   Phone No: " << node->phoneNumber << endl;
            cout << "   Email: " << node->email << endl;
            cout << "   Date of Birth: " << node->birthDate << endl;
            cout << "   Address: " << node->homeAddress << endl;
        }
    }

    void displayContactsInfo(ContactNode* node, string fullName) {
        if (node->endOfContact) {
            cout << "Name: " << fullName << endl;
            cout << "   Phone No: " << node->phoneNumber << endl;
            cout << "   Email: " << node->email << endl;
            cout << "   Date of Birth: " << node->birthDate << endl;
            cout << "   Address: " << node->homeAddress << endl;
        }
        for (int i = 0; i < 26; ++i) {
            if (node->connections[i] != nullptr) {
                char c = 'a' + i;
                displayContactsInfo(node->connections[i], fullName + c);
            }
        }
    }

    void displayContacts() {
        displayContactsInfo(root, "");
    }
};

int main() {
    int choice;
    Directory contactBook;

    do {
        cout << "Select an Operation!" << endl;
        cout << "1. Add a new contact" << endl;
        cout << "2. Edit a contact" << endl;
        cout << "3. Delete a contact" << endl;
        cout << "4. Display contacts" << endl;
        cout << "5. Find a contact" << endl;
        cout << "6. Quit" << endl;

        cin >> choice;

        switch (choice) {
        case 1: {
            string fullName, phoneNumber, email, birthDate, homeAddress;
            cout << "Enter full name: ";
            cin >> fullName;
            cout << "Enter phone number: ";
            cin >> phoneNumber;

            cout << "Enter email (or '-' to skip): ";
            cin >> email;
            if (email == "-") {
                email = "";
            }

            cout << "Enter date of birth (or '-' to skip): ";
            cin >> birthDate;
            if (birthDate == "-") {
                birthDate = "";
            }

            cout << "Enter address (or '-' to skip): ";
            cin >> homeAddress;
            if (homeAddress == "-") {
                homeAddress = "";
            }

            contactBook.addContact(fullName, phoneNumber, email, birthDate, homeAddress);
            break;
        }

        case 2: {
            string fullName, newPhoneNumber, newEmail, newBirthDate, newHomeAddress;
            cout << "Enter full name of contact to edit: ";
            cin >> fullName;
            cout << "Enter new phone number: ";
            cin >> newPhoneNumber;

            cout << "Enter new email (or '-' to skip): ";
            cin >> newEmail;
            if (newEmail == "-") {
                newEmail = "";
            }

            cout << "Enter new date of birth (or '-' to skip): ";
            cin >> newBirthDate;
            if (newBirthDate == "-") {
                newBirthDate = "";
            }

            cout << "Enter new address (or '-' to skip): ";
            cin >> newHomeAddress;
            if (newHomeAddress == "-") {
                newHomeAddress = "";
            }

            contactBook.editContact(fullName, newPhoneNumber, newEmail, newBirthDate, newHomeAddress);
            break;
        }

        case 3: {
            string fullName;
            cout << "Enter full name of contact to delete: ";
            cin >> fullName;
            contactBook.deleteContact(fullName);
            break;
        }

        case 4: {
            cout << "Contacts:" << endl;
            contactBook.displayContacts();
            break;
        }

        case 5: {
            string fullName;
            cout << "Enter name to find: ";
            cin >> fullName;
            vector<ContactNode*> searchResults = contactBook.searchContacts(fullName);
            if (!searchResults.empty()) {
                cout << "Found contacts:" << endl;
                for (ContactNode* node : searchResults) {
                    contactBook.displayContactInfo(node);
                }
            } else {
                cout << fullName << " not found in the contact book." << endl;
            }
            break;
        }

        case 6: {
            cout << "Exiting..." << endl;
            break;
        }

        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 6);

    return 0;
}