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
        string carrera;
        string insertadoPor;
        string codigoClase;
        QString ruta;

        string estado;
        string observacion; // Para que digan que quieren de cambio
        string visibilidad;

        int id; // Para mantener track de los archivos
        int numRevisiones; // Para contar cuantas veces se ha revisado el silabo

    public:

        Silabo(string facultad, string carrera, string nombre, string codigoClase, QString ruta, string estado, string observacion, int id, int numRevisiones)
            : facultad(facultad), carrera(carrera), insertadoPor(nombre), codigoClase(codigoClase),ruta(ruta),estado(estado), observacion(observacion), id(id), numRevisiones(numRevisiones){
        }
        ~Silabo(){}

          string getFacultad() const {
              return facultad;
          }

          string getCarreras() const {
              return carrera;
          }

          string getNombre() const {
              return insertadoPor;
          }

          string getCodigoClase() const {
              return codigoClase;
          }

          QString getRuta() const {
              return ruta;
          }


          string getEstado() const {
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

          void setCarreras(const string nuevasCarreras) {
              carrera = nuevasCarreras;
          }

          void setNombre(const string& nuevoNombre) {
              insertadoPor = nuevoNombre;
          }

          void setCodigoClase(const string& nuevoCodigoClase) {
              codigoClase = nuevoCodigoClase;
          }

          void setRuta(const QString& nuevaRuta) {
              ruta = nuevaRuta;
          }

          void setEstado(const string& nuevoEstado) {
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
              for (int i = 0; i < codigoClase.size(); i++) {
                  char c = codigoClase[i];
                  val += c;
              }

              return val;
          }

};

#endif // SILABO_H
