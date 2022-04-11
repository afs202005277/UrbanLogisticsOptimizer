#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
using namespace std;

. // este tambem não

string randomPlateGenerator(){
    string plate;
    plate += (char) (65 + (rand() % ( 90 - 65 + 1 )));
    plate += (char) (65 + (rand() % ( 90 - 65 + 1 )));
    plate += (char) (48 + (rand() % ( 57 - 48 + 1 )));
    plate += (char) (48 + (rand() % ( 57 - 48 + 1 )));
    plate += (char) (65 + (rand() % ( 90 - 65 + 1 )));
    plate += (char) (65 + (rand() % ( 90 - 65 + 1 )));
    return plate;
}

int main() {
    unordered_set<string> usedPlates;
    randomPlateGenerator();
    ifstream input("../input/carrinhas.txt");
    ofstream output("../input/carrinhas2.txt");
    string line;
    getline(input, line);
    line += " matricula";
    output << line << endl;
    while(getline(input, line)){
        string plate;
        do{
            plate = randomPlateGenerator();
        } while(!usedPlates.insert(plate).second);
        output << line + " " + plate << endl;
    }
}