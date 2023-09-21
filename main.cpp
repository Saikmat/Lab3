/*
* Copyright 2023 - Howard Community College All rights reserved; Unauthorized duplication prohibited.
* Name: Sai Matukumalli
* Class: CMSY-171
* Instructor: Justyn Crook
* Program Name: Lab 1
* Program Description: This lab is a review of concepts covered previously. Using two dynamically allocated arrays and a vector
* it maintains a database of the name, number, and endangered status of each animal in the database. It features a menu
* for adding and displaying the name in the database as well as displaying the animal's endangered status.
*/


#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

/*
 * Runs the menu of the program, enabling users to choose what they want to do in the database, add or display
 * Dynamically allocates the arrays for names, types, and size based on the user entered count
 * Menu validates input and ensures that user enters an integer 1-3 incl.
 * Returns 0 for successful completion and any other value for error return
 */

struct Animal {
    char* name;
    int typeCount;
    bool endangered;
};

void printCopyright();

void addAnimals(vector<Animal*>* database);

void displayAnimals(vector<Animal*> database);

void displayEndangered(vector<Animal*> database);

void searchAnimals(vector<Animal*> animals);

void selectionSortStrings(vector<Animal*> &animals);

/*
 * The ADT structure which holds the animal database data
 * Takes input of:
 * a 2D char array
 * an array of integers for the number of name
 * an array of booleans for whether the animal is endangered
 */



int main() {
    printCopyright();

    int chosenOption;
    const int ADD_ANIMALS_MENU_OPTION = 1;
    const int DISPLAY_ANIMALS_MENU_OPTION = 2;
    const int DISPLAY_ENDANGERED_MENU_OPTION = 3;
    const int SEARCH_ANIMALS_MENU_OPTION = 4;
    const int QUIT_MENU_OPTION = 5;

    Animal* a1 = new Animal;
    Animal* a2 = new Animal;
    Animal* a3 = new Animal;
    Animal* a4 = new Animal;
    Animal* a5 = new Animal;
    Animal* a6 = new Animal;

    a1->name = "California Puma";
    a1->typeCount = 2005;
    a1->endangered = false;
    a2->name = "Bengal Tiger";
    a2->typeCount = 97;
    a2->endangered = true;
    a3->name = "White Rhino";
    a3->typeCount = 45;
    a3->endangered = true;
    a4->name = "California Condor";
    a4->typeCount = 275;
    a4->endangered = false;
    a5->name = "Grey Wolf";
    a5->typeCount = 77;
    a5->endangered = true;
    a6->name = "Three Toed Sloth";
    a6->typeCount = 1725;
    a6->endangered = false;

    vector<Animal*> database = {a1, a2, a3, a4, a5, a6};

    const char WELCOME_TEXT[] = "Welcome to Animal Vector Database\n\n";

    const char MENU_TEXT[] = "\n1. Add Animal(s)"
                             "\n2. Display Animals"
                             "\n3. Display Endangered"
                             "\n4. Search animals"
                             "\n5. Quit";

    bool quit = true;
    cout << WELCOME_TEXT;
    while (quit) {
        chosenOption = 0;
        cout << MENU_TEXT;
        cout << "\nEnter a menu choice: ";
        cin >> chosenOption;
        while (
                !(chosenOption == ADD_ANIMALS_MENU_OPTION
                  || chosenOption == DISPLAY_ANIMALS_MENU_OPTION
                  || chosenOption == DISPLAY_ENDANGERED_MENU_OPTION
                  || chosenOption == SEARCH_ANIMALS_MENU_OPTION
                  || chosenOption == QUIT_MENU_OPTION)) {
            cout << "Invalid option";
            cout << MENU_TEXT << endl;
            cout << "Enter a menu choice: ";
            if (!(cin >> chosenOption)) {
                return 1;
            }
        }
        //Exhaustive
        switch (chosenOption) {
            case ADD_ANIMALS_MENU_OPTION: {
                addAnimals(&database);
                break;
            }
            case DISPLAY_ANIMALS_MENU_OPTION: {
                displayAnimals(database);
                break;
            }
            case DISPLAY_ENDANGERED_MENU_OPTION: {
                displayEndangered(database);
                break;
            }
            case SEARCH_ANIMALS_MENU_OPTION: {
                searchAnimals(database);
                break;
            }
            case QUIT_MENU_OPTION: {
                cout << "Thank you for using animal database";
                quit = false;
                break;
            }
        }
    }
    while (!database.empty()) {
        delete database.back();
        database.pop_back();
    }
    database.clear();
    return 0;
}


