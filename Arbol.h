#ifndef ARBOL_H
#define ARBOL_H
#include "nodoD.h"
#include <Silabo.h>
#include <Usuario.h>
#include <listaD.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include <QString>
using std::ofstream;
using std::ios;
using std::string;
using std::ios;
using std::cout;


class Arbol {
    private:
        Arbol* left;
        Arbol* right;
        Silabo *data = nullptr;

    public:

        Arbol(Silabo* silabo) {
            this->left = nullptr;
            this->right = nullptr;
            this->data = silabo;
        }
        Arbol* getArbolIzq() {
            return left;
        }

        Arbol* getArbolDer() {
            return right;
        }

        Silabo* getRaiz() {
            return data;
        }

        void setArbolIzq(Arbol &obj) {
            left = &obj;
        }

        void setArbolDer(Arbol &obj) {
            right = &obj;
        }

        void setRaiz(Silabo* n) {
            data = n;
        }

        void add(Silabo *obj)
        {
            if (data == nullptr)
            {
                data = obj;
                return;
            }

            int val = obj->toNum();
            cout << (val <= data->toNum()) << "\n";
            // Ordenar en base al nombre
            if (val <= data->toNum())
            {
                // Si no hay nada a la izquierda, agregar un arbol con ese silabo
                if (left == nullptr)
                {
                    left = new Arbol(obj);
                }
                else
                {
                    // Si hay un arbol a la izquierda, usar ese nuevo subarbol
                    // para ver donde se tiene que colocar
                    left->add(obj);
                }
            }
            else
            {
                // Tiene que ir a la derecha
                if (right == nullptr)
                {
                    right = new Arbol(obj);
                }
                else
                {
                    right->add(obj);
                }
            }
        }
        void extraerArbol(Arbol* arbol) {


            std::ifstream file("silabo.xls");
            if (file.is_open()) {
                string header;
                std::getline(file, header);

                string facultad, carrera, nombre, codigoClase, ruta, estado, observacion;
                int id, numRevisiones;
                while (file >> facultad >> carrera >> nombre >> codigoClase >> ruta >> estado >> observacion >> id >> numRevisiones) {
                    Silabo* nuevoSilabo = new Silabo(facultad, carrera, nombre, codigoClase, QString::fromStdString(ruta), estado, observacion, id, numRevisiones);
                    this->add(nuevoSilabo);
                }
                file.close();
                std::cout << "Silabos cargados desde el archivo.\n";
            } else {
                std::cerr << "Error al abrir el archivo.\n";
            }
        }


        void guardarExcel(std::ofstream &file, Arbol *nodo) {
            if (nodo == nullptr ) {
                return;
            }
               Silabo *silabo = nodo->getRaiz();
                   file
                        << silabo->getFacultad() << "\t"
                        << silabo->getCarreras() << "\t"
                        << silabo->getNombre() << "\t"
                        << silabo->getCodigoClase() << "\t"
                        << silabo->getRuta().toStdString() << "\t"
                        << silabo->getEstado() << "\t"
                        << silabo->getObservacion() << "\t"
                        << silabo->getId() << "\t"
                        << silabo->getNumRevisiones() << "\t" << "\n";


                guardarExcel(file, nodo->getArbolIzq());
                guardarExcel(file, nodo->getArbolDer());

        }


        void guardar() {
            std::ifstream file;
            file.open("silabo.xls");
            file.close();
            std::ofstream File("silabo.xls");
            if (File.is_open()) {
                File << "Facultad\tCarrera\tIngresado Por\tCodigo de Clase\tRuta\tEstado\tObservacion\tID\tNumero de Revisiones\n";
                guardarExcel(File,this);
                File.close();
                std::cout << "XLS exportado.\n";
            } else {
                std::cerr << "Error en el archivo.\n";
            }
        }


        ~Arbol() {
           if (left != nullptr) {
               delete left;
               left = nullptr;
           }
           if (right != nullptr) {
               delete right;
               right = nullptr;
           }
           if (data != nullptr) {
               delete data;
               data = nullptr;
           }
       }



};


#endif // ARBOL_H
