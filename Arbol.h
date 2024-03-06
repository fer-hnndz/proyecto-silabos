#ifndef ARBOL_H
#define ARBOL_H
#include "nodoD.h"

template <typename T>
class Arbol {
    private:
        Arbol<T>* left;
        Arbol<T>* right;
        T data;

        // nodoD<T>* root;

        // void AddAux(nodoD<T> *nodo){
        //     if(nodo->AntPtr->AntPtr==0){
        //         nodoD<T>* Padre = nodo->AntPtr;
        //         Padre->AntPtr = nodo;
        //     }else if(nodo->AntPtr->SigPtr==0){
        //         nodoD<T>* Padre = nodo->AntPtr;
        //         Padre->SigPtr = nodo;
        //     }else if(nodo->SigPtr->AntPtr == 0){
        //         nodoD<T>* Padre = nodo->SigPtr;
        //         Padre->AntPtr = nodo;
        //     }else if(nodo->SigPtr->SigPtr == 0){
        //         nodoD<T>*Padre = nodo->SigPtr;
        //         Padre->SigPtr=nodo;
        //     }else{
        //         AddAux(nodo->AntPtr);
        //     }

        // }

    public:
        Arbol<T>* getArbolIzq() {
            return left;
        }

        Arbol<T>* getArbolDer() {
            return right;
        }

        T getRaiz() {
            return data;
        }

        void setArbolIzq(Arbol<T> &Arbol) {
            left = Arbol;
        }

        void setArbolDer(Arbol<T> &Arbol) {
            right = Arbol;
        }

        void setRaiz(T n) {
            data = n;
        }

        // void Add(nodoD<T> nodo){
        //     if(root==0){
        //         root = nodo;
        //     }else if(root->AntPtr==0){
        //         root->AntPtr = nodo;
        //     }else if(root->SigPtr==0){
        //         root->SigPtr = nodo;
        //     }else{
        //         AddAux(nodo);
        //     }
        // }
};


#endif // ARBOL_H
