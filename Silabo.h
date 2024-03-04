#ifndef SILABO_H
#define SILABO_H

#include <Ingenieria.h>
#include <string>
#include <fstream>
#include <Estado.h>
#include <vector>

using std::string;
using std::ofstream;

template <typename T>
class Silabo {
    private:
        int id; // Para mantener track de los archivos
        int numRevisiones; // Para contar cuantas veces se ha revisado el silabo
        string nombre;
        ofstream archivo;
        Estado estado;
        string observacion; // Para que digan que quieren de cambio
        std::vector<Ingenieria> carreras;

    public:

        string getNombre() {
            return nombre;
        }

        Estado getEstado(){ // Para obtener el estado asignado desde el enum
            return estado;
        }
        const std::vector<Ingenieria> &getCarreras() const;
};

#endif // SILABO_H
