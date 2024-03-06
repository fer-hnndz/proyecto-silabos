#ifndef ARBOL_H
#define ARBOL_H
#include "nodoD.h"
#include <Silabo.h>

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

            int val = obj->toInt();
            cout << (val <= data->toInt()) << "\n";
            // Ordenar en base al nombre
            if (val <= data->toInt())
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
};


#endif // ARBOL_H
