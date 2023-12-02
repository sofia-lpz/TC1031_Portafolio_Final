//Nicole Davila
//Sofia Moreno Lopez
#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <map>
using namespace std;

struct entry {
  string mes;
  int dia;
  string hora;
  string ip;
  string comm;
};

bool leeDatos(list<struct entry> &datos, string archivo) {
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
}

void nuevaBitacora(const list<struct entry> &datos, const string &ipSearchStart, const string &ipSearchEnd) {
  ofstream f1("bitacora_filtrada");
  for (const entry &registro : datos) {
    if (registro.ip >= ipSearchStart && registro.ip <= ipSearchEnd) {
      f1 << registro.mes << " " << registro.dia << " " << registro.hora << " "
         << registro.ip << registro.comm << "\n";
    }
  }
  f1.close();
}

bool operador(const entry& a, const entry& b) {
  return a.ip < b.ip;
}

int main() {
  list<struct entry> datos;

  if (leeDatos(datos, "bitacora.txt")) {

    datos.sort(operador);

    cout << "Se leyó y ordenó la bitacora con éxito." << "\n";
    string ipSearchStart, ipSearchEnd;

    cout << "Ingrese la ip de inicio de búsqueda: ";
    cin >> ipSearchStart;

    cout << "Ingrese la ip final de búsqueda: ";
    cin >> ipSearchEnd;

    nuevaBitacora(datos, ipSearchStart, ipSearchEnd);

    return 0;
  }
  cout << "No se pudo leer la bitacora.";
  return 0;
}
