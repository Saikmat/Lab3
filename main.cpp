/*
* Copyright 2024 - Howard Community College All rights reserved; Unauthorized duplication prohibited.
* Name: Sai Matukumalli
* Class: CMSY-171
* Instructor: Justin Lieberman
* Program Name: Lab 3
* Program Description: This program reads animals from a file, puts them into our animal database vector, and allowing us to manipulate the data points.
 * The program allows us to manipulate the file when animals are added or edited as well.
*/


#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>

using namespace std;

const int MAX_LENGTH = 25;

struct Animal {
    char name[MAX_LENGTH];
    char species[MAX_LENGTH];
    int typeCount;
    bool endangered;
};

void printCopyright();

void addAnimals(vector<Animal *> *database, vector<string> species);

void displayAnimals(vector<Animal*> database);

void displayEndangered(vector<Animal*> database);

void searchAnimals(vector<Animal *> animals, const vector<string>& species, fstream &stream);

void selectionSortStrings(vector<Animal*> &animals);

void readAnimal(vector<Animal*>& animals, fstream& stream, int ENDANGERED_COUNT);

void readSpecies(vector<string>& animals, fstream&);

void refreshFile(vector<Animal *>& animals, fstream &stream);

void updateRecordInVector(vector<Animal *> animal, int loc, vector<string> species);

void updateRecordInFile(vector<Animal *> animals, int location, fstream &stream);

void updateEndangered(vector<Animal *> *animals, int ENDANGERED_COUNT);

int main() {
    printCopyright();

    int chosenOption;
    const int ENDANGERED_COUNT  = 100;
    const int ADD_ANIMALS_MENU_OPTION = 1;
    const int DISPLAY_ANIMALS_MENU_OPTION = 2;
    const int DISPLAY_ENDANGERED_MENU_OPTION = 3;
    const int SEARCH_ANIMALS_MENU_OPTION = 4;
    const int QUIT_MENU_OPTION = 5;
    const string ANIMAL_RECORD_LOCATION = R"(C:\Users\SaiKM\CLionProjects\Lab3\animal.dat)";
    const string SPECIES_RECORD_LOCATION = R"(C:\Users\SaiKM\CLionProjects\Lab3\species.txt)";

    fstream animalRecords;
    animalRecords.open(ANIMAL_RECORD_LOCATION, fstream::in | fstream::out | fstream::binary);
    vector<Animal*> database;
    readAnimal(database, animalRecords, ENDANGERED_COUNT);
    animalRecords.close();
    animalRecords.open(ANIMAL_RECORD_LOCATION, ios::binary | ios::out);
    refreshFile(database, animalRecords);
    animalRecords.close();

    fstream speciesRecords;
    speciesRecords.open(SPECIES_RECORD_LOCATION);
    vector<string> speciesList;
    readSpecies(speciesList, speciesRecords);

    const char WELCOME_TEXT[] = "Welcome to Animal Vector Database\n\n";
    const char MENU_TEXT[] = "\n1. Add Animal(s)"
                             "\n2. Display Animals"
                             "\n3. Display Endangered"
                             "\n4. Search animals"
                             "\n5. Quit";
    cout << WELCOME_TEXT;

    bool quit = true;
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
        switch (chosenOption) { // NOLINT(*-multiway-paths-covered)
            case ADD_ANIMALS_MENU_OPTION: {
                addAnimals(&database, speciesList);
                animalRecords.open(ANIMAL_RECORD_LOCATION, ios::out | ios::binary);
                refreshFile(database, animalRecords);
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
                animalRecords.open(ANIMAL_RECORD_LOCATION, ios::binary | ios::in | ios::out);
                searchAnimals(database, speciesList, animalRecords);
                break;
            }
            case QUIT_MENU_OPTION: {
                cout << "Thank you for using animal database";
                quit = false;
                break;
            }
        }
    }

    animalRecords.clear();
    speciesRecords.clear();
    animalRecords.close();
    speciesRecords.close();
    while (!database.empty()) {
        delete database.back();
        database.pop_back();
    }
    database.clear();
    speciesList.clear();

    return 0;
}


