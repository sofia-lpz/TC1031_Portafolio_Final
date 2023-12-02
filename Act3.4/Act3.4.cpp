/*
Nicole Davila
Sofia Moreno Lopez A01028251

NOTA: para el funcionameinto de este codigo, debe usarse
la lista ordenada que salio de la actividad 2.3 (la
evidencia pasada) como indica canvas

si no, apareceran ips duplicadas

Usamos un binary heap como un caso especial de arbol de busqueda binaria
*/

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <sstream>
#include <vector>
using namespace std;

struct entry {
  string mes;
  int dia;
  string hora;
  string ip;
  string comm;
  int key = 1;
};

string extractIP(const string &ipWithPort) {
  return ipWithPort.substr(0, ipWithPort.find(':'));
}
// Complejidad de extractIP: O(n)

bool leeDatos(vector<struct entry> &datos, string archivo) {
  ifstream miArchivo(archivo); // Abre el archivo
  if (miArchivo.is_open()) { // Comprueba que el archivo se abrió correctamente
    string mes, hora, ipWithPort, comm;
    int dia;

    while (miArchivo >> mes >> dia >> hora >>
           ipWithPort) {                 // Lee los datos del archivo
      getline(miArchivo, comm);          // Lee el resto de la línea
      string ip = extractIP(ipWithPort); // Extrae la IP del registro
      datos.push_back(
          {mes, dia, hora, ip, comm}); // Almacena los datos en el vector
    }
    miArchivo.close(); // Cierra el archivo
    return true;       // Retorna verdadero si se pudo leer el archivo
  } else {
    return false; // Retorna falso si no se pudo abrir el archivo
  }
}
// Complejidad de leeDatos: O(n)

struct keyCompare {
  bool operator()(const entry &a, const entry &b) const {
    return a.key < b.key; // Ordena por llave
  }
};
// Complejidad de keyCompare: O(1)
// Overload de operador, maxheap

void nuevaBitacoraOrdenada(const list<struct entry> &datos) {
  ofstream f1("bitacora_ordenada");
  for (const entry &registro : datos) {
    f1 << registro.mes << " " << registro.dia << " " << registro.hora << " "
       << registro.ip << registro.comm << "\n";
  }
  f1.close();
}

void printEntry(const struct entry &myEntry) {
  cout << myEntry.ip << "           " << myEntry.key << endl;
}
// Complejidad de printEntry: O(1)

void design() {
  cout << "ip (sin puerto)"
       << "     numero de accesos" << endl; // Imprime el encabezado
}
// Complejidad de design: O(1)

int main() {
  vector<struct entry> datos; // Vector para almacenar los datos
  priority_queue<struct entry, vector<struct entry>, keyCompare> binaryheap;

  string bitacora = "bitacora_ordenada.txt";

  if (leeDatos(datos, bitacora)) {
    cout << "Se leyó " << bitacora << " con éxito."
         << "\n\n";

    // Mapa para almacenar las ip y su frecuencia
    map<string, int> cuentaIp;
    for (int i = 0; i < datos.size(); i++) {
      cuentaIp[datos[i].ip]++;
    }
    // O(n)

    for (int i = 0; i < datos.size(); i++) {
      datos[i].key = cuentaIp[datos[i].ip]; // Guarda la cantidad de veces que
                                            // se repite la ip

      if (i == 0 || (datos[i].ip != datos[i - 1].ip)) {
        binaryheap.push(datos[i]);
        /* No guarda en el árbol binario los entries cuyos
        ips que se repiten*/
      }
    }

    cout << "Los 5 ips con más accesos: " << endl;

    design();

    for (int i = 0; i < 5; i++) {
      printEntry(
          binaryheap.top()); // Imprime el entry con la mayor llave (maxheap)
      binaryheap.pop();      // Elimina el entry con la mayor llave
    }
    return 0;
  }

  cout << "No se pudo leer la bitácora.";
  return 0;
}
