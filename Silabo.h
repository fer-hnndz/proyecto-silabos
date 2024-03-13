#ifndef SILABO_H
#define SILABO_H

#include <Ingenieria.h>
#include <string>
#include <fstream>
#include <Estado.h>
#include <vector>
#include <QString>

using std::string;
using std::ofstream;

class Silabo {
    private:
        string facultad;
        std::vector<string> carreras;
        string nombre;
        string codigoClase;
        QString ruta;

        Estado estado;
        string observacion; // Para que digan que quieren de cambio

        int id; // Para mantener track de los archivos
        int numRevisiones; // Para contar cuantas veces se ha revisado el silabo

    public:

        Silabo(string facultad, std::vector<string> carreras, string nombre, string codigoClase, QString ruta, Estado estado, string observacion, int id, int numRevisiones)
            : facultad(facultad), carreras(carreras), nombre(nombre), estado(estado), observacion(observacion), id(id), numRevisiones(numRevisiones){
        }
        ~Silabo()
        {

        }

        string getFacultad() const {
              return facultad;
          }

          const std::vector<string>& getCarreras() const {
              return carreras;
          }

          string getNombre() const {
              return nombre;
          }

          string getCodigoClase() const {
              return codigoClase;
          }

          QString getRuta() const {
              return ruta;
          }


          Estado getEstado() const {
              return estado;
          }

          string getObservacion() const {
              return observacion;
          }

          int getId() const {
              return id;
          }

          int getNumRevisiones() const {
              return numRevisiones;
          }

          // Setters
          void setFacultad(const string& nuevaFacultad) {
              facultad = nuevaFacultad;
          }

          void setCarreras(const std::vector<string>& nuevasCarreras) {
              carreras = nuevasCarreras;
          }

          void setNombre(const string& nuevoNombre) {
              nombre = nuevoNombre;
          }

          void setCodigoClase(const string& nuevoCodigoClase) {
              codigoClase = nuevoCodigoClase;
          }

          void setRuta(const QString& nuevaRuta) {
              ruta = nuevaRuta;
          }


          void setEstado(Estado nuevoEstado) {
              estado = nuevoEstado;
          }

          void setObservacion(const string& nuevaObservacion) {
              observacion = nuevaObservacion;
          }

          void setId(int nuevoId) {
              id = nuevoId;
          }

          void setNumRevisiones(int nuevoNumRevisiones) {
              numRevisiones = nuevoNumRevisiones;
          }

          long toNum() const {
              long val = 0;
              for (int i = 0; i < nombre.size(); i++) {
                  char c = nombre[i];
                  val += c;
              }

              return val;
          }

};

#endif // SILABO_H
