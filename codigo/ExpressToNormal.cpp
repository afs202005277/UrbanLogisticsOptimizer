#include <iostream>
#include <string>
#include <fstream>
using namespace std;

. // não percebo porque é que isto existe
int main() {
    ifstream input("../input/encomendas.txt");
    ofstream output("../input/encomendas2.txt");
    string line;
    while (getline(input, line)){
        line = line.substr(0, line.find_last_of(' '));
        output << line << endl;
    }
    input.close();
    output.close();
}
