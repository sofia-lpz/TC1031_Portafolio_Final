#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

struct entry {
  string mes;
  int dia;
  string hora;
  string ip;
  string comm;
};

int mtoi(string mes) {
  map<string, int> dictMeses{{"Jan", 1}, {"Feb", 2},  {"Mar", 3},  {"Apr", 4},
                             {"May", 5}, {"Jun", 6},  {"Jul", 7},  {"Aug", 8},
                             {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}};
  return dictMeses[mes];
} 
int converttosec(int dia, string hora) {
  int num;
  int segundos;
  istringstream ss(hora);
  char delimiter; // To store the delimiter (colon)
  for (int i = 2; i >= 0; i--) {
    ss >> num;
    segundos = segundos + (num * pow(60, i));
    ss >> delimiter; // Read and discard the delimiter
  }
  return segundos + (dia - 1) * 86400;
}
 
bool isSorted(const vector<entry> &datos) {
    for (int i = 1; i < datos.size(); i++) {
        if (mtoi(datos[i].mes) < mtoi(datos[i - 1].mes) ||
            (mtoi(datos[i].mes) == mtoi(datos[i - 1].mes) &&
             converttosec(datos[i].dia, datos[i].hora) < converttosec(datos[i - 1].dia, datos[i].hora))) {
            return false;
        }
    }
    return true;
}
void bogosort(vector<entry> &datos) {
    while (!isSorted(datos)) {
        random_shuffle(datos.begin(), datos.end());
    }
}

void ordenaInsercion(vector<struct entry> &datos) {
  for (int i = 0; i < datos.size(); i++) { // O(n)
    for (int j = i; j > 0; j--) {          // O(n)
      if ((mtoi(datos[j].mes) < mtoi(datos[j - 1].mes))) {
        swap(datos[j], datos[j - 1]);
      }
      else if (datos[j].mes == datos[j - 1].mes) {
        if (converttosec(datos[j].dia, datos[j].hora) <
            converttosec(datos[j - 1].dia, datos[j].hora)) {
          swap(datos[j], datos[j - 1]);
        }
      } else
        break;
    }
  }
} // O(n^2) en el peor caso debido a su for loop anidado dentro de otro for loop

bool leeDatos(vector<struct entry> &datos, string archivo) {
  ifstream miArchivo(archivo);
  if (miArchivo.is_open()) {
    string mes, hora, ip, comm;
    int dia;

    while (miArchivo >> mes >> dia >> hora >> ip) {
      getline(miArchivo, comm);
      datos.push_back({mes, dia, hora, ip, comm});
    }
    miArchivo.close();
    return true;
  } else {
    return false;
  }
} // O(n) - Depende del tamaño del vector

void nuevaBitacora(const vector<struct entry> &datos, int imes, int idia, int fmes, int fdia) {
  ofstream f1("bitacora_ordenada");
  for (const entry &registro : datos) {
    int mes = mtoi(registro.mes);
    if ((mes > imes || (mes == imes && registro.dia >= idia)) &&
        (mes < fmes || (mes == fmes && registro.dia <= fdia))) {
      f1 << registro.mes << " " << registro.dia << " " << registro.hora << " "
         << registro.ip << " " << registro.comm << endl;
    }
  }
  f1.close();
}
// O(n) - Depende del tamaño de 'datos'; su nuevo ordenamiento no afecta la
// complejidad de tiempo

int main() {
  vector<struct entry> datos;

  if (leeDatos(datos, "bitacora.txt")) {
    int imes, idia, fmes, fdia;
    string simes, sfmes;
    
    ordenaInsercion(datos);
    cout << "ordenado con insertion sort" <<endl;

    cout << "Introduce mes de inicio (formato Jan, Feb, etc) ";
    cin >> simes;
    imes = mtoi(simes);
    cout << "Introduce día de inicio ";
    cin >> idia;

    cout << "Introduce mes de fin (formato Jan, Feb, etc) ";
    cin >> sfmes;
    fmes = mtoi(sfmes);
    cout << "Introduce día de fin ";
    cin >> fdia;
    nuevaBitacora(datos, imes, idia, fmes, fdia);
    return 0;
  }

  cout << "No se pudo leer el archivo";
  return 0;
}
