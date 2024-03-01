#ifndef SILABO_H
#define SILABO_H

#include <Ingenieria.h>
#include <string>
#include <fstream>

using std::string;
using std::ofstream;

template <typename T>
class Silabo {
    private:
        int id; // Para mantener track de los archivos
        Ingenieria carrera;
        string nombre;
        ofstream archivo;
    public:
        Ingenieria getCarrera() {
            return carrera;
        }

        string getNombre() {
            return nombre;
        }

};

#endif // SILABO_H
