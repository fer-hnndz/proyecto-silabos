#ifndef ARBOL_H
#define ARBOL_H
#include "nodoD.h"
#include <Silabo.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
using std::ofstream;
using std::ios;
using std::string;
using std::ios;


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
        void extraer() {

            std::ifstream file("data.xls");
                if (!file.is_open()) {
                    std::cerr << "Error al abrir el archivo.\n";
                    return;
                }

                std::string line;
                while (std::getline(file, line)) {
                    std::istringstream ss(line);
                    std::string facultad, carrera, nombre, codigoClase, ruta, estado, observacion;
                    int id, numRevisiones;

                    if (!(ss >> facultad >> carrera >> nombre >> codigoClase >> ruta >> estado >> observacion >> id >> numRevisiones)) {
                        std::cerr << "Error al leer datos de la línea.\n";
                        break;
                    }

                    Silabo *silabo = new Silabo(facultad, carrera, nombre, codigoClase, QString::fromStdString(ruta), estado, observacion, id, numRevisiones);

                    add(silabo);
                }
             file.close();
            if (std::remove("data.xls") != 0 ) {
                    std::cerr << "Error al eliminar el archivo.\n";
                } else {
                    std::cout << "Archivo eliminado exitosamente.\n";
                }


        }

        void guardarExcel(std::ofstream &file, Arbol *nodo) {
            if (nodo == nullptr) {
                return;
            }

            Silabo *silabo = nodo->getRaiz();

            file << silabo->getFacultad() << "\t"
                 << silabo->getCarreras() << "\t"
                 << silabo->getNombre() << "\t"
                 << silabo->getCodigoClase() << "\t"
                 << silabo->getRuta().toStdString() << "\t"
                 << silabo->getEstado()<< "\t"
                 << silabo->getObservacion() << "\t"
                 << silabo->getId() << "\t"
                 << silabo->getNumRevisiones() << "\t"<<"\n";

            // Llamar recursivamente para los hijos del nodo
            guardarExcel(file, nodo->getArbolIzq());
            guardarExcel(file, nodo->getArbolDer());
        }

        void guardar() {
            std::ifstream file;
            file.open("data.xls");
            file.close();
            std::ofstream File("data.xls");
            if (File.is_open()) {
                // Escribir los encabezados
                File << "Facultad\tCarrera\tNombre\tCodigo de Clase\tRuta\tEstado\tObservacion\tID\tNumero de Revisiones\n";
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