/*
 * Prints Howard CC Copyright statement
 */
void printCopyright() {
    cout << "Copyright 2024 - Howard Community College All rights reserved; Unauthorized duplication prohibited\n\n\n\n";
}

/*
 * Adds animals to the vector
 * Takes input of the animal database, and the list of species
 */
void addAnimals(vector<Animal *> *database, vector<string> species) {
    const int ENDANGERED_COUNT = 100;
    int animalCount;
    string speciesName;
    char *inputCstring;
    const string NONE = "none";
    string type = "Please enter the animal type (none to stop): ";
    string speciesText = "Please enter the animal species from the menu";
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
        cout << speciesText << "\n";
        for (int i = 0; i < species.size(); ++i) {
            cout << i+1 << ". " + species.at(i) << endl;
        }
        int speciesValue = 0;
        cin >> speciesValue;
        while(speciesValue <= 0 || speciesValue > species.size()) {
            cout << &"Invalid entry, enter a value between 1 and " [ species.size()];
            cin >> speciesValue;
        }
        cout << number;
        cin >> animalCount;
        while (animalCount < 0) {
            cout << error;
            cin >> animalCount;
        }
        cout << "\n";
        Animal* animal = new Animal;
        animal->typeCount = animalCount;
        strncpy_s(animal->name, MAX_LENGTH, inputCstring, MAX_LENGTH);
        strncpy_s(animal->species, MAX_LENGTH, speciesName.c_str(), MAX_LENGTH);
        animal->endangered = animalCount < ENDANGERED_COUNT;
        database->push_back(animal);
        selectionSortStrings(*database);
    }
}

/*
 * Rewrites the entire file in order of the vector
 * Takes the vector and the filestream
 */
void refreshFile(vector<Animal *>& animals, fstream &stream) {
    stream.seekp(ios::beg);
    for (int i = 0; i < animals.size(); i++) {
        stream.write(reinterpret_cast<char*>(animals.at(i)), sizeof(Animal));
    }
}

/*
 * Displays all the animals, including their name, species, count, and endangered status
 * Takes the animal database input
 */
void displayAnimals(vector<Animal*> database) {
    const char ENDANGERED_STRING[] = "\nThis animal is endangered";
    const char NOT_ENDANGERED_STRING[] = "\nThis animal is not endangered";
    selectionSortStrings(database);
    for (const Animal* ITEM: database) {
        cout << "\nAnimal: " << (*ITEM).name <<
            "\nOf species " << (*ITEM).species <<
             "\nHas a count of: " << (*ITEM).typeCount <<
             ((*ITEM).endangered ?  ENDANGERED_STRING : NOT_ENDANGERED_STRING);
        cout << "\n\n";
    }
    if(database.empty()){
        cout << "\nThere are no animals to display\n";
    }
}

/*
 * Displays only the endangered animals
 * Takes input of the database
 */
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

/*
 * Searches the animals using binary search, and allows the record values to be updated, before rewriting to the file
 * Takes input of the animals database, the list of species, and the filestream
 */
void searchAnimals(vector<Animal*> animals, const vector<string>& speciesList, fstream &stream) {
    selectionSortStrings(animals);
    cout << "Enter the name of the animal you are looking for: ";
    int low = 0, mid, high = animals.size()-1;
    string input;

    cin.ignore();
    getline(cin, input);

    while (low <= high) {
        mid = (low + high) / 2;
        Animal currAnimal = *animals.at(mid);
        if (strcmp(input.c_str(), currAnimal.name) == 0) {
            cout << "Animal Name: " << currAnimal.name
                 << "\nAnimal Species: " << currAnimal.species
                 << "\nAnimal Count " << currAnimal.typeCount
                 << "\nAnimal is " << (currAnimal.endangered ? "endangered" : "not Endangered");
            char userChange;
            cout << "\n\nDo you want to update the record?";
            cin >> userChange;
            while(tolower(userChange) != 'y' && tolower(userChange) != 'n'){
                cout << "enter a valid value <y or n>";
                cin >> userChange;
            }
            userChange = tolower(userChange);
            if(userChange == 'y'){
                updateRecordInVector(animals, mid, speciesList);
                updateRecordInFile(animals, mid, stream);
            }
            return;
        } else if (strcmp(input.c_str(), currAnimal.name) > 0) {
            low = mid + 1;
        } else if (strcmp(input.c_str(), currAnimal.name) < 0) {
            high = mid - 1;
        }
    }

    cout << "\nThere is no animal entry corresponding to \"" << input << "\"" << endl;
}

