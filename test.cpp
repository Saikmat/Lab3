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
    char* name = new char[25];
    char* species = new char[25];

}__attribute__((packed));

void printCopyright();

void addAnimals(vector<Animal*>* database, fstream &stream);

void displayAnimals(vector<Animal*> database);

void displayEndangered(vector<Animal*> database);

void searchAnimals(vector<Animal*> animals);

void selectionSortStrings(vector<Animal*> &animals);

void readAnimal(vector<Animal*>& animals, fstream&);

void readSpecies(vector<string>& animals, fstream&);

void updateFile(vector<Animal *>& animals, fstream &stream);

int main() {
    printCopyright();

    int chosenOption;
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

    for (const auto &ITEM: database) {
        cout << ITEM->name << ITEM->species << endl;
    }
    return 0;
}


/*
 * Prints Howard CC Copyright statement
 */
void printCopyright() {
    cout << "Copyright 2023 - Howard Community College All rights reserved; Unauthorized duplication prohibited\n\n\n\n";
}



/*
 * Not working
 */
void readAnimal(vector<Animal *> &animals, fstream &stream) {
    while (stream) {
        if(!stream.good() || stream.eof()) {
            cout << "read failed";
            return;
        }
        Animal* animal = new Animal;
        Animal a = *animal;
        stream.getline(reinterpret_cast<char*>(&a), sizeof(Animal));
        animals.push_back(&a);
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
