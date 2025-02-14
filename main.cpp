#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int parte = 0;

void dividirArchivo(){
    //int lineasArch = 262144; el salto de linea es tomado como un byte
    //int partes = 16;

    ifstream archivo("data.txt",ios::binary);

    int lineasPorArchivo = 262144;
    int parte = 0;

    while (parte < 16) {
        vector<vector<char>> lineas;
        lineas.reserve(lineasPorArchivo);

        for (int i = 0; i < lineasPorArchivo; i++) {
            vector<char> linea(257);
            if (!archivo.read(linea.data(), 257)) break;
            lineas.push_back(linea);
        }

        sort(lineas.begin(), lineas.end());

        ofstream archfin("Archivo0" + to_string(parte) + ".txt", ios::binary);
        for (const auto& linea : lineas) {
            archfin.write(linea.data(), 257);
        }

        parte++;
    }

    archivo.close();
}

void ordenararchivos() {
    ios::sync_with_stdio(false); //Optimiza algunos procesos de enviar y recibir datos pero desactiva el uso de cin y cout
    int currarch = 0;
    string linea0, linea1, nombrefinal;

    while (currarch < 16) {
        nombrefinal = (currarch == 14) ? "sorted_complete.txt" : "Archivo0" + to_string(currarch + 1) + ".txt";
        string archivo0 = (currarch == 0) ? "Archivo0.txt" : "Archivo0" + to_string(currarch) + ".txt";
        string archivo1 = "Archivo" + to_string(currarch + 1) + ".txt";

        ofstream archfin(nombrefinal, ios::binary);
        ifstream arch0(archivo0, ios::binary); //Archivo 0 de entrada, este son los 0, 01, 02
        ifstream arch1(archivo1, ios::binary); //Archivo 1 de entrada son los 1,2,3,4

        vector<char> buffer0(257), buffer1(257); //Se crean 2 buffers uno para cada linea los cuales almacenan las lineas en char
        bool tiene0 = static_cast<bool> (arch0.read(buffer0.data(), 257)); //Se crean boolenados y se leen datos con el buffer
        bool tiene1 = static_cast<bool> (arch1.read(buffer1.data(), 257));

        //Lo del static bool fue obtenido de https://stackoverflow.com/questions/38659115/make-fails-with-error-cannot-convert-stdistream-aka-stdbasic-istreamchar
        //Sirve para realizar la conversion y que se pueda utilizar como un booleano el si obtiene los caracteres o no

        while (tiene0 && tiene1) { //Recorremos los archivos hasta que uno se quede sin caracteres
            if (buffer0 < buffer1) {
                archfin.write(buffer0.data(), 257); //Se escribe en el nuevo archivo creado
                tiene0 = static_cast<bool>(arch0.read(buffer0.data(), 257)); //El boolenao toma true en caso de que aun haiga datos y a su vez se ponen en el buffer
            } else {
                archfin.write(buffer1.data(), 257);
                tiene1 = static_cast<bool>(arch1.read(buffer1.data(), 257));
            }
        }

        while (arch0.read(buffer0.data(), 257)) { //Si salio del otro bucle entonces uno de los archivos llego al final en caso de que sea el arch1
            linea0 = string(buffer0.data(), arch0.gcount()); //Mientras que se pueda seguir leyendo se agregan al archivofinal
            archfin.write(linea0.data(), linea0.size());
        }

        while (arch1.read(buffer1.data(), 257)) { //en caso de que se haya acabado el arch0
            linea1 = string(buffer1.data(), arch1.gcount());//Mientras que se pueda seguir leyendo se agregan al archivofinal
            archfin.write(linea1.data(), linea1.size());
        }

        arch0.close();
        arch1.close();
        archfin.close();
        currarch++;
    }
}


int main(){
    dividirArchivo();

    return 0;
}