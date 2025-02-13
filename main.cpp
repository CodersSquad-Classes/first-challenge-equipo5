#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;



void dividirArchivo(){
    //int lineasArch = 262144; el salto de linea es tomado como un byte
    //int partes = 16;

    ifstream archivo("data.txt",ios::binary);

    vector<char> buffer(67371008);

    int parte = 0;

    while (parte<16)
    {
        ofstream archfin("Archivo"+to_string(parte)+".txt",ios::binary);
        archivo.read(buffer.data(), buffer.size());
        archfin.write(buffer.data(), 67371008);
        parte++;
        archfin.close();
    }
}

int main(){
    dividirArchivo();
    return 0;
}