#include <iostream>
#include <string>

# define ADD "ADD"
# define SEARCH "SEARCH"
# define EXIT "EXIT"

# define MAX_CONTACT 8

using namespace std;

class Contact {
    public:
        string firstName;
        string lastName;
        string nickName;
        string phoneNumber;
        string darkestSecret;
};

class PhoneBook {

    public:
        int contactCount = 0;
        Contact contacts[MAX_CONTACT];
        void addContact(Contact newContact) {
            if (contactCount == MAX_CONTACT - 1) {
                contactCount = 0;
            }
            contacts[contactCount] = newContact;
            contactCount++;
        }
};

Contact createContact() {

    Contact newContact;

    cout << "First name: ";
    cin >> newContact.firstName;
    cout << "Last name: ";
    cin >> newContact.lastName;
    cout << "Nickname: ";
    cin >> newContact.nickName;
    cout << "Phone number: ";
    cin >> newContact.phoneNumber;
    cout << "Darkest secret: ";
    cin >> newContact.darkestSecret;
    return newContact;
}

void printTen(string s) {
    
    size_t len = s.length();
    if (len <= 10) {
        while (len <= 10) {
            cout << " ";
            len++;
        }
        cout << s;
    } else {
        for (size_t i = 0; i < 9; i++) {
            cout << s[i];
        }
        cout << ".";
    }
}

void displayEntry(Contact contact) {
    cout << contact.firstName << "\n";
    cout << contact.lastName << "\n";
    cout << contact.nickName << "\n";
    cout << contact.phoneNumber << "\n";
    cout << contact.darkestSecret << "\n";
}

void displayContact(Contact c, int i) {
    
    for (int j = 0; j < 9; j++) cout << " ";
    cout << i << "|";
    printTen(c.firstName);
    cout << "|";
    printTen(c.lastName);
    cout << "|";
    printTen(c.nickName);
}

void displayContacts(PhoneBook phoneBook) {

    int display;

    if (phoneBook.contactCount == 0)
        cout << "You don't have contacts now, Enter ADD to add them\n";
    for (int i = 0; i < phoneBook.contactCount; i++) {
        displayContact(phoneBook.contacts[i], i);
        cout << "\n";
    }
    cout << "Enter the index of the contact: ";
    cin >> display;
    while (display >= phoneBook.contactCount || display < 0) {
        cout << "No such entry\n" << "Enter the index of the contact: ";
        cin >> display;
    }
    displayEntry(phoneBook.contacts[display]);
}

int main() {
    string command;

    PhoneBook phoneBook;
    Contact contact;

    while (true) {
        cout << "Enter a command: options: (ADD, SEARCH, EXIT): ";
        
        cin >> command;
        if (command == ADD) {
            contact = createContact();
            if (contact.firstName.empty()
                || contact.lastName.empty()
                || contact.nickName.empty()
                || contact.darkestSecret.empty()) {
                    cout << "Cannot create a contact with an empty field, try again.\n";
                    continue; 
                }
            phoneBook.addContact(contact);
        } else if (command == SEARCH) {
            displayContacts(phoneBook);

        } else if (command == EXIT)
            break;
    }
    cout << "Exiting the phonebook application.\n";
    cout << "Goodbye!\n";
    cin.clear();
    return 0;
}