/*
 * Prints Howard CC Copyright statement
 */
void printCopyright() {
    cout << "Copyright 2023 - Howard Community College All rights reserved; Unauthorized duplication prohibited\n\n\n\n";
}


/*
* Adds animal characteristics to the animal database
* Takes input of a vector of animal structs
*/
void addAnimals(vector<Animal*>* database) {
    const int ENDANGERED_COUNT = 100;
    int animalCount;
    char *inputCstring;
    const string NONE = "none";
    string type = "Please enter the animal type (none to stop): ";
    string number = "Enter the number of animals: ";
    string error = "Negative Count, enter a positive value: ";
    string alreadyFound = "This animal is already in the database, please enter another animal";
    while (true) {
        cout << type;
        cin.ignore();
        string originalCaps;
        string input;
        bool flag;
        do {
            flag = false;
            getline(cin, input);
            originalCaps = input;
            for (char &c: input) {
                c = tolower(c);
            }
            if (input == NONE) {
                return;
            }
            inputCstring = new char[originalCaps.length() + 1];
            for (int i = 0; i < originalCaps.length(); i++) {
                inputCstring[i] = originalCaps.at(i);
            }
            inputCstring[input.length()] = '\0';\

            for(Animal* value : *database){
                if((*value).name == originalCaps){
                    cout << alreadyFound;
                    flag = true;
                }
            }
        } while (flag);
        cout << number;
        cin >> animalCount;
        while (animalCount < 0) {
            cout << error;
            cin >> animalCount;
        }
        cout << "\n";
        Animal* animal = new Animal;
        animal->typeCount = animalCount;
        animal->name = inputCstring;
        animal->endangered = animalCount < ENDANGERED_COUNT;
        database->push_back(animal);
    }
}

/*
 * displays all the name, their counts, and if they are endangered
 * Takes input of a vector of Animal structs
 */
void displayAnimals(vector<Animal*> database) {
    const char ENDANGERED_STRING[] = "\nThis animal is endangered";
    const char NOT_ENDANGERED_STRING[] = "\nThis animal is not endangered";
    selectionSortStrings(database);
    for (const Animal* ITEM: database) {
        cout << "\nAnimal: " << (*ITEM).name <<
             "\nHas a count of: " << (*ITEM).typeCount <<
             ((*ITEM).endangered ?  ENDANGERED_STRING : NOT_ENDANGERED_STRING);
        cout << "\n\n";
    }
    if(database.empty()){
        cout << "\nThere are no animals to display\n";
    }
}

void displayEndangered(vector<Animal*> database) {
    const char ENDANGERED_STRING[] = " is endangered\n";
    selectionSortStrings(database);
    for(const Animal* VALUE : database){
        if((*VALUE).endangered){
            cout << (*VALUE).name << ENDANGERED_STRING;
        }
    }
    if(database.empty()){
        cout << "\nThere are no endangered animals to display\n";
    }
}

void searchAnimals(vector<Animal*> animals) {
    selectionSortStrings(animals);
    cout << "Enter the name of the animal you are looking for: ";
    string input;
    cin.ignore();
    getline(cin, input);
    int low = 0, mid, high = animals.size();
    while (low != high) {
        mid = (low + high) / 2;
        Animal currAnimal = *animals.at(mid);
        if (strcmp(input.c_str(), currAnimal.name) == 0) {
            cout << "Animal Name: " << currAnimal.name
                 << "\nAnimal Count " << currAnimal.typeCount
                 << "\nAnimal is " << (currAnimal.endangered ? "endangered" : "not Endangered");
            return;
        } else if (strcmp(input.c_str(), currAnimal.name) > 0) {
            low = mid + 1;
        } else if (strcmp(input.c_str(), currAnimal.name) < 0) {
            high = mid - 1;
        }
    }
    cout << "\nThere is no animal entry corresponding to \"" << input << "\"" << endl;

}

void selectionSortStrings(vector<Animal*> &animals){
    for (int i = 0; i < animals.size()-1; ++i) {
        for (int j = i+1; j < animals.size(); ++j) {
            if(strcmp((*animals.at(i)).name, (*animals.at(j)).name) > 0){
                swap(animals.at(i), animals.at(j));
            }
        }
    }
}
