#ifndef SILABO_H
#define SILABO_H

#include <Ingenieria.h>
#include <string>
#include <fstream>
#include <Estado.h>
#include <vector>

using std::string;
using std::ofstream;

class Silabo {
    private:
        string facultad;
        std::vector<Ingenieria> carreras;
        string nombre;
        string codigoClase;
        string ruta;
        ofstream archivo;

        Estado estado;
        string observacion; // Para que digan que quieren de cambio

        int id; // Para mantener track de los archivos
        int numRevisiones; // Para contar cuantas veces se ha revisado el silabo

    public:

        Silabo(string facultad, std::vector<Ingenieria> carreras, string nombre, string codigoClase, string ruta, ofstream archivo, Estado estado, string observacion, int id, int numRevisiones)
            : facultad(facultad), carreras(carreras), nombre(nombre), estado(estado), observacion(observacion), id(id), numRevisiones(numRevisiones){
        }

        string getNombre() {
            return nombre;
        }

        Estado getEstado(){ // Para obtener el estado asignado desde el enum
            return estado;
        }
        const std::vector<Ingenieria> &getCarreras() const;

        long toNum()
        {
            long val = 0;
            for (int i = 0; i < nombre.size(); i++)
            {
                char c = nombre[i];
                val += c;
            }

            return val;
        }
};

#endif // SILABO_H
