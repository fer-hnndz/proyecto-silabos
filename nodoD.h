#ifndef NODOD_H
#define NODOD_H
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::string;

template<typename tipo> class listaD;
template<typename tipo>
class nodoD{ //LISTA DOBLEMENTE ENLAZADA
    friend class listaD<tipo>;
    friend class MainWindow;
    friend class Arbol;
private:
    tipo Dato;
    nodoD<tipo> *AntPtr;
    nodoD<tipo> *SigPtr;
public:
    nodoD(const tipo &);
    nodoD(nodoD<tipo> *, const tipo &, nodoD<tipo> *);
    tipo getDato()const;
};

template<typename tipo>
nodoD<tipo>::nodoD(const tipo &Dato) : AntPtr(0), Dato(Dato), SigPtr(0)
{}

template<typename tipo>
nodoD<tipo>::nodoD(nodoD<tipo> *AntPtr,const tipo &Dato, nodoD<tipo> *SigPtr) : AntPtr(AntPtr), Dato(Dato), SigPtr(SigPtr){}

template<typename tipo>
tipo nodoD<tipo>::getDato() const
{
    return Dato;
}
#endif // NODOD_H
