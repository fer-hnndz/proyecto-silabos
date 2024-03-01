#ifndef SILABO_H
#define SILABO_H

#include <Ingenieria.h>
#include <string>
#include <fstream>
#include <Estado.h>

using std::string;
using std::ofstream;

template <typename T>
class Silabo {
    private:
        int id; // Para mantener track de los archivos
        int numRevisiones; // Para contar cuantas veces se ha revisado el silabo
        Ingenieria carrera;
        string nombre;
        ofstream archivo;
        Estado estado;
    public:
        // Getters
        Ingenieria getCarrera() {
            return carrera;
        }

        string getNombre() {
            return nombre;
        }

        Estado getEstado(){ // Para obtener el estado asignado desde el enum
            return estado;
        }
};

#endif // SILABO_H
