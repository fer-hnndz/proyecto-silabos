#ifndef ARBOL_H
#define ARBOL_H

template <typename T>
class Arbol {
    private:
        Arbol<T>* left;
        Arbol<T>* right;
        T data;
    public:
        Arbol<T>* getArbolIzq() {
            return left;
        }

        Arbol<T>* getRightDer() {
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
};


#endif // ARBOL_H
