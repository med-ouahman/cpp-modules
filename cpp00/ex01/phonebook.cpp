#include <iostream>
#include <string>
#include <iomanip>

# define ADD "ADD"
# define SEARCH "SEARCH"
# define EXIT "EXIT"

# define MAX_CONTACT 8

int eofErr;

class Contact {
    public:
        std::string firstName;
        std::string lastName;
        std::string nickName;
        std::string phoneNumber;
        std::string darkestSecret;
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

    std::cout << "First name:\n";
    
    if (!(std::getline(std::cin, newContact.firstName))) {
        eofErr = 1;
        return newContact;
    }
    std::cout << "Last name:\n";
    if (!(std::getline(std::cin, newContact.lastName))) {
        eofErr = 1;
        return newContact;
    }
    std::cout << "Nickname:\n";
    if (!(std::getline(std::cin, newContact.nickName))) {
        eofErr = 1;
        return newContact;
    }
    std::cout << "Phone number:\n";
    if (!(std::getline(std::cin, newContact.phoneNumber))) {
        eofErr = 1;
        return newContact;
    }
    std::cout << "Darkest secret:\n";
    if (!(std::getline(std::cin, newContact.darkestSecret))) {
        eofErr = 1;
    }
    return newContact;
}

void printTrunc(std::string s) {
    
    if (s.length() >= 10) {
        std::cout << std::setw(10) << s.substr(0, 10) << ".";
    } else {
        std::cout << std::setw(10) << s;   
    }
}

void displayEntry(Contact contact) {
    std::cout << contact.firstName << "\n";
    std::cout << contact.lastName << "\n";
    std::cout << contact.nickName << "\n";
    std::cout << contact.phoneNumber << "\n";
    std::cout << contact.darkestSecret << "\n";
}

void displayContact(Contact c, int i) {
    
    std::cout << std::setw(10) << i;
    std::cout << "|";
    printTrunc(c.firstName);
    std::cout << "|";
    printTrunc(c.lastName);
    std::cout << "|";
    printTrunc(c.nickName);
    std::cout << "|";
}

int getNum(int *num) {
    std::string s;

    if (!std::getline(std::cin, s)) {
        return 0;
    }
    try {
        *num = std::stoi(s);
    } catch (std::exception e) {
       return -1;
    }
    return 1;
}

void displayContacts(PhoneBook phoneBook) {

    int index = -1;
    if (phoneBook.contactCount == 0) {
        std::cout << "You don't have contacts now, Enter ADD to add them\n";
        return ;
    }
    for (int i = 0; i < phoneBook.contactCount; i++) {
        displayContact(phoneBook.contacts[i], i);
        std::cout << std::endl;
    }
    std::cout << "Enter the index of the contact:\n";
    if (!getNum(&index)) {
        eofErr = 1;
        return ;
    }
    while (index >= phoneBook.contactCount || index < 0) {
        std::cout << "No such entry\nEnter the index of the contact:\n";
        if (!getNum(&index)) {
            eofErr = 1;
            return ;
        }
    }
    displayEntry(phoneBook.contacts[index]);
}

int main() {
    std::string command;
    PhoneBook phoneBook;
    Contact contact;
    eofErr = 0;

    while (true) {
        std::cout << "Enter a command: options: (ADD, SEARCH, EXIT):\n";
        if (!std::getline(std::cin, command)) {
            break;
        }
        if (command == ADD) {
            contact = createContact();
            if (eofErr)
                break;
            if (contact.firstName.empty()
                || contact.lastName.empty()
                || contact.nickName.empty()
                || contact.darkestSecret.empty()) {
                    std::cout << "Cannot create a contact with an empty field, try again.\n";
                    continue; 
            }
            phoneBook.addContact(contact);
        } else if (command == SEARCH) {
            displayContacts(phoneBook);
            if (eofErr) {
                break;
            }
        } else if (command == EXIT) {
            break;
        }
    }
    if (eofErr)
        std::cout << "\n";
    std::cout << "Exiting the phonebook application.\n";
    std::cout << "Goodbye!" << std::endl;
    std::cin.clear();
    return 0;
}