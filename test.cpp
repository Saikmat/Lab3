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
#include <fstream>

using namespace std;

struct Animal {
    char* name = new char[25];
    char* species = new char[25];
    int typecount;
    bool endangered;

}__attribute__((packed));

void readAnimal(vector<Animal*>& animals, fstream&);

int main() {

    const string ANIMAL_RECORD_LOCATION = R"(C:\Users\SaiKM\CLionProjects\Lab3\animal.dat)";

    fstream animalRecords;
    animalRecords.open(ANIMAL_RECORD_LOCATION, fstream::in | fstream::binary);
    vector<Animal*> database;
    readAnimal(database, animalRecords);

    for (const auto &ITEM: database) {
        if(ITEM == nullptr){
            continue;
        }
        cout << ITEM->name << ITEM->species << endl;
    }
    return 0;
}


/*
 * Not working
 */
void readAnimal(vector<Animal *> &animals, fstream &stream) {
   while(stream){
       Animal* animal = new Animal;
       stream.read(reinterpret_cast<char *>(&animal), sizeof(Animal));
       animals.push_back(animal);
   }
}