/*
 * Individually writes animals into the file without clearing it each time
 * Takes the database, the location that it needs to be written to, and the filestream
 */
void updateRecordInFile(vector<Animal*> animals, int location, fstream &stream) {
    stream.seekg(location * sizeof(Animal), ios::beg);
    stream.seekp(ios::beg + location * sizeof(Animal));
    stream.write(reinterpret_cast <char*> (animals.at(location)), sizeof(Animal));
    stream.close();
}

/*
 * Allows individual elements in the vector to be updated, helper method for search
 */
void updateRecordInVector(vector<Animal*> animals, int loc, vector<string> species) {
    const string animalUpdate = "Enter the value you want to change animal to(! for no change)";
    const string speciesUpdate = "Enter the new species of the animal";
    const string countUpdate = "Enter the new count of animals";

    string temp;
    cout << animalUpdate;
    cin.ignore();
    getline(cin, temp);
    if(temp != "!"){
        for (char & specie : animals.at(loc)->species) {
            specie = '0';
        }
        strncpy_s(animals.at(loc)->name, MAX_LENGTH, temp.c_str(), MAX_LENGTH);
    }

    cout << speciesUpdate << endl;
    for (int i = 0; i < species.size(); ++i) {
        cout << i+1 << ". " << species.at(i) << endl;
    }

    int numberInput;
    cin >> numberInput;
    while(numberInput < 0 || numberInput > species.size()){
        cout << "\nThat is an invalid option, enter a value between 0 and " << species.size();
    }
    for (char & specie : animals.at(loc)->species) {
        specie = '0';
    }
    strncpy_s(animals.at(loc)->species, animals.size(), species.at(numberInput).c_str(), animals.size());

    cout << countUpdate;
    cin >> numberInput;
    while(numberInput < 0){
        cout << "Negative Number, please enter a positive numberInput for count";
    }
    animals.at(loc)->typeCount = numberInput;
}

/*
 * Sorts the list of animals using a selection sort in the vector
 * Takes the animals vector
 */
void selectionSortStrings(vector<Animal*> &animals) {
    for (int i = 0; i < animals.size() - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < animals.size(); ++j) {
            if (strcmp((*animals.at(j)).name, (*animals.at(min_idx)).name) > 0) {
                min_idx = j;
            }
            swap(animals.at(min_idx), animals.at(j));
        }
    }
}

/*
 * Reads the animals out of the file and adds them into the vector, and then sorts the vector
 */
void readAnimal(vector<Animal *> &animals, fstream &stream, const int ENDANGERED_COUNT) {
    while (!stream.eof()) {
        if(!stream.good() || stream.eof()) {
            cout << "read failed";
            return;
        }
        Animal* animal = new Animal;
        animals.push_back(animal);
        stream.read(reinterpret_cast<char*>(animals.back()), sizeof(Animal));
    }
    animals.pop_back();
    updateEndangered(&animals, ENDANGERED_COUNT);
    selectionSortStrings(animals);
}

/*
 * Updates whether the animals are endangered in the vector
 * Takes input of the animals database, and the number of animals needed to be endangered.
 */
void updateEndangered(vector<Animal *> *animals, const int ENDANGERED_COUNT) {
    for (Animal *animal : *animals) {
        animal->endangered = animal->typeCount < ENDANGERED_COUNT;
    }
}

/*
 * Reads the values from the species list and puts them into a vector
 * Takes input of the filestream and the vector of strings to put speices names.
 */
void readSpecies(vector<string> &animals, fstream &stream) {
    while(!stream.eof()){
        char *str = new char[25];
        stream.getline(str, 25);
        animals.emplace_back(str);

    }
}