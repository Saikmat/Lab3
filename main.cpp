/*
* Copyright 2023 - Howard Community College All rights reserved; Unauthorized duplication prohibited.
* Name: Sai Matukumalli
* Class: CMSY-171
* Instructor: Justyn Crook
* Program Name: Lab 3
* Program Description:
*/


#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>

using namespace std;

struct Animal {
    char name[25];
    char species[25];
    int typeCount;
    bool endangered;
};

void printCopyright();

void addAnimals(vector<Animal *> *database, vector<string> species);

void displayAnimals(vector<Animal*> database);

void displayEndangered(vector<Animal*> database);

void searchAnimals(vector<Animal *> animals, vector<string> species, fstream &stream);

void selectionSortStrings(vector<Animal*> &animals);

void readAnimal(vector<Animal*>& animals, fstream& stream);

void readSpecies(vector<string>& animals, fstream&);

void refreshFile(vector<Animal *>& animals, fstream &stream);

void updateRecordInVector(Animal* animal, vector<string> species);

void updateRecordInFile(Animal *animal, int location, fstream &stream);

void updateEndangeredStatus(vector<Animal *> &animals, const int count);

int main() {
    printCopyright();

    int chosenOption;
    const int ENDANGERED_COUNT = 100;
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
    readAnimal(database, animalRecords);
    updateEndangeredStatus(database, ENDANGERED_COUNT);
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
        switch (chosenOption) {
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
                animalRecords.open(ANIMAL_RECORD_LOCATION, ios::app);
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

void updateEndangeredStatus(vector<Animal *> &animals, const int count) {
    for (Animal *animal: animals) {
        animal->endangered = animal->typeCount < count;
    }
}


/*
 * Prints Howard CC Copyright statement
 */
void printCopyright() {
    cout << "Copyright 2023 - Howard Community College All rights reserved; Unauthorized duplication prohibited\n\n\n\n";
}

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
        cout << speciesText;
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
        strcpy(animal->name, inputCstring);
        strcpy(animal->species, speciesName.c_str());
        animal->endangered = animalCount < ENDANGERED_COUNT;
        database->push_back(animal);
        selectionSortStrings(*database);
    }
}

void refreshFile(vector<Animal *>& animals, fstream &stream) {
    stream.seekg(ios::beg);
    selectionSortStrings(animals);
    for (const auto &animal: animals) {
        stream.write(animal->name, 25*sizeof(char));
        stream.write(animal->species, 25*sizeof(char));
    }
}


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

void searchAnimals(vector<Animal*> animals, vector<string> speciesList, fstream &stream) {
    selectionSortStrings(animals);
    cout << "Enter the name of the animal you are looking for: ";
    int low = 0, mid, high = animals.size();
    string input;

    cin.ignore();
    getline(cin, input);

    while (low != high) {
        mid = (low + high) / 2;
        Animal currAnimal = *animals.at(mid);
        if (strcmp(input.c_str(), currAnimal.name) == 0) {
            cout << "Animal Name: " << currAnimal.name
                 << "\nAnimal Count " << currAnimal.typeCount
                 << "\nAnimal is " << (currAnimal.endangered ? "endangered" : "not Endangered");
            updateRecordInVector(&currAnimal, speciesList);
            updateRecordInFile(&currAnimal, mid, stream);
            return;
        } else if (strcmp(input.c_str(), currAnimal.name) > 0) {
            high = mid - 1;
        } else if (strcmp(input.c_str(), currAnimal.name) < 0) {
            low = mid + 1;
        }
    }

    cout << "\nThere is no animal entry corresponding to \"" << input << "\"" << endl;

}

void updateRecordInFile(Animal *animal, int location, fstream &stream) {
    stream.seekg(location*sizeof(Animal), ios::beg);
    stream.seekp(-1*sizeof(Animal), ios::cur);
    stream.write(reinterpret_cast<char*>(&animal), sizeof(Animal));
}

void updateRecordInVector(Animal* animal, vector<string> species) {
    const string animalUpdate = "Enter the value you want to change animal to(! for no change)";
    const string speciesUpdate = "Enter the new species of the animal(! for no change)";
    const string countUpdate = "Enter the new count of animals(! for no change)";
    char userChange;
    cout << "Do you want to update the record?";
    userChange = cin.get();
    while(tolower(userChange) != 'y' || tolower(userChange) != 'n'){
        cout << "enter a valid value <y or n>";
        userChange = cin.get();
    }
    string temp;
    if(userChange == 'y'){
        cout << animalUpdate;
        getline(cin, temp);
        if(temp != "!"){
            strcpy(animal->name, temp.c_str());
        }

        cout << speciesUpdate;
        for (int i = 0; i < species.size(); ++i) {
            cout << i+1 << ". " << species.at(i) << endl;
        }
        getline(cin, temp);
        if(temp != "!"){
            strcpy(animal->species, species.at(stoi(temp, nullptr, 10)).c_str());
        }

        cout << countUpdate;
        getline(cin, temp);
        if(temp != "!"){
            animal->typeCount = stoi(temp, nullptr, 10);
        }
    }
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

/*
 * Functional
 */
void readAnimal(vector<Animal *> &animals, fstream &stream) {
    while (stream) {
        if(!stream.good() || stream.eof()) {
            cout << "read failed";
            return;
        }
        Animal* animal = new Animal;
        animals.push_back(animal);
        stream.read(reinterpret_cast<char*>(animals.back()), sizeof(Animal));
    }
}

/*
 * Functioning properly
 */
void readSpecies(vector<string> &animals, fstream &stream) {
    while(!stream.eof()){
        char *str = new char[25];
        stream.getline(str, 25);
        animals.push_back(str);
    }
}