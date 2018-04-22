#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdio>
#include <conio.h>

using namespace std;

struct Person {
    int individualNumberOfEachFriend;
    string name, surname, phoneNumber, email, address;
};

int addFriendsAndSaveThemToTextFile(Person persons[], int numberOfFriends) {
    string name, surname, phoneNumber, email, address;

    cout << "Podaj imie: ";
    cin >> name;
    cout << "Podaj nazwisko: ";
    cin >> surname;
    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline(cin, phoneNumber);
    cout << "Podaj adres email: ";
    cin >> email;
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin, address);

    int personId = numberOfFriends + 1;

    persons[numberOfFriends].individualNumberOfEachFriend = personId;
    persons[numberOfFriends].name = name;
    persons[numberOfFriends].surname = surname;
    persons[numberOfFriends].phoneNumber = phoneNumber;
    persons[numberOfFriends].email = email;
    persons[numberOfFriends].address = address;


    fstream file;
    file.open("KsiazkaAdresowa.txt", ios::out | ios::app);
    if(file.good()) {
        file << personId << endl;
        file << name << endl;
        file << surname << endl;
        file << phoneNumber << endl;
        file << email << endl;
        file << address << endl;

        file.close();

        cout << "Przyjaciel zostal dodany." << endl;
        Sleep(1000);
    } else {
        cout << "Nie mozna otworzyc pliku KsiazkaAdresowa.txt !!" <<endl;
    }
    numberOfFriends++;
    return numberOfFriends;
}

int loadFriendsFromTextFile(Person persons[]) {

    fstream file;
    file.open("KsiazkaAdresowa.txt", ios::in);

    if(!file.good()) {
        cout << "Plik nie istnieje!" <<endl;
    }

    string line;
    int numberOfLine = 1;
    int numberOfFriends = 0;

    while(getline(file, line)) {
        switch(numberOfLine) {
        case 1:
            persons[numberOfFriends].individualNumberOfEachFriend = atoi(line.c_str());
            break;
        case 2:
            persons[numberOfFriends].name = line;
            break;
        case 3:
            persons[numberOfFriends].surname = line;
            break;
        case 4:
            persons[numberOfFriends].phoneNumber = line;
            break;
        case 5:
            persons[numberOfFriends].email = line;
            break;
        case 6:
            persons[numberOfFriends].address = line;
            break;
        }
        if (numberOfLine == 6) {
            numberOfLine = 0;
            numberOfFriends++;
        }
        numberOfLine++;

    }
    file.close();

    return numberOfFriends;
}

void searchByName(Person persons[], int numberOfFriends) {
    string name;
    int index = 0;
    cout << "Podaj imie przyjaciela: ";
    cin >> name;

    while(index < numberOfFriends) {
        if(persons[index].name == name) {
            cout << endl;
            cout << "ID: " << persons[index].individualNumberOfEachFriend << endl;
            cout << persons[index].name << " " << persons[index].surname << endl;
            cout << "Telefon: " << persons[index].phoneNumber << endl;
            cout << "Email: " << persons[index].email << endl;
            cout << "Adres: " << persons[index].address << endl;
        }
        index++;
    }
    getch();

}

void searchBySurname(Person persons[], int numberOfFriends) {
    string surname;
    int index = 0;
    cout << "Podaj nazwisko przyjaciela: ";
    cin >> surname;

    while(index < numberOfFriends) {
        if(persons[index].surname == surname) {
            cout << endl;
            cout << "ID: " << persons[index].individualNumberOfEachFriend << endl;
            cout << persons[index].name << " " << persons[index].surname << endl;
            cout << "Telefon: " << persons[index].phoneNumber << endl;
            cout << "Email: " << persons[index].email << endl;
            cout << "Adres: " << persons[index].address << endl;
        }
        index++;
    }
    getch();
}

void writeAllYourFriends(Person persons[], int numberOfFriends) {
    int index = 0;

    while(index < numberOfFriends) {

        cout << endl;
        cout << "ID: " << persons[index].individualNumberOfEachFriend << endl;
        cout << persons[index].name << " " << persons[index].surname << endl;
        cout << "Telefon: " << persons[index].phoneNumber << endl;
        cout << "Email: " << persons[index].email << endl;
        cout << "Adres: " << persons[index].address << endl;
        index++;
    }
    getch();
}

void basicMenu (Person persons[], int numberOfFriends) {
    while(1) {

        char choice;

        system("cls");
        cout << "1. Dodaj przyjaciela." <<endl;
        cout << "2. Wyszukaj przyjaciela." <<endl;
        cout << "9. Koniec programu." <<endl;
        cout << endl;

        cin >> choice;

        if(choice == '1') {
            numberOfFriends = addFriendsAndSaveThemToTextFile(persons, numberOfFriends);
        } else if(choice == '2') {
            char option;
            system("cls");
            cout << "1. Wyszukiwanie po imieniu." <<endl;
            cout << "2. Wyszukiwanie po nazwisku." <<endl;
            cout << "3. Wyswietl wszystkich znajomych." <<endl;
            cout << "4. Powrot do wczesniejszego menu." <<endl;
            cout << endl;
            cin >> option;

            if(option == '1') {
                searchByName(persons, numberOfFriends);
            } else if(option == '2') {
                searchBySurname(persons, numberOfFriends);
            } else if(option == '3') {
                writeAllYourFriends(persons, numberOfFriends);
            } else if(option == '4') {
                basicMenu(persons, numberOfFriends);
            }
        } else if(choice == '9') {
            exit(0);
        }

    }
}

int main() {
    int numberOfFriends = 0;
    Person persons[100];

    numberOfFriends = loadFriendsFromTextFile(persons);

    basicMenu(persons, numberOfFriends);
    return 0;
